#include "mainwindow.h"

#include <QApplication>
#include <QThread>
#include <reader.h>
#include <master.h>
#include <storage.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //создаем объекты и перемещаем в потоки
    QThread* readerThread = new QThread();
    Reader* reader = new Reader ();
    QObject::connect(readerThread,SIGNAL(started()), reader, SLOT(run()));
    QObject::connect(reader, SIGNAL(finished()), readerThread, SLOT(terminate()));
    reader->moveToThread(readerThread);

    readerThread->start();

    MainWindow w;
    w.show();
    return a.exec();
}
