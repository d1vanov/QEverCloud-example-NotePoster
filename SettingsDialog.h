/**
 * Original work: Copyright (c) 2014 Sergey Skoblikov
 * Modified work: Copyright (c) 2015-2020 Dmitry Ivanov
 *
 * This file is a part of QEverCloud-example-NotePoster project and is
 * distributed under the terms of MIT license:
 * https://opensource.org/licenses/MIT
 */

#ifndef QEVERCLOUD_EXAMPLE_NOTE_POSTER_SETTINGS_DIALOG_H
#define QEVERCLOUD_EXAMPLE_NOTE_POSTER_SETTINGS_DIALOG_H

#include <QDialog>

namespace Ui {
class SettingsDialog;
}

class SettingsDialog: public QDialog
{
    Q_OBJECT
public:
    explicit SettingsDialog(QWidget * parent = nullptr);
    ~SettingsDialog() override;

private Q_SLOTS:
    void login();
    void onFinished();

private:
    Ui::SettingsDialog * m_pUi;
};

#endif // QEVERCLOUD_EXAMPLE_NOTE_POSTER_SETTINGS_DIALOG_H
