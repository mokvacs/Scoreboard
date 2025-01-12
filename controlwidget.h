#ifndef CONTROLWIDGET_H
#define CONTROLWIDGET_H

#include <QWidget>

namespace Ui {
class ControlWidget;
}

class ControlWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ControlWidget(QWidget *parent = nullptr);
    ~ControlWidget() override;

    void RefreshSettings();

    void SetTeamName(const QString& name);

    void ChangeScore(const int delta);
    void ChangeFouls(const int delta);

public slots:
    void OnScoreboardResized(const int width, const int height);

private:
    void SetLabelColours();

    void InitControls();

    void UpdateScore();
    void UpdateFouls();

    int m_score;
    int m_fouls;

    Ui::ControlWidget *ui;
};

#endif // CONTROLWIDGET_H
