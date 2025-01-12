#include "shortcutbutton.h"

#include "shortcutrecorderdialog.h"

ShortcutButton::ShortcutButton(QWidget *parent)
    : QPushButton(parent),
      m_keySequence(Qt::Key::Key_unknown)
{
    connect(this, &QPushButton::clicked, this, &ShortcutButton::OnClicked);
}

void ShortcutButton::SetKeySequence(const QKeySequence &key)
{
    m_keySequence = key;
    setText(key.toString());
}

QKeySequence ShortcutButton::GetKeySequence() const
{
    return m_keySequence;
}

void ShortcutButton::SetDescription(const QString &d)
{
    m_description = d;
}

void ShortcutButton::OnClicked()
{
    ShortcutRecorderDialog d;
    const QString s = QString("Change shortcut for the following: %1.\nPress the shortcut you want to set").arg(m_description);
    d.SetLabelString(s);
    if (d.exec() == QDialog::Accepted)
    {
        SetKeySequence(d.GetKeySequence());
    }
}
