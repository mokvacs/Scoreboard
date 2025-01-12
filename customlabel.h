#ifndef CUSTOMLABEL_H
#define CUSTOMLABEL_H

#include <QLabel>

class CustomLabel : public QLabel
{
    Q_OBJECT
public:
    explicit CustomLabel(QWidget *parent = nullptr);
    ~CustomLabel() override;

protected:
    void mouseDoubleClickEvent(QMouseEvent *e) override;
};

#endif // CUSTOMLABEL_H
