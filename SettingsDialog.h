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
    explicit SettingsDialog(QWidget * parent = 0);
    ~SettingsDialog();

private Q_SLOTS:
    void login();
    void onFinished();

private:
    Ui::SettingsDialog * m_pUi;
};

#endif // QEVERCLOUD_EXAMPLE_NOTE_POSTER_SETTINGS_DIALOG_H
