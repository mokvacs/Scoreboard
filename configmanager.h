#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include <memory>

class QSettings;
class QString;
class QVariant;

namespace Config
{
    enum Identifier : unsigned int
    {
        ShowControls,
        QuarterLength,
        TimeoutLength,
        BackgroundColour,
        TextColour,
        StartTimoutTimerImmediately,
        SoundBuzzerAfterTimeout,

        // Shortcuts
        ShortcutTimerStartStop,
        ShortcutIncreaseLeftScore,
        ShortcutDecreaseLeftScore,
        ShortcutIncreaseLeftFouls,
        ShortcutDecreaseLeftFouls,
        ShortcutIncreaseRightScore,
        ShortcutDecreaseRightScore,
        ShortcutIncreaseRightFouls,
        ShortcutDecreaseRightFouls,

        Invalid
    };
}

class ConfigManager
{
public:
    ~ConfigManager() = default;

    QVariant GetConfigValue(const Config::Identifier i);
    void SaveConfigValue(const Config::Identifier i, const QVariant& value);

    static ConfigManager &get();

private:
    ConfigManager();

    std::unique_ptr<QSettings> m_settings;

    static std::unique_ptr<ConfigManager> m_instance;
};

#endif // CONFIGMANAGER_H
