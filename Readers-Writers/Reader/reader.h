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

class Reader : public QObject
{
    Q_OBJECT
public:
    explicit Reader(QObject *parent = nullptr);
    void toFile (QString str);

public slots:
    void run ();

private:
//    QCanal *customerCanal;      //канал для приема заказчиком
//    QCanal *dispatcherCanalOrder;   //канал для приема диспетчером
//    QCanal *courierCanal;
    QCanal *generalCanal;

    int ORDER_COUNT = 10000000;


signals:
    void finished();


};

#endif // CUSTOMER_H
