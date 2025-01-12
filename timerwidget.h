#ifndef TIMERWIDGET_H
#define TIMERWIDGET_H

#include <QTimer>
#include <QWidget>

namespace Ui {
class TimerWidget;
}

class TimerWidget : public QWidget
{
    Q_OBJECT

public:
    enum Mode {
        Main,
        Timeout
    };

    explicit TimerWidget(QWidget *parent = nullptr);
    ~TimerWidget() override;

    void RefreshSettings();

    void SetMode(Mode m);

signals:
    void buzzerClicked();

    void warning(const QString&);

    void timeoutStarted(TimerWidget*);
    void timeExpired();

public slots:
    void OnStartStopClick();

    void OnScoreboardResized(const int width, const int height);

protected:
    void mouseDoubleClickEvent(QMouseEvent *e) override;

private slots:
    void OnEdit();
    void OnReset();
    void OnTimeout();

    void UpdateTime();

private:
    void SetStripped();

    bool NextIntervalIsTenth() const;

    bool IntervalIsFull() const;

    void DecreaseTenths();
    void DecreaseSeconds();
    void DecreaseMinutes();

    void SetNextInterval();

    void InitTimes(const int minutes = -1, const int seconds = -1, const int tenths = -1);

    void ExpireTime();
    void UpdateTimeDisplay(const bool extraPrecise = false);
    void StartTimer();
    void StopTimer();

    void SetLabelColours();

    Ui::TimerWidget *ui;

    QTimer m_timer;
    int m_timerInterval;
    int m_minutesRemaining;
    int m_secondsRemaining;
    int m_tenthsLeft;

    bool m_isInitial;
    bool m_isFinished;

    Mode m_mode;
};

#endif // TIMERWIDGET_H
