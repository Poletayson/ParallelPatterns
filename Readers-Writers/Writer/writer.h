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
    QCanal *generalCanal;

    void write ();

    unsigned long MAX_DELAY = 700;
    int WRITER_ID;

signals:
    void finished();

};

#endif // CUSTOMER_H
