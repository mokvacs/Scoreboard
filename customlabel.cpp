#include "customlabel.h"

#include <QMouseEvent>
#include <QInputDialog>

CustomLabel::CustomLabel(QWidget *parent)
    : QLabel(parent)
{

}

CustomLabel::~CustomLabel()
{

}

void CustomLabel::mouseDoubleClickEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton)
    {
        const auto text = QInputDialog::getText(this, "Edit Team Name", "Team Name");
        if (!text.isEmpty())
        {
            this->setText(text);
        }
        return;
    }
    QLabel::mouseDoubleClickEvent(e);
}
