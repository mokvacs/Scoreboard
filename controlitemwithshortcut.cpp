#include "controlitemwithshortcut.h"
#include "ui_controlitemwithshortcut.h"

ControlItemWithShortcut::ControlItemWithShortcut(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ControlItemWithShortcut)
{
    ui->setupUi(this);

    connect(ui->pushButtonPlus, &QToolButton::clicked, this, &ControlItemWithShortcut::increase);
    connect(ui->pushButtonMinus, &QToolButton::clicked, this, &ControlItemWithShortcut::decrease);
}

ControlItemWithShortcut::~ControlItemWithShortcut()
{
    delete ui;
}

void ControlItemWithShortcut::SetIncreaseText(const QString &text)
{
    ui->pushButtonPlus->setText(text);
}

void ControlItemWithShortcut::SetDecreaseText(const QString &text)
{
    ui->pushButtonMinus->setText(text);
}

void ControlItemWithShortcut::SetShortcutText(const QString &text)
{
    ui->label->setText(text);
}
