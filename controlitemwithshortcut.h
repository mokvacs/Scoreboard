#ifndef CONTROLITEMWITHSHORTCUT_H
#define CONTROLITEMWITHSHORTCUT_H

#include <QWidget>

namespace Ui {
class ControlItemWithShortcut;
}

class ControlItemWithShortcut : public QWidget
{
    Q_OBJECT

public:
    explicit ControlItemWithShortcut(QWidget *parent = nullptr);
    ~ControlItemWithShortcut() override;

    void SetIncreaseText(const QString& text);
    void SetDecreaseText(const QString& text);
    void SetShortcutText(const QString& text);

signals:
    void increase();
    void decrease();

private:
    Ui::ControlItemWithShortcut *ui;
};

#endif // CONTROLITEMWITHSHORTCUT_H
