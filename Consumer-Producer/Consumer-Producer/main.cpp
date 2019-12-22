#include "mainwindow.h"

#include <QApplication>
#include <QThread>
#include <ConsProd.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    int consCounter = 5;
    int prodCounter = 3;

    qsrand(static_cast<unsigned int>(QTime::currentTime().msec()));

    int ind = 1;
    for (int i = 0; i < consCounter; i++){
        //создаем объекты и перемещаем в потоки
        QThread* consumerThread = new QThread();
        Consumer* consumer = new Consumer (ind++);
        QObject::connect(consumerThread,SIGNAL(started()), consumer, SLOT(run()));
        QObject::connect(consumer, SIGNAL(finished()), consumerThread, SLOT(terminate()));
        consumer->moveToThread(consumerThread);
        consumerThread->start();
    }

    ind = 1;
    for (int i = 0; i < prodCounter; i++){
        //создаем объекты и перемещаем в потоки
        QThread* producerThread = new QThread();
        Producer* producer = new Producer (ind++);
        QObject::connect(producerThread,SIGNAL(started()), producer, SLOT(run()));
        QObject::connect(producer, SIGNAL(finished()), producerThread, SLOT(terminate()));
        producer->moveToThread(producerThread);
        producerThread->start();
    }

    MainWindow w;
    w.show();
    return a.exec();
}
