#ifndef QEVERCLOUD_EXAMPLE_NOTE_POSTER_SETTINGS_H
#define QEVERCLOUD_EXAMPLE_NOTE_POSTER_SETTINGS_H

#include <QObject>
#include <QString>

class QSettings;

class Settings: public QObject
{
    Q_OBJECT
public:
    Settings();

    QString host();
    void setHost(QString value);

    QString consumerKey();
    void setConsumerKey(QString value);

    QString consumerSecret();
    void setConsumerSecret(QString value);

    QString noteStoreUrl();
    void setNoteStoreUrl(QString value);

    QString authenticationToken();
    void setAuthenticationToken(QString value);

private:
    QSettings * m_settings;
};

Settings * settings();

#endif // QEVERCLOUD_EXAMPLE_NOTE_POSTER_SETTINGS_H
