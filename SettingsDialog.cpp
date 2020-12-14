/**
 * Original work: Copyright (c) 2014 Sergey Skoblikov
 * Modified work: Copyright (c) 2015-2020 Dmitry Ivanov
 *
 * This file is a part of QEverCloud-example-NotePoster project and is
 * distributed under the terms of MIT license:
 * https://opensource.org/licenses/MIT
 */

#include "SettingsDialog.h"
#include "ui_SettingsDialog.h"
#include "Settings.h"

#include <qevercloud/QEverCloudOAuth.h>

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
    EvernoteOAuthDialog dialog(
        m_pUi->consumerKeyLineEdit->text().trimmed(),
        m_pUi->consumerSecretLineEdit->text().trimmed(),
        m_pUi->hostLineEdit->text().trimmed());

    dialog.setWindowTitle("Log in to Evernote");

    if (dialog.exec() != QDialog::Accepted) {
        QMessageBox::critical(0, "NotePoster", "Login failed.\n" + dialog.oauthError());
        return;
    }

    const auto res = dialog.oauthResult();
    m_pUi->authenticationTokenLineEdit->setText(res.authenticationToken);
    m_pUi->noteStoreUrlLineEdit->setText(res.noteStoreUrl);
}

void SettingsDialog::onFinished()
{
    auto * s = settings();
    s->setHost(m_pUi->hostLineEdit->text());
    s->setConsumerKey(m_pUi->consumerKeyLineEdit->text());
    s->setConsumerSecret(m_pUi->consumerSecretLineEdit->text());
    s->setNoteStoreUrl(m_pUi->noteStoreUrlLineEdit->text());
    s->setAuthenticationToken(m_pUi->authenticationTokenLineEdit->text());
}
