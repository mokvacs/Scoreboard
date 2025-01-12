#ifndef SHORTCUTRECORDERDIALOG_H
#define SHORTCUTRECORDERDIALOG_H

#include <QDialog>

namespace Ui {
class ShortcutRecorderDialog;
}

class ShortcutRecorderDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ShortcutRecorderDialog(QWidget *parent = nullptr);
    ~ShortcutRecorderDialog() override;

    void SetLabelString(const QString &text);
    QKeySequence GetKeySequence() const;

private:
    Ui::ShortcutRecorderDialog *ui;
};

#endif // SHORTCUTRECORDERDIALOG_H
