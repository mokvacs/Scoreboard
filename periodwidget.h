#ifndef PERIODWIDGET_H
#define PERIODWIDGET_H

#include <QWidget>

namespace Ui {
class PeriodWidget;
}

class PeriodWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PeriodWidget(QWidget *parent = nullptr);
    ~PeriodWidget() override;

    void SetTextColour(const QColor &textColour);

private:
    Ui::PeriodWidget *ui;
};

#endif // PERIODWIDGET_H
