#ifndef QEVERCLOUD_EXAMPLE_NOTE_POSTER_MAIN_WINDOW_H
#define QEVERCLOUD_EXAMPLE_NOTE_POSTER_MAIN_WINDOW_H

#include <QDialog>
#include <QTextCharFormat>

#include <qt5qevercloud/QEverCloud.h>

namespace Ui {
class MainWindow;
}

class MainWindow: public QDialog
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget * parent = Q_NULLPTR);
    ~MainWindow();

private slots:
    void setBold(bool yes);
    void setItalic(bool yes);
    void currentCharFormatChanged(QTextCharFormat f);
    void createNote();
private:
    Ui::MainWindow * m_pUi;
    qevercloud::INoteStorePtr m_pNoteStore;
    QMap<QString, QString> m_notebooks;
    bool m_inLoop;
};

#endif // QEVERCLOUD_EXAMPLE_NOTE_POSTER_MAIN_WINDOW_H
