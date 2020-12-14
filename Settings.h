/**
 * Original work: Copyright (c) 2014 Sergey Skoblikov
 * Modified work: Copyright (c) 2015-2020 Dmitry Ivanov
 *
 * This file is a part of QEverCloud-example-NotePoster project and is
 * distributed under the terms of MIT license:
 * https://opensource.org/licenses/MIT
 */

#ifndef QEVERCLOUD_EXAMPLE_NOTE_POSTER_SETTINGS_H
#define QEVERCLOUD_EXAMPLE_NOTE_POSTER_SETTINGS_H

#include <QObject>
#include <QString>

class QSettings;

class Settings: public QObject
{
    Q_OBJECT
public:
    explicit Settings(QObject * parent = nullptr);
    ~Settings() override;

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
    QSettings * m_settings = nullptr;
};

Settings * settings();

#endif // QEVERCLOUD_EXAMPLE_NOTE_POSTER_SETTINGS_H
