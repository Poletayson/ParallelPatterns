#ifndef QCANAL_H
#define QCANAL_H

#include <QObject>
#include <QSharedMemory>
#include <QSystemSemaphore>
#include <message.h>

class QCanal : public QSharedMemory
{
public:
    QCanal();
    QCanal(QString key);
    bool put (int d);    //поместить сообщение в канал
    int get ();       //получить сообщение из канала
    void lockCanal ();
    void unlockCanal ();
    bool getIsEmpty();
    void estafeta();

    int getNumW();
    void setNumW(int value);

    int getNumR();
    void setNumR(int value);

    int getWaitW();
    void setWaitW(int value);

    int getWaitR();
    void setWaitR(int value);

private:
    bool isEmpty;
    int numW, numR, waitW, waitR;
    QSystemSemaphore *e, *r, *w;
    Message* message;   //сообщение, содержащееся в канале
};

#endif // QCANAL_H
