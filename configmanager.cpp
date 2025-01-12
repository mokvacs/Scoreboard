#include "configmanager.h"

#include <QColor>
#include <QDebug>
#include <QKeySequence>
#include <QSettings>
#include <QString>
#include <QTime>

namespace Config
{
    const QMap<Identifier, QString> configNameMap = {
        {ShowControls, "ShowControls"},
        {QuarterLength, "QuarterLength"},
        {TimeoutLength, "TimeoutLength"},
        {BackgroundColour, "BackgroundColour"},
        {TextColour, "TextColour"},
        {StartTimoutTimerImmediately, "StartTimoutTimerImmediately"},
        {SoundBuzzerAfterTimeout, "SoundBuzzerAfterTimeout"},
        {ShortcutTimerStartStop, "ShortcutTimerStartStop"},
        {ShortcutIncreaseLeftScore, "ShortcutIncreaseLeftScore"},
        {ShortcutDecreaseLeftScore, "ShortcutDecreaseLeftScore"},
        {ShortcutIncreaseLeftFouls, "ShortcutIncreaseLeftFouls"},
        {ShortcutDecreaseLeftFouls, "ShortcutDecreaseLeftFouls"},
        {ShortcutIncreaseRightScore, "ShortcutIncreaseRightScore"},
        {ShortcutDecreaseRightScore, "ShortcutDecreaseRightScore"},
        {ShortcutIncreaseRightFouls, "ShortcutIncreaseRightFouls"},
        {ShortcutDecreaseRightFouls, "ShortcutDecreaseRightFouls"}
    };

    QString IdentifierToString(const Identifier i)
    {
        return configNameMap.value(i, "");
    }

    Identifier StringToIdentifier(const QString& s)
    {
        return configNameMap.key(s, Invalid);
    }

    QVariant GetDefault(const Identifier i)
    {
        QVariant res;
        switch (i) {
        case ShowControls:
            res = true;
            break;
        case QuarterLength:
            res = QTime(0, 10);
            break;
        case TimeoutLength:
            res = QTime(0, 1);
            break;
        case BackgroundColour:
            res = QColor(240, 240, 240);
            break;
        case TextColour:
            res = QColor(Qt::black);
            break;
        case StartTimoutTimerImmediately:
            res = true;
            break;
        case SoundBuzzerAfterTimeout:
            res = true;
            break;
        case ShortcutTimerStartStop:
            res = QKeySequence(Qt::Key_Space);
            break;
        case ShortcutIncreaseLeftScore:
            res = QKeySequence(Qt::Key_W);
            break;
        case ShortcutDecreaseLeftScore:
            res = QKeySequence(Qt::Key_S);
            break;
        case ShortcutIncreaseLeftFouls:
            res = QKeySequence(Qt::Key_A);
            break;
        case ShortcutDecreaseLeftFouls:
            res = QKeySequence(Qt::Key_D);
            break;
        case ShortcutIncreaseRightScore:
            res = QKeySequence(Qt::Key_Up);
            break;
        case ShortcutDecreaseRightScore:
            res = QKeySequence(Qt::Key_Down);
            break;
        case ShortcutIncreaseRightFouls:
            res = QKeySequence(Qt::Key_Right);
            break;
        case ShortcutDecreaseRightFouls:
            res = QKeySequence(Qt::Key_Left);
            break;
        case Invalid:
            break;
        }
        return res;
    }
}

std::unique_ptr<ConfigManager> ConfigManager::m_instance (nullptr);

QVariant ConfigManager::GetConfigValue(const Config::Identifier i)
{
    return m_settings->value(Config::IdentifierToString(i), Config::GetDefault(i));
}

void ConfigManager::SaveConfigValue(const Config::Identifier i, const QVariant &value)
{
    m_settings->setValue(Config::IdentifierToString(i), value);
}

ConfigManager &ConfigManager::get()
{
    if (m_instance == nullptr)
        m_instance.reset(new ConfigManager);
    return *m_instance;
}

ConfigManager::ConfigManager()
    : m_settings(new QSettings("MateKovacs", "Scoreboard"))
{

}
