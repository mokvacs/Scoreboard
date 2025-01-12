#include "configeditordialog.h"
#include "ui_configeditordialog.h"

#include "configmanager.h"

#include "shortcutbutton.h"

ConfigEditorDialog::ConfigEditorDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigEditorDialog)
{
    ui->setupUi(this);
    setWindowTitle("Configuration");

    SetWidgetConfigIdentifier(ui->checkBoxShowControls, Config::Identifier::ShowControls);
    SetWidgetConfigIdentifier(ui->timeEditQuarterLength, Config::Identifier::QuarterLength);
    SetWidgetConfigIdentifier(ui->pushButtonBackgroundColourSelector, Config::Identifier::BackgroundColour);
    SetWidgetConfigIdentifier(ui->pushButtonTextColourSelector, Config::Identifier::TextColour);
    SetWidgetConfigIdentifier(ui->timeEditTimeoutLength, Config::Identifier::TimeoutLength);
    SetWidgetConfigIdentifier(ui->checkBoxStartTimout, Config::Identifier::StartTimoutTimerImmediately);
    SetWidgetConfigIdentifier(ui->checkBoxSoundBuzzerAfterTimeout, Config::Identifier::SoundBuzzerAfterTimeout);

    SetWidgetConfigIdentifier(ui->shortcutButtonStartStopTime, Config::Identifier::ShortcutTimerStartStop);
    SetWidgetConfigIdentifier(ui->shortcutButtonIncreaseScoreLeft, Config::Identifier::ShortcutIncreaseLeftScore);
    SetWidgetConfigIdentifier(ui->shortcutButtonDecreaseScoreLeft, Config::Identifier::ShortcutDecreaseLeftScore);
    SetWidgetConfigIdentifier(ui->shortcutButtonIncreaseFoulsLeft, Config::Identifier::ShortcutIncreaseLeftFouls);
    SetWidgetConfigIdentifier(ui->shortcutButtonDecreaseFoulsLeft, Config::Identifier::ShortcutDecreaseLeftFouls);
    SetWidgetConfigIdentifier(ui->shortcutButtonIncreaseScoreRight, Config::Identifier::ShortcutIncreaseRightScore);
    SetWidgetConfigIdentifier(ui->shortcutButtonDecreaseScoreRight, Config::Identifier::ShortcutDecreaseRightScore);
    SetWidgetConfigIdentifier(ui->shortcutButtonIncreaseFoulsRight, Config::Identifier::ShortcutIncreaseRightFouls);
    SetWidgetConfigIdentifier(ui->shortcutButtonDecreaseFoulsRight, Config::Identifier::ShortcutDecreaseRightFouls);

    SetShortcutDescriptionInEditor(ui->shortcutButtonStartStopTime, ui->labelShortcutStartStopTime);
    SetShortcutDescriptionInEditor(ui->shortcutButtonIncreaseScoreLeft, ui->labelIncreaseScoreLeft);
    SetShortcutDescriptionInEditor(ui->shortcutButtonDecreaseScoreLeft, ui->labelDecreaseScoreLeft);
    SetShortcutDescriptionInEditor(ui->shortcutButtonIncreaseFoulsLeft, ui->labelIncreaseFoulsLeft);
    SetShortcutDescriptionInEditor(ui->shortcutButtonDecreaseFoulsLeft, ui->labelDecreaseFoulsLeft);
    SetShortcutDescriptionInEditor(ui->shortcutButtonIncreaseScoreRight, ui->labelIncreaseScoreRight);
    SetShortcutDescriptionInEditor(ui->shortcutButtonDecreaseScoreRight, ui->labelDecreaseScoreRight);
    SetShortcutDescriptionInEditor(ui->shortcutButtonIncreaseFoulsRight, ui->labelIncreaseFoulsRight);
    SetShortcutDescriptionInEditor(ui->shortcutButtonDecreaseFoulsRight, ui->labelDecreaseFoulsRight);

    InitWidgets();
}

ConfigEditorDialog::~ConfigEditorDialog()
{
    delete ui;
}

void ConfigEditorDialog::SaveConfigValues() const
{
    auto &manager = ConfigManager::get();
    for (auto iter = m_widgetIdMap.begin(); iter != m_widgetIdMap.end(); ++iter)
    {
        auto widget = iter.value();
        if (auto w = dynamic_cast<QCheckBox*>(widget))
        {
            manager.SaveConfigValue(iter.key(), w->isChecked());
        }
        else if (auto w = dynamic_cast<QTimeEdit*>(widget))
        {
            manager.SaveConfigValue(iter.key(), w->time());
        }
        else if (auto w = dynamic_cast<ColourSelectorWidget*>(widget))
        {
            manager.SaveConfigValue(iter.key(), w->getColour());
        }
        else if (auto w = dynamic_cast<ShortcutButton*>(widget))
        {
            manager.SaveConfigValue(iter.key(), w->GetKeySequence());
        }
    }
}

void ConfigEditorDialog::InitWidgets()
{
    auto &manager = ConfigManager::get();
    for (auto iter = m_widgetIdMap.begin(); iter != m_widgetIdMap.end(); ++iter)
    {
        auto configValue = manager.GetConfigValue(iter.key());
        auto widget = iter.value();
        if (auto w = dynamic_cast<QCheckBox*>(widget))
        {
            w->setChecked(configValue.toBool());
        }
        else if (auto w = dynamic_cast<QTimeEdit*>(widget))
        {
            w->setTime(configValue.toTime());
        }
        else if (auto w = dynamic_cast<ColourSelectorWidget*>(widget))
        {
            w->setColour(configValue.value<QColor>());
        }
        else if (auto w = dynamic_cast<ShortcutButton*>(widget))
        {
            w->SetKeySequence(configValue.value<QKeySequence>());
        }
    }
}

void ConfigEditorDialog::SetWidgetConfigIdentifier(QWidget *widget, const Config::Identifier id)
{
    m_widgetIdMap.insert(id, widget);
}

void ConfigEditorDialog::SetShortcutDescriptionInEditor(ShortcutButton *editor, QLabel *label)
{
    editor->SetDescription(label->text());
}
