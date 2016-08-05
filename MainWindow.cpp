#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "Settings.h"
#include <QMessageBox>

using namespace qevercloud;

MainWindow::MainWindow(QWidget * parent) :
    QDialog(parent),
    m_pUi(new Ui::MainWindow),
    m_inLoop(false)
{
    m_pUi->setupUi(this);

    m_pNoteStore = new NoteStore(settings()->noteStoreUrl(), settings()->authenticationToken(), this);

    // reading notebook names and guids
    QStringList notebookNames;
    QString defaultNotebookName;
    QList<Notebook> notebooksList = m_pNoteStore->listNotebooks();
    int numNotebooks = notebooksList.length();
    notebookNames.reserve(numNotebooks);
    for(int i = 0; i < numNotebooks; i++)
    {
        const Notebook & notebook = notebooksList.at(i);
        m_notebooks[notebook.name] = notebook.guid;
        notebookNames << notebook.name;
        if (notebook.defaultNotebook) {
            defaultNotebookName = notebook.name;
        }
    }
    qSort(notebookNames);
    m_pUi->notebooksComboBox->addItems(notebookNames);
    m_pUi->notebooksComboBox->setCurrentIndex(notebookNames.indexOf(defaultNotebookName));

    connect(m_pUi->noteTextEdit, SIGNAL(currentCharFormatChanged(QTextCharFormat)), SLOT(currentCharFormatChanged(QTextCharFormat)));
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
        note.title = m_pUi->titleLineEdit->text().trimmed().left(EDAM_NOTE_TITLE_LEN_MAX);
        note.notebookGuid = m_notebooks[m_pUi->notebooksComboBox->currentText()];
        note.content = enml;
        note = m_pNoteStore->createNote(note);
        QMessageBox::information(this, "Success", QString("Note GUID: %1").arg(note.guid));
    }
    catch(const std::exception & e)
    {
        QMessageBox::critical(this, "Failure", e.what());
    }
}

