#ifndef INCREMENTABLELCDNUMBER_H
#define INCREMENTABLELCDNUMBER_H

#include <QLCDNumber>

class IncrementableLCDNumber : public QLCDNumber
{
    Q_OBJECT
public:
    explicit IncrementableLCDNumber(QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *e) override;

private:
    void IncreaseCounter();
    void DecreaseCounter();
};

#endif // INCREMENTABLELCDNUMBER_H
