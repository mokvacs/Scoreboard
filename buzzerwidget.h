#ifndef BUZZERWIDGET_H
#define BUZZERWIDGET_H

#include <QWidget>

namespace Ui {
class BuzzerWidget;
}

class BuzzerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BuzzerWidget(QWidget *parent = nullptr);
    ~BuzzerWidget() override;

public slots:
    void PlayBuzzerSound();

private:
    Ui::BuzzerWidget *ui;
};

#endif // BUZZERWIDGET_H
