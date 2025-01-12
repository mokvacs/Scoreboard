#include "timerwidget.h"
#include "ui_timerwidget.h"

#include "configmanager.h"
#include "timeeditdialog.h"

#include <QResizeEvent>
#include <QDebug>
#include <QMouseEvent>
#include <QTime>

#define ONE_TENTH_MS 100
#define ONE_SECOND_MS 1000

namespace  {

    void SetLabelColour(QLabel *label, const QColor &colour)
    {
        auto p = label->palette();
        p.setColor(label->foregroundRole(), colour);
        label->setPalette(p);
    }

}

TimerWidget::TimerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TimerWidget)
{
    ui->setupUi(this);

    m_timer.setTimerType(Qt::TimerType::PreciseTimer);

    QFont timeFont;
    timeFont.setBold(true);
    timeFont.setPointSize(40);
    ui->labelMinutes->setFont(timeFont);
    ui->labelColon->setFont(timeFont);
    ui->labelSeconds->setFont(timeFont);

    m_mode = Main;

    InitTimes();

    UpdateTimeDisplay();
    SetLabelColours();

    connect(ui->pushButtonStartStop, &QPushButton::clicked, this, &TimerWidget::OnStartStopClick);
    connect(ui->pushButtonReset, &QPushButton::clicked, this, &TimerWidget::OnReset);
    connect(ui->pushButtonTimeout, &QPushButton::clicked, this, &TimerWidget::OnTimeout);
    connect(ui->pushButtonBuzzer, &QPushButton::clicked, this, &TimerWidget::buzzerClicked);

    connect(&m_timer, &QTimer::timeout, this, &TimerWidget::UpdateTime);
}

TimerWidget::~TimerWidget()
{
    delete ui;
}

void TimerWidget::RefreshSettings()
{
    SetLabelColours();
}

void TimerWidget::SetLabelColours()
{
    auto &manager = ConfigManager::get();
    auto textColour = manager.GetConfigValue(Config::Identifier::TextColour).value<QColor>();

    SetLabelColour(ui->labelMinutes, textColour);
    SetLabelColour(ui->labelSeconds, textColour);
    SetLabelColour(ui->labelColon, textColour);
    ui->widgetPeriod->SetTextColour(textColour);
}

void TimerWidget::SetMode(TimerWidget::Mode m)
{
    m_mode = m;
}

void TimerWidget::OnReset()
{
    InitTimes();
    UpdateTimeDisplay();
}

void TimerWidget::OnTimeout()
{
    if (m_timer.isActive())
    {
        emit warning("Can't start timeout while clock is running");
        return;
    }
    TimerWidget *timeoutWidget = new TimerWidget();

    emit timeoutStarted(timeoutWidget);
    connect(timeoutWidget,
            &TimerWidget::timeExpired,
            timeoutWidget,
            [timeoutWidget](){timeoutWidget->close(); timeoutWidget->deleteLater();});
    timeoutWidget->SetStripped();
    timeoutWidget->SetMode(Timeout);
    timeoutWidget->InitTimes();
    timeoutWidget->UpdateTimeDisplay();
    timeoutWidget->setWindowModality(Qt::WindowModality::ApplicationModal);
    timeoutWidget->setWindowTitle("Timeout");

    auto &manager = ConfigManager::get();
    if (manager.GetConfigValue(Config::Identifier::StartTimoutTimerImmediately).toBool())
    {
        timeoutWidget->StartTimer();
    }

    timeoutWidget->show();
}

void TimerWidget::OnStartStopClick()
{
    if (m_timer.isActive())
        StopTimer();
    else
        StartTimer();
}

void TimerWidget::OnScoreboardResized(const int width, const int height)
{
    const int pointSize = std::min(width / 31, height / 12);
//    qDebug() << "Setting font size to " << pointSize;
    QFont timeFont;
    timeFont.setBold(true);
    timeFont.setPointSize(pointSize);
    ui->labelMinutes->setFont(timeFont);
    ui->labelColon->setFont(timeFont);
    ui->labelSeconds->setFont(timeFont);
}

void TimerWidget::mouseDoubleClickEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton)
    {
        if (!m_timer.isActive())
            OnEdit();
        return;
    }
    QWidget::mouseDoubleClickEvent(e);
}

void TimerWidget::OnEdit()
{
    TimeEditDialog d;
    d.SetCurrentTime(m_minutesRemaining, m_secondsRemaining, m_tenthsLeft);
    if (d.exec() == QDialog::Accepted)
    {
        InitTimes(d.GetMinutes(), d.GetSeconds(), d.GetTenths());
        UpdateTimeDisplay(true);
    }
}

void TimerWidget::UpdateTime()
{
//    qDebug() << "Before" << m_minutesRemaining << ":" << m_secondsRemaining << "." << m_tenthsLeft;
    if (NextIntervalIsTenth())
    {
        DecreaseTenths();
    }
    else
    {
        DecreaseSeconds();
    }
    if (m_isFinished)
        return;
    SetNextInterval();
    if (m_timer.interval() != m_timerInterval)
    {
        m_timer.setInterval(m_timerInterval);
    }
//    qDebug() << "Before" << m_minutesRemaining << ":" << m_secondsRemaining << "." << m_tenthsLeft;
    UpdateTimeDisplay();
}

void TimerWidget::SetStripped()
{
    ui->pushButtonBuzzer->setVisible(false);
    ui->pushButtonTimeout->setVisible(false);
    ui->widgetPeriod->setVisible(false);
}

bool TimerWidget::NextIntervalIsTenth() const
{
    return m_minutesRemaining == 0 || (m_minutesRemaining == 1 && m_secondsRemaining == 0);
}

bool TimerWidget::IntervalIsFull() const
{
    return m_timerInterval == (NextIntervalIsTenth() ? ONE_TENTH_MS : ONE_SECOND_MS);
}

void TimerWidget::DecreaseTenths()
{
    if (--m_tenthsLeft < 0)
    {
        m_tenthsLeft = 9;
        DecreaseSeconds();
    }
}

void TimerWidget::DecreaseSeconds()
{
    if (--m_secondsRemaining < 0)
    {
        m_secondsRemaining = 59;
        DecreaseMinutes();
    }
}

void TimerWidget::DecreaseMinutes()
{
    if (--m_minutesRemaining < 0)
    {
        ExpireTime();
    }
}

void TimerWidget::SetNextInterval()
{
    const bool countTenths = m_isInitial ? (NextIntervalIsTenth()) : (m_minutesRemaining == 0);
    m_timerInterval = countTenths ? 100 : ONE_SECOND_MS;
}

void TimerWidget::InitTimes(const int minutes, const int seconds, const int tenths)
{
    auto &manager = ConfigManager::get();
    const auto configId = m_mode == Main ? Config::Identifier::QuarterLength : Config::Identifier::TimeoutLength;
    const QTime defaultTime = manager.GetConfigValue(configId).toTime();
    m_minutesRemaining = minutes == -1 ? defaultTime.minute() : minutes;
    m_secondsRemaining = seconds == -1 ? defaultTime.second() : seconds;
    m_tenthsLeft = tenths == -1 ? 0 : tenths;

    m_isInitial = true;
    m_isFinished = false;
    SetNextInterval();
}

void TimerWidget::ExpireTime()
{
    m_isFinished = true;
    m_minutesRemaining = 0;
    m_secondsRemaining = 0;
    m_tenthsLeft = 0;
    m_timer.stop();
    emit timeExpired();
}

void TimerWidget::UpdateTimeDisplay(const bool extraPrecise)
{
    if (m_minutesRemaining <= 0)
    {
        ui->labelColon->setText(".");
        ui->labelMinutes->setText(QString::number(m_secondsRemaining).rightJustified(2, '0').toStdString().c_str());
        ui->labelSeconds->setText(QString("%1%2").arg(m_tenthsLeft).arg(extraPrecise ? m_timerInterval / 10 : 0).toStdString().c_str());
    }
    else
    {
        ui->labelColon->setText(":");
        ui->labelMinutes->setText(QString::number(m_minutesRemaining).rightJustified(2, '0').toStdString().c_str());
        ui->labelSeconds->setText(QString::number(m_secondsRemaining).rightJustified(2, '0').toStdString().c_str());
    }
}

void TimerWidget::StartTimer()
{
    if (m_isInitial && IntervalIsFull())
    {
        UpdateTime();
        m_isInitial = false;
    }
    else
    {
        UpdateTimeDisplay(false);
    }
    m_timer.setSingleShot(false);
    m_timer.start(m_timerInterval);
}

void TimerWidget::StopTimer()
{
    m_timerInterval = m_timer.remainingTime();
    m_timer.stop();
    UpdateTimeDisplay(true);
}
