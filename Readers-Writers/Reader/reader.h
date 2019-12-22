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

class Reader : public QObject
{
    Q_OBJECT
public:
    explicit Reader(QObject *parent = nullptr);
    void toFile (QString str);

public slots:
    void run ();

private:
    void read ();
    QCanal *generalCanal;

    unsigned long MAX_DELAY = 700;
    int READER_ID;

signals:
    void finished();

};

#endif // CUSTOMER_H
