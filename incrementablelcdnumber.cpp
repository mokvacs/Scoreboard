#include "incrementablelcdnumber.h"

#include <QMouseEvent>

IncrementableLCDNumber::IncrementableLCDNumber(QWidget *parent)
    : QLCDNumber(parent)
{

}

void IncrementableLCDNumber::mousePressEvent(QMouseEvent *e)
{
    switch (e->button()) {
    case Qt::LeftButton:
    {
        IncreaseCounter();
        break;
    }
    case Qt::RightButton:
    {
        DecreaseCounter();
        break;
    }
    default:
        QLCDNumber::mousePressEvent(e);
    }
}

void IncrementableLCDNumber::IncreaseCounter()
{
    this->display(std::min(9, this->intValue() + 1));
}

void IncrementableLCDNumber::DecreaseCounter()
{
    this->display(std::max(0, this->intValue() - 1));
}
