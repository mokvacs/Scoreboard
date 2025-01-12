#ifndef SHORTCUTBUTTON_H
#define SHORTCUTBUTTON_H

#include <QKeySequence>
#include <QPushButton>

class ShortcutButton : public QPushButton
{
    Q_OBJECT
public:
    explicit ShortcutButton(QWidget *parent);
    ~ShortcutButton() override = default;

    void SetKeySequence(const QKeySequence &key);
    QKeySequence GetKeySequence() const;

    void SetDescription(const QString &d);

private slots:
    void OnClicked();

private:
    QString m_description;
    QKeySequence m_keySequence;
};

#endif // SHORTCUTBUTTON_H
