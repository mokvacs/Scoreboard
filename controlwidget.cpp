#include "controlwidget.h"
#include "ui_controlwidget.h"

#include "configmanager.h"

ControlWidget::ControlWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ControlWidget)
{
    ui->setupUi(this);

    ui->lcdNumber->setDigitCount(3);

    InitControls();

    QFont foulFont = ui->labelFouls->font();
    foulFont.setBold(true);
    foulFont.setPointSize(40);
    ui->labelFouls->setFont(foulFont);

    QFont teamNameFont = ui->labelTeamName->font();
    teamNameFont.setBold(true);
    teamNameFont.setPointSize(60);
    ui->labelTeamName->setFont(teamNameFont);

    SetLabelColours();

    m_score = 0;
    m_fouls = 0;

    UpdateScore();
    UpdateFouls();

    connect(ui->plusOneControlItem, &ControlItemWithShortcut::increase, this, [this](){ChangeScore(1);});
    connect(ui->plusOneControlItem, &ControlItemWithShortcut::decrease, this, [this](){ChangeScore(-1);});

    connect(ui->plusTwoControlItem, &ControlItemWithShortcut::increase, this, [this](){ChangeScore(2);});
    connect(ui->plusTwoControlItem, &ControlItemWithShortcut::decrease, this, [this](){ChangeScore(-2);});

    connect(ui->plusThreeControlItem, &ControlItemWithShortcut::increase, this, [this](){ChangeScore(3);});
    connect(ui->plusThreeControlItem, &ControlItemWithShortcut::decrease, this, [this](){ChangeScore(-3);});

    connect(ui->foulControlItem, &ControlItemWithShortcut::increase, this, [this](){ChangeFouls(1);});
    connect(ui->foulControlItem, &ControlItemWithShortcut::decrease, this, [this](){ChangeFouls(-1);});

    RefreshSettings();
}

ControlWidget::~ControlWidget()
{
    delete ui;
}

void ControlWidget::RefreshSettings()
{
    auto &manager = ConfigManager::get();

    const bool enableButtons = manager.GetConfigValue(Config::Identifier::ShowControls).toBool();

    ui->plusOneControlItem->setVisible(enableButtons);
    ui->plusTwoControlItem->setVisible(enableButtons);
    ui->plusThreeControlItem->setVisible(enableButtons);
    ui->foulControlItem->setVisible(enableButtons);
    ui->widgetPlaceholder->setVisible(!enableButtons);

    SetLabelColours();
}

void ControlWidget::SetTeamName(const QString &name)
{
    ui->labelTeamName->setText(name);
}

void ControlWidget::ChangeScore(const int delta)
{
    m_score += delta;
    if (m_score < 0)
        m_score = 0;
    UpdateScore();
}

void ControlWidget::ChangeFouls(const int delta)
{
    m_fouls += delta;
    if (m_fouls < 0)
        m_fouls = 0;
    UpdateFouls();
}

void ControlWidget::OnScoreboardResized(const int width, const int height)
{
    const int foulPointSize = std::min(width / 31, height / 12);
    QFont foulFont;
    foulFont.setBold(true);
    foulFont.setPointSize(foulPointSize);
    ui->labelFouls->setFont(foulFont);

    const int teamNameLength = ui->labelTeamName->text().size();
    const int teamNamePointSize = std::min(width / 3 / teamNameLength, height / 8);
    QFont teamNameFont;
    teamNameFont.setBold(true);
    teamNameFont.setPointSize(teamNamePointSize);
    ui->labelTeamName->setFont(teamNameFont);
}

void ControlWidget::SetLabelColours()
{
    auto &manager = ConfigManager::get();
    auto textColour = manager.GetConfigValue(Config::Identifier::TextColour).value<QColor>();

    auto p = ui->labelTeamName->palette();
    p.setColor(ui->labelTeamName->foregroundRole(), textColour);
    ui->labelTeamName->setPalette(p);

    p = ui->labelFouls->palette();
    p.setColor(ui->labelFouls->foregroundRole(), textColour);
    ui->labelFouls->setPalette(p);

    p = ui->lcdNumber->palette();
    p.setColor(ui->lcdNumber->foregroundRole(), textColour);
    ui->lcdNumber->setPalette(p);
}

void ControlWidget::InitControls()
{
    ui->foulControlItem->SetIncreaseText("+1");
    ui->foulControlItem->SetDecreaseText("-1");
    ui->foulControlItem->SetShortcutText("");
    ui->foulControlItem->adjustSize();

    ui->plusOneControlItem->SetIncreaseText("+1");
    ui->plusOneControlItem->SetDecreaseText("-1");
    ui->plusOneControlItem->SetShortcutText("");

    ui->plusTwoControlItem->SetIncreaseText("+2");
    ui->plusTwoControlItem->SetDecreaseText("-2");
    ui->plusTwoControlItem->SetShortcutText("");

    ui->plusThreeControlItem->SetIncreaseText("+3");
    ui->plusThreeControlItem->SetDecreaseText("-3");
    ui->plusThreeControlItem->SetShortcutText("");
}

void ControlWidget::UpdateScore()
{
    const QString s (QString::number(m_score));
    ui->lcdNumber->display(s);
}

void ControlWidget::UpdateFouls()
{
    ui->labelFouls->setText(QString::number(m_fouls));
}
