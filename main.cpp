/**
 * Original work: Copyright (c) 2014 Sergey Skoblikov
 * Modified work: Copyright (c) 2015-2020 Dmitry Ivanov
 *
 * This file is a part of QEverCloud-example-NotePoster project and is
 * distributed under the terms of MIT license:
 * https://opensource.org/licenses/MIT
 */

#include "MainWindow.h"
#include "NotePosterApplication.h"
#include "SettingsDialog.h"

#include <qevercloud/Log.h>

#include <QDebug>
#include <QMessageBox>

#include <stdexcept>

using namespace qevercloud;

int main(int argc, char * argv[])
{
    try
    {
        // qrand is used for nonce generation by default
        // so qsrand must be called in the default case
        qsrand(QDateTime::currentMSecsSinceEpoch() % static_cast<quint64>(256)*256*256*256);

        QApplication app(argc, argv);

        qevercloud::setLogger(qevercloud::newStdErrLogger(qevercloud::LogLevel::Trace));

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

