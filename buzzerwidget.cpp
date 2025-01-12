#include "buzzerwidget.h"
#include "ui_buzzerwidget.h"

#include <QSound>

BuzzerWidget::BuzzerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BuzzerWidget)
{
    ui->setupUi(this);
    connect(ui->pushButton, &QPushButton::clicked, this, &BuzzerWidget::PlayBuzzerSound);
}

BuzzerWidget::~BuzzerWidget()
{
    delete ui;
}

void BuzzerWidget::PlayBuzzerSound()
{
    QSound::play(":/mixkit-basketball-buzzer-1647.wav");
}
