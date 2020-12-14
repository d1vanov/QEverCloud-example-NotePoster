/**
 * Original work: Copyright (c) 2014 Sergey Skoblikov
 * Modified work: Copyright (c) 2015-2020 Dmitry Ivanov
 *
 * This file is a part of QEverCloud-example-NotePoster project and is
 * distributed under the terms of MIT license:
 * https://opensource.org/licenses/MIT
 */

#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "Settings.h"

#include <QMessageBox>

using namespace qevercloud;

MainWindow::MainWindow(QWidget * parent) :
    QDialog(parent),
    m_pUi(new Ui::MainWindow)
{
    m_pUi->setupUi(this);

    m_pNoteStore.reset(
        newNoteStore(
            settings()->noteStoreUrl(),
            newRequestContext(settings()->authenticationToken(), -1)));

    // reading notebook names and guids
    QStringList notebookNames;
    QString defaultNotebookName;
    QList<Notebook> notebooksList = m_pNoteStore->listNotebooks();
    int numNotebooks = notebooksList.length();
    notebookNames.reserve(numNotebooks);
    for(int i = 0; i < numNotebooks; i++)
    {
        const Notebook & notebook = notebooksList.at(i);

        const auto & notebookName = notebook.name();
        Q_ASSERT(notebookName);

        const auto & notebookGuid = notebook.guid();
        Q_ASSERT(notebookGuid);

        m_notebooks[*notebookName] = *notebookGuid;
        notebookNames << *notebookName;
        if (notebook.defaultNotebook()) {
            defaultNotebookName = *notebookName;
        }
    }

    std::sort(notebookNames.begin(), notebookNames.end());

    m_pUi->notebooksComboBox->addItems(notebookNames);
    m_pUi->notebooksComboBox->setCurrentIndex(
        notebookNames.indexOf(defaultNotebookName));

    QObject::connect(
        m_pUi->noteTextEdit,
        &QTextEdit::currentCharFormatChanged,
        this,
        &MainWindow::currentCharFormatChanged);
}

MainWindow::~MainWindow()
{
    delete m_pUi;
}

void MainWindow::setBold(bool yes)
{
    if (!m_inLoop) {
        m_pUi->noteTextEdit->setFontWeight(yes ? QFont::Bold : QFont::Normal);
    }
}

void MainWindow::setItalic(bool yes)
{
    if (!m_inLoop) {
        m_pUi->noteTextEdit->setFontItalic(yes);
    }
}

void MainWindow::currentCharFormatChanged(QTextCharFormat format)
{
    Q_UNUSED(format)

    m_inLoop = true;
    m_pUi->boldButton->setChecked(m_pUi->noteTextEdit->fontWeight() >= QFont::Bold);
    m_pUi->italicButton->setChecked(m_pUi->noteTextEdit->fontItalic());
    m_inLoop = false;
}

void MainWindow::createNote()
{
    // For the sake of simplicity do not handle images and ENML extensions
    QString enml = m_pUi->noteTextEdit->toHtml();
    enml = enml.mid(enml.indexOf("<body "));
    enml.replace("<body ", "<en-note ");
    enml = enml.left(enml.indexOf("</body>"));
    enml += "</en-note>";

    // the xml header must always be present
    enml.prepend("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
                 "<!DOCTYPE en-note SYSTEM \"http://xml.evernote.com/pub/enml2.dtd\">\n");

    try
    {
        Note note;
        note.setTitle(m_pUi->titleLineEdit->text().trimmed().left(EDAM_NOTE_TITLE_LEN_MAX));
        note.setNotebookGuid(m_notebooks[m_pUi->notebooksComboBox->currentText()]);
        note.setContent(enml);

        note = m_pNoteStore->createNote(note);

        const auto & noteGuid = note.guid();
        Q_ASSERT(noteGuid);

        QMessageBox::information(this, "Success", QString("Note GUID: %1").arg(*noteGuid));
    }
    catch(const std::exception & e)
    {
        QMessageBox::critical(this, "Failure", e.what());
    }
}

