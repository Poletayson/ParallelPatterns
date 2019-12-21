#include "qcanal.h"

QCanal::QCanal():QSharedMemory()
{
    isEmpty = true;
    put(Message::EMPTY);
}

QCanal::QCanal(QString key):QSharedMemory(key)
{
    e = new QSystemSemaphore ("e", 1);
    w = new QSystemSemaphore ("w", 0);
    r = new QSystemSemaphore ("r", 0);
    isEmpty = true; //и
    if (create(2048))
       put(Message::EMPTY);
    else
        attach();
}

bool QCanal::put(int d)
{
    lock();
    isEmpty = false;
    int *to = &((int*)data())[5];
    memcpy(to, &d, sizeof (int));
    unlock();
    return true;
}

int QCanal::get()
{
    void *dataPointer = data();
    return ((int*)dataPointer)[5];
}

void QCanal::lockCanal()
{

}

void QCanal::unlockCanal()
{
    put(Message::EMPTY);
}

bool QCanal::getIsEmpty()
{
    attach();
    lock();
    void *dataPointer = data();
    int val = ((int*)dataPointer)[0];
    unlock();

    return val == Message::EMPTY ? true : false;

}

void QCanal::estafeta() {
    if ( ((getNumW() > 0)  ||   (getNumR() > 0) ) &&  (getWaitW() > 0) ){
        e->release(); // завершить читателей или писателя
       }
       else if ( (getNumR() == 0) && (getNumW() == 0)  &&  (getWaitW() > 0)) {
            setWaitW(getWaitW() - 1);
            w->release();  // работа писателя
       }
       else if ( (getNumW() == 0) && (getWaitW() == 0) && (getWaitR() > 0) ) {
           setWaitR(getWaitR() - 1);
           r->release();   // читатель
       }
       else {
           e->release();    // запрос ввода
       }
}


int QCanal::getNumW(){
    void *dataPointer = data();
    return ((int*)dataPointer)[0];

}

void QCanal::setNumW(int value){
     lock();
     isEmpty = false;
     int *to = (int*)data();
     memcpy(to, &value, sizeof (int));
     unlock();
     numW = value;
}

int QCanal::getNumR(){
    void *dataPointer = data();
    return ((int*)dataPointer)[1];
}

 void QCanal::setNumR(int value){
     lock();
     isEmpty = false;
     int *to = &((int*)data())[1];
     memcpy(to, &value, sizeof (int));
     unlock();
     numR = value;
}

int QCanal::getWaitW(){
    void *dataPointer = data();
    return ((int*)dataPointer)[2];
}

void QCanal::setWaitW(int value){
    lock();
    isEmpty = false;
    int *to = &((int*)data())[2];
    memcpy(to, &value, sizeof (int));
    unlock();
    waitW = value;
}

int QCanal::getWaitR(){
    void *dataPointer = data();
    return ((int*)dataPointer)[3];
}

 void QCanal::setWaitR(int value){
     lock();
     isEmpty = false;
     int *to = &((int*)data())[3];
     memcpy(to, &value, sizeof (int));
     unlock();
     waitR = value;
}
