#include "MainWindow.h"
#include <QApplication>
#include <QMessageBox>
#include "SettingsDialog.h"
#include <QtDebug>

using namespace qevercloud;

class NotePosterApplication: public QApplication
{
public:
    bool notify(QObject * pObject, QEvent * pEvent);
};

bool NotePosterApplication::notify(QObject * pObject, QEvent * pEvent)
{
    try
    {
        return QApplication::notify(pObject, pEvent);
    }
    catch(const std::exception & exception)
    {
        qDebug() << exception.what();
        quit();
    }
    catch(...)
    {
        qDebug() << "Unknown exception";
        quit();
    }

    return false;
}

int main(int argc, char * argv[])
{
    try
    {
        // qrand is used for nonce generation by default
        // so qsrand must be called in the default case
        qsrand(QDateTime::currentMSecsSinceEpoch() % static_cast<quint64>(256)*256*256*256);

        QApplication app(argc, argv);

        SettingsDialog settingsDialog;
        if (settingsDialog.exec() != QDialog::Accepted) {
            return 0;
        }

        MainWindow window;
        window.show();

        return app.exec();
    }
    catch(const std::exception & exception)
    {
        qDebug() << exception.what();
        return 1;
    }
    catch(...)
    {
        qDebug() << "Unknown exception";
        return 1;
    }
}

