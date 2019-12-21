#include "mainwindow.h"

#include <QApplication>
#include <QThread>
#include <reader.h>
#include <dispetcher.h>
#include <master.h>
#include <storage.h>
#include <courier.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //создаем объекты и перемещаем в потоки
    QThread* customerThread = new QThread();
    Customer* customer = new Customer ();
    QObject::connect(customerThread,SIGNAL(started()), customer, SLOT(run()));
    QObject::connect(customer, SIGNAL(finished()), customerThread, SLOT(terminate()));
    customer->moveToThread(customerThread);

//    QThread* dispetcherThread = new QThread();
//    Dispetcher* dispetcher = new Dispetcher ();
//    QObject::connect(dispetcherThread,SIGNAL(started()), dispetcher, SLOT(run()));
//    QObject::connect(dispetcher, SIGNAL(finished()), dispetcherThread, SLOT(terminate()));
//    dispetcher->moveToThread(dispetcherThread);

//    QThread* masterThread = new QThread();
//    Master* master = new Master ();
//    QObject::connect(masterThread,SIGNAL(started()), master, SLOT(run()));
//    QObject::connect(master, SIGNAL(finished()), masterThread, SLOT(terminate()));
//    master->moveToThread(masterThread);

//    QThread* storageThread = new QThread();
//    Storage* storage = new Storage ();
//    QObject::connect(storageThread,SIGNAL(started()), storage, SLOT(run()));
//    QObject::connect(storage, SIGNAL(finished()), storageThread, SLOT(terminate()));
//    storage->moveToThread(storageThread);

//    QThread* courierThread = new QThread();
//    Courier* courier = new Courier ();
//    QObject::connect(courierThread,SIGNAL(started()), courier, SLOT(run()));
//    QObject::connect(courier, SIGNAL(finished()), courierThread, SLOT(terminate()));
//    courier->moveToThread(courierThread);

    customerThread->start();
//    dispetcherThread->start();
//    masterThread->start();
//    storageThread->start();
//    courierThread->start();


    MainWindow w;
    w.show();
    return a.exec();
}
