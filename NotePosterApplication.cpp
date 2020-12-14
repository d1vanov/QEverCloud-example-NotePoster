/**
 * Original work: Copyright (c) 2014 Sergey Skoblikov
 * Modified work: Copyright (c) 2015-2020 Dmitry Ivanov
 *
 * This file is a part of QEverCloud-example-NotePoster project and is
 * distributed under the terms of MIT license:
 * https://opensource.org/licenses/MIT
 */

#include "NotePosterApplication.h"

#include <QDebug>

#include <stdexcept>

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
