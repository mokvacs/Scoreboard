#include "colourselectorwidget.h"

#include <QColorDialog>

ColourSelectorWidget::ColourSelectorWidget( QWidget* parent )
    : QPushButton(parent)
{
    connect(this, &QPushButton::clicked, this, &ColourSelectorWidget::changeColour);
}

void ColourSelectorWidget::updateColour()
{
    setStyleSheet("background-color: " + m_colour.name());
}

void ColourSelectorWidget::changeColour()
{
    QColor newColour = QColorDialog::getColor(m_colour, parentWidget());
    if (newColour != m_colour)
    {
        setColour(newColour);
    }
}

void ColourSelectorWidget::setColour( const QColor& colour )
{
    this->m_colour = colour;
    updateColour();
}

const QColor& ColourSelectorWidget::getColour() const
{
    return m_colour;
}
