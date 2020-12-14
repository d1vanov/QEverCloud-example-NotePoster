/**
 * Original work: Copyright (c) 2014 Sergey Skoblikov
 * Modified work: Copyright (c) 2015-2020 Dmitry Ivanov
 *
 * This file is a part of QEverCloud-example-NotePoster project and is
 * distributed under the terms of MIT license:
 * https://opensource.org/licenses/MIT
 */

#ifndef QEVERCLOUD_EXAMPLE_NOTE_POSTER_MAIN_WINDOW_H
#define QEVERCLOUD_EXAMPLE_NOTE_POSTER_MAIN_WINDOW_H

#include <QDialog>
#include <QTextCharFormat>

#include <qevercloud/QEverCloud.h>

namespace Ui {
class MainWindow;
}

class MainWindow: public QDialog
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget * parent = nullptr);
    ~MainWindow() override;

private Q_SLOTS:
    void setBold(bool yes);
    void setItalic(bool yes);
    void currentCharFormatChanged(QTextCharFormat f);
    void createNote();

private:
    Ui::MainWindow * m_pUi;
    qevercloud::INoteStorePtr m_pNoteStore;
    QMap<QString, QString> m_notebooks;
    bool m_inLoop = false;
};

#endif // QEVERCLOUD_EXAMPLE_NOTE_POSTER_MAIN_WINDOW_H
