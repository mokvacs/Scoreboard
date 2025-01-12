#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include <QWidget>

namespace Ui {
class Scoreboard;
}

class ConfigManager;
class TimerWidget;

class Scoreboard : public QWidget
{
    Q_OBJECT

public:
    explicit Scoreboard(QWidget *parent = nullptr);
    ~Scoreboard() override;

    void RefreshAllSettings();

    void keyPressEvent(QKeyEvent *event) override;

signals:
    void resized(int width, int height);

protected:
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void OnTimeoutStarted(TimerWidget *timerWidget);

    void PlayBuzzerSound();

private:
    void SetApplicationBackground(ConfigManager &manager);
    void SetKeySequenceCallbacks(ConfigManager &manager);

    Ui::Scoreboard *ui;
};

#endif // SCOREBOARD_H
