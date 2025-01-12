#ifndef COLOURSELECTORWIDGET_H
#define COLOURSELECTORWIDGET_H

#include <QPushButton>
#include <QColor>

class ColourSelectorWidget : public QPushButton
{
    Q_OBJECT
public:
    ColourSelectorWidget(QWidget* parent);

    void setColour(const QColor& color);
    const QColor& getColour() const;

public slots:
    void updateColour();
    void changeColour();

private:
    QColor m_colour;
};

#endif // COLOURSELECTORWIDGET_H
