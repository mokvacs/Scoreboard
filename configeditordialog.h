#ifndef CONFIGEDITORDIALOG_H
#define CONFIGEDITORDIALOG_H

#include <QDialog>
#include <QMap>

namespace Ui {
class ConfigEditorDialog;
}

namespace Config {
enum Identifier : unsigned int;
}

class ShortcutButton;
class QLabel;

class ConfigEditorDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConfigEditorDialog(QWidget *parent = nullptr);
    ~ConfigEditorDialog() override;

    void SaveConfigValues() const;

private:
    void InitWidgets();

    void SetWidgetConfigIdentifier(QWidget *widget, const Config::Identifier id);
    void SetShortcutDescriptionInEditor(ShortcutButton *editor, QLabel *label);

    QMap<Config::Identifier, QWidget*> m_widgetIdMap;
    Ui::ConfigEditorDialog *ui;
};

#endif // CONFIGEDITORDIALOG_H
