#ifndef MASTER_H
#define MASTER_H

#include <QObject>
#include <QSharedMemory>
#include <QFile>
#include <QFileDevice>
#include <qcanal.h>
#include <message.h>
#include <QTextStream>
#include <QThread>

class Master : public QObject
{
    Q_OBJECT
public:
    explicit Master(QObject *parent = nullptr);
    void toFile (QString str);

public slots:
    void run ();

private:
    QCanal *customerCanal;
    QCanal *dispatcherCanalOrder;
    QCanal *dispatcherCanalToMaster;
    QCanal *courierCanal;
    QCanal *masterCanal;
    QCanal *generalCanal;
    QCanal *storageCanal;

signals:
    void finished();
};

#endif // MASTER_H
