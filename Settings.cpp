#include "Settings.h"
#include <QApplication>
#include <QDir>
#include <QSettings>
#include <QtDebug>

Settings * settings()
{
    static Settings * pSettings = 0;
    if (!pSettings) {
        pSettings = new Settings;
    }

    return pSettings;
}

Settings::Settings()
{
    QString iniPath = QDir(qApp->applicationDirPath()).absoluteFilePath("NotePoster.ini");
    m_settings = new QSettings(iniPath, QSettings::IniFormat, this);
}

QString Settings::host()
{
    return m_settings->value("Evernote/host", QString()).toString().trimmed();
}

void Settings::setHost(QString value)
{
    m_settings->setValue("Evernote/host", value);
    m_settings->sync();
}

QString Settings::consumerKey()
{
    return m_settings->value("Evernote/consumerKey", QString()).toString().trimmed();
}

void Settings::setConsumerKey(QString value)
{
    m_settings->setValue("Evernote/consumerKey", value);
    m_settings->sync();
}

QString Settings::consumerSecret()
{
    return m_settings->value("Evernote/consumerSecret", QString()).toString().trimmed();
}

void Settings::setConsumerSecret(QString value)
{
    m_settings->setValue("Evernote/consumerSecret", value);
    m_settings->sync();
}

QString Settings::noteStoreUrl()
{
    return m_settings->value("Evernote/noteStoreUrl", QString()).toString().trimmed();
}

void Settings::setNoteStoreUrl(QString value)
{
    m_settings->setValue("Evernote/noteStoreUrl", value);
    m_settings->sync();
}

QString Settings::authenticationToken()
{
    return m_settings->value("Evernote/authenticationToken", QString()).toString().trimmed();
}

void Settings::setAuthenticationToken(QString value)
{
    m_settings->setValue("Evernote/authenticationToken", value);
    m_settings->sync();
}
