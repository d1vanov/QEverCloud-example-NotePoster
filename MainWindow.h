#ifndef QEVERCLOUD_EXAMPLE_NOTE_POSTER_MAIN_WINDOW_H
#define QEVERCLOUD_EXAMPLE_NOTE_POSTER_MAIN_WINDOW_H

#include <QDialog>
#include <QTextCharFormat>

#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
#include <qt4qevercloud/QEverCloud.h>
#else
#include <qt5qevercloud/QEverCloud.h>
#endif

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
    qevercloud::INoteStore * m_pNoteStore;
    QMap<QString, QString> m_notebooks;
    bool m_inLoop;
};

#endif // QEVERCLOUD_EXAMPLE_NOTE_POSTER_MAIN_WINDOW_H
