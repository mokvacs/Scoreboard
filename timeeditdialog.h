#ifndef TIMEEDITDIALOG_H
#define TIMEEDITDIALOG_H

#include <QDialog>

namespace Ui {
class TimeEditDialog;
}

class TimeEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TimeEditDialog(QWidget *parent = nullptr);
    ~TimeEditDialog() override;

    void SetCurrentTime(const int minutes, const int seconds, const int tenths);

    int GetMinutes() const;
    int GetSeconds() const;
    int GetTenths() const;

private:
    Ui::TimeEditDialog *ui;
};

#endif // TIMEEDITDIALOG_H
