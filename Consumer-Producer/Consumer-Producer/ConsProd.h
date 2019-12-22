#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <QObject>
#include <QSharedMemory>
#include <QFile>
#include <QFileDevice>
#include <QTextStream>
#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include <QTime>
#include <QDebug>
#include <qcanal.h>
#include <message.h>

static int ORDER_MAX = 0;
static int PROD_DELAY = 500;    //время на производство
static int  storage = 0;
static int orderCount = 0;
static QMutex qmt;
static QWaitCondition condition;
static QMutex mutexProducers;
static QWaitCondition conditionProducers;

/*
 *
 * ПОТРЕБИТЕЛЬ
 *
 */

class Consumer : public QObject
{
    Q_OBJECT
public:
    explicit Consumer(int id, QObject *parent = nullptr);
    void toFile (QString str);

public slots:
    void run ();

private:
    void consume ();
    QCanal *generalCanal;

    unsigned long MAX_DELAY = 1500;
    int CONSUMER_ID;

signals:
    void finished();

};

/*
 *
 * ПРОИЗВОДИТЕЛЬ
 *
 */

class Producer : public QObject
{
    Q_OBJECT
public:
    explicit Producer(int id, QObject *parent = nullptr);
    void toFile (QString str);

public slots:
    void run ();

private:
    void produce ();
    QCanal *generalCanal;

    unsigned long MAX_DELAY = 700;
    int PRODUCER_ID;

signals:
    void finished();

};


#endif // CUSTOMER_H
