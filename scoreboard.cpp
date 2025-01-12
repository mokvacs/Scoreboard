#include "scoreboard.h"
#include "ui_scoreboard.h"

#include "configmanager.h"

#include <QDebug>
#include <QKeyEvent>
#include <QSound>

namespace
{
    QMap<QKeySequence, std::function<void()>> keyFunctionMap;

    QKeySequence GetKeySequenceFromEvent(const QKeyEvent &event)
    {
        QString modifier;
        const auto& m = event.modifiers();
        if (m & Qt::ShiftModifier)
        {
            modifier += "Shift+";
        }
        if (m & Qt::ControlModifier)
        {
            modifier += "Ctrl+";
        }
        if (m & Qt::AltModifier)
        {
            modifier += "Alt+";
        }
        return QKeySequence(modifier + QKeySequence(event.key()).toString());
    }
}

Scoreboard::Scoreboard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Scoreboard)
{
    ui->setupUi(this);

    ui->widgetControlLeft->SetTeamName("Home");
    ui->widgetControlRight->SetTeamName("Away");

    setFocusPolicy(Qt::FocusPolicy::StrongFocus);

    for (auto child : findChildren<QWidget*>())
    {
        child->setFocusPolicy(Qt::FocusPolicy::NoFocus);
    }

    connect(this, &Scoreboard::resized, ui->widgetTimer,        &TimerWidget::OnScoreboardResized);
    connect(this, &Scoreboard::resized, ui->widgetControlLeft,  &ControlWidget::OnScoreboardResized);
    connect(this, &Scoreboard::resized, ui->widgetControlRight, &ControlWidget::OnScoreboardResized);

    connect(ui->widgetTimer, &TimerWidget::timeExpired, this, &Scoreboard::PlayBuzzerSound);
    connect(ui->widgetTimer, &TimerWidget::timeoutStarted, this, &Scoreboard::OnTimeoutStarted);

    connect(ui->widgetTimer, &TimerWidget::buzzerClicked, this, &Scoreboard::PlayBuzzerSound);

    auto &manager = ConfigManager::get();
    SetApplicationBackground(manager);
    SetKeySequenceCallbacks(manager);
}

Scoreboard::~Scoreboard()
{
    delete ui;
}

void Scoreboard::RefreshAllSettings()
{
    ui->widgetControlLeft->RefreshSettings();
    ui->widgetControlRight->RefreshSettings();
    ui->widgetTimer->RefreshSettings();

    auto &manager = ConfigManager::get();
    SetApplicationBackground(manager);
    SetKeySequenceCallbacks(manager);
}

void Scoreboard::keyPressEvent(QKeyEvent *event)
{
    const auto keySequence = GetKeySequenceFromEvent(*event);
    if (keyFunctionMap.contains(keySequence))
        keyFunctionMap.value(keySequence)();
    else
        QWidget::keyPressEvent(event);
//    qDebug() << "Handling key press event: " << event->key();
//    const int delta = event->modifiers() & Qt::KeyboardModifier::ControlModifier ? -1 : 1;
//    switch (event->key()) {
//    case Qt::Key_Space:
//        ui->widgetTimer->OnStartStopClick();
//        break;
//    case Qt::Key_Right:
//        ui->widgetControlRight->ChangeScore(delta);
//        break;
//    case Qt::Key_Left:
//        ui->widgetControlLeft->ChangeScore(delta);
//        break;
//    case Qt::Key_A:
//        ui->widgetControlLeft->ChangeFouls(delta);
//        break;
//    case Qt::Key_D:
//        ui->widgetControlRight->ChangeFouls(delta);
//        break;
//    default:
//        QWidget::keyPressEvent(event);
//        break;
//    }
}

void Scoreboard::resizeEvent(QResizeEvent *event)
{
//    qDebug() << "Width: " << event->size().width() << ", height: " << event->size().height();
    emit resized(event->size().width(), event->size().height());
    QWidget::resizeEvent(event);
}

void Scoreboard::OnTimeoutStarted(TimerWidget *timerWidget)
{
    auto &manager = ConfigManager::get();
    if (manager.GetConfigValue(Config::Identifier::SoundBuzzerAfterTimeout).toBool())
    {
        connect(timerWidget, &TimerWidget::timeExpired, this, &Scoreboard::PlayBuzzerSound);
    }
}

void Scoreboard::PlayBuzzerSound()
{
    qDebug() << "Playing buzzer sound";
    QSound::play(":/buzzer.wav");
}

void Scoreboard::SetApplicationBackground(ConfigManager &manager)
{
    auto p = QApplication::palette();
    p.setColor(QPalette::Background, manager.GetConfigValue(Config::Identifier::BackgroundColour).value<QColor>());
    QApplication::setPalette(p);
}

void Scoreboard::SetKeySequenceCallbacks(ConfigManager &manager)
{
    static const QMap<Config::Identifier, std::function<void()>> funcMap
    {
        {Config::Identifier::ShortcutTimerStartStop, [this](){ui->widgetTimer->OnStartStopClick();}},
        {Config::Identifier::ShortcutIncreaseLeftScore, [this](){ui->widgetControlLeft->ChangeScore(1);}},
        {Config::Identifier::ShortcutDecreaseLeftScore, [this](){ui->widgetControlLeft->ChangeScore(-1);}},
        {Config::Identifier::ShortcutIncreaseLeftFouls, [this](){ui->widgetControlLeft->ChangeFouls(1);}},
        {Config::Identifier::ShortcutDecreaseLeftFouls, [this](){ui->widgetControlLeft->ChangeFouls(-1);}},
        {Config::Identifier::ShortcutIncreaseRightScore, [this](){ui->widgetControlRight->ChangeScore(1);}},
        {Config::Identifier::ShortcutDecreaseRightScore, [this](){ui->widgetControlRight->ChangeScore(-1);}},
        {Config::Identifier::ShortcutIncreaseRightFouls, [this](){ui->widgetControlRight->ChangeFouls(1);}},
        {Config::Identifier::ShortcutDecreaseRightFouls, [this](){ui->widgetControlRight->ChangeFouls(-1);}}
    };
    keyFunctionMap.clear();
    for (auto iter = funcMap.cbegin(); iter != funcMap.cend(); ++iter)
    {
        auto keySequence = manager.GetConfigValue(iter.key()).value<QKeySequence>();
        keyFunctionMap.insert(keySequence, iter.value());
    }
}
