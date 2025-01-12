#include "timeeditdialog.h"
#include "ui_timeeditdialog.h"

TimeEditDialog::TimeEditDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TimeEditDialog)
{
    ui->setupUi(this);

    setWindowTitle("Edit Time Remaining");
}

TimeEditDialog::~TimeEditDialog()
{
    delete ui;
}

void TimeEditDialog::SetCurrentTime(const int minutes, const int seconds, const int tenths)
{
    ui->spinBoxMinutes->setValue(minutes);
    ui->spinBoxSeconds->setValue(seconds);
    ui->spinBoxTenths->setValue(tenths);
}

int TimeEditDialog::GetMinutes() const
{
    return ui->spinBoxMinutes->value();
}

int TimeEditDialog::GetSeconds() const
{
    return ui->spinBoxSeconds->value();
}

int TimeEditDialog::GetTenths() const
{
    return ui->spinBoxTenths->value();
}
