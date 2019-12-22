#include "mainwindow.h"

#include <QApplication>
#include <QThread>
#include <writer.h>
#include <master.h>
#include <storage.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //создаем объекты и перемещаем в потоки
    QThread* writerThread = new QThread();
    Writer* writer = new Writer ();
    QObject::connect(writerThread,SIGNAL(started()), writer, SLOT(run()));
    QObject::connect(writer, SIGNAL(finished()), writerThread, SLOT(terminate()));
    writer->moveToThread(writerThread);

    writerThread->start();

    MainWindow w;
    w.show();
    return a.exec();
}
