/**
 * Original work: Copyright (c) 2014 Sergey Skoblikov
 * Modified work: Copyright (c) 2015-2020 Dmitry Ivanov
 *
 * This file is a part of QEverCloud-example-NotePoster project and is
 * distributed under the terms of MIT license:
 * https://opensource.org/licenses/MIT
 */

#ifndef QEVERCLOUD_EXAMPLE_NOTE_POSTER_APPLICATION_H
#define QEVERCLOUD_EXAMPLE_NOTE_POSTER_APPLICATION_H

#include <QApplication>

class NotePosterApplication: public QApplication
{
    Q_OBJECT
public:
    bool notify(QObject * pObject, QEvent * pEvent) override;
};

#endif // QEVERCLOUD_EXAMPLE_NOTE_POSTER_APPLICATION_H
