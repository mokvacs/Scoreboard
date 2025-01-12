#include "periodwidget.h"
#include "ui_periodwidget.h"

PeriodWidget::PeriodWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PeriodWidget)
{
    ui->setupUi(this);
}

PeriodWidget::~PeriodWidget()
{
    delete ui;
}

void PeriodWidget::SetTextColour(const QColor &textColour)
{
    auto p = ui->label->palette();
    p.setColor(ui->label->foregroundRole(), textColour);
    ui->label->setPalette(p);

    p = ui->lcdNumber->palette();
    p.setColor(ui->label->foregroundRole(), textColour);
    ui->lcdNumber->setPalette(p);
}
