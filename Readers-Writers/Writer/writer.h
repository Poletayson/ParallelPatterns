#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <QObject>
#include <QSharedMemory>
#include <QFile>
#include <QFileDevice>
#include <qcanal.h>
#include <message.h>
#include <QTextStream>
#include <QThread>
#include <QTime>

class Writer : public QObject
{
    Q_OBJECT
public:
    explicit Writer(QObject *parent = nullptr);
    void toFile (QString str);

public slots:
    void run ();

private:
//    QCanal *customerCanal;      //канал для приема заказчиком
//    QCanal *dispatcherCanalOrder;   //канал для приема диспетчером
//    QCanal *courierCanal;
    void write ();
    QCanal *generalCanal;

    unsigned long MAX_DELAY = 700;
    int ORDER_COUNT = 10000000;
    int WRITER_ID;


signals:
    void finished();


};

#endif // CUSTOMER_H
