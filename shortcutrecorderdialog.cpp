#include "shortcutrecorderdialog.h"
#include "ui_shortcutrecorderdialog.h"

#include <QKeyEvent>

ShortcutRecorderDialog::ShortcutRecorderDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShortcutRecorderDialog)
{
    ui->setupUi(this);

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
}

ShortcutRecorderDialog::~ShortcutRecorderDialog()
{
    delete ui;
}

void ShortcutRecorderDialog::SetLabelString(const QString &text)
{
    ui->label->setText(text);
}

QKeySequence ShortcutRecorderDialog::GetKeySequence() const
{
    return ui->keySequenceEdit->keySequence();
}
