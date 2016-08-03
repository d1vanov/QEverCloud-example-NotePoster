#include "SettingsDialog.h"
#include "ui_SettingsDialog.h"
#include "Settings.h"

#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
#include <QEverCloud-qt4/QEverCloudOAuth.h>
#else
#include <QEverCloud-qt5/QEverCloudOAuth.h>
#endif

#include <QMessageBox>

using namespace qevercloud;

SettingsDialog::SettingsDialog(QWidget * parent) :
    QDialog(parent),
    m_pUi(new Ui::SettingsDialog)
{
    m_pUi->setupUi(this);
    m_pUi->hostLineEdit->setText(settings()->host());
    m_pUi->consumerKeyLineEdit->setText(settings()->consumerKey());
    m_pUi->consumerSecretLineEdit->setText(settings()->consumerSecret());
    m_pUi->noteStoreUrlLineEdit->setText(settings()->noteStoreUrl());
    m_pUi->authenticationTokenLineEdit->setText(settings()->authenticationToken());
}

SettingsDialog::~SettingsDialog()
{
    delete m_pUi;
}

void SettingsDialog::login()
{
    EvernoteOAuthDialog dialog(m_pUi->consumerKeyLineEdit->text().trimmed(),
                               m_pUi->consumerSecretLineEdit->text().trimmed(),
                               m_pUi->hostLineEdit->text().trimmed());
    dialog.setWindowTitle("Log in to Evernote");

    if (dialog.exec() != QDialog::Accepted) {
        QMessageBox::critical(0, "NotePoster", "Login failed.\n" + dialog.oauthError());
        return;
    }

    m_pUi->authenticationTokenLineEdit->setText(dialog.oauthResult().authenticationToken);
    m_pUi->noteStoreUrlLineEdit->setText(dialog.oauthResult().noteStoreUrl);
}

void SettingsDialog::onFinished()
{
    settings()->setHost(m_pUi->hostLineEdit->text());
    settings()->setConsumerKey(m_pUi->consumerKeyLineEdit->text());
    settings()->setConsumerSecret(m_pUi->consumerSecretLineEdit->text());
    settings()->setNoteStoreUrl(m_pUi->noteStoreUrlLineEdit->text());
    settings()->setAuthenticationToken(m_pUi->authenticationTokenLineEdit->text());
}
