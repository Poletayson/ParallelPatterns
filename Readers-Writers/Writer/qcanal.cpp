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
    int *to = &((int*)data())[5];
    memcpy(to, &d, sizeof (int));
    unlock();
    return true;
}

int QCanal::getData()
{
    return ((int*)data())[5];
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
            waitWDec();
            //setWaitW(getWaitW() - 1);
            w->release();  // работа писателя
       }
       else if ( (getNumW() == 0) && (getWaitW() == 0) && (getWaitR() > 0) ) {
           waitRDec();
           //setWaitR(getWaitR() - 1);
           r->release();   // читатель
       }
       else {
           e->release();    // запрос ввода
    }
}


int QCanal::getNumW(){
    return ((int*)data())[0];
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
    return ((int*)data())[1];
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
    return ((int*)data())[2];
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
    return ((int*)data())[3];
}

 void QCanal::setWaitR(int value){
     lock();
     isEmpty = false;
     int *to = &((int*)data())[3];
     memcpy(to, &value, sizeof (int));
     unlock();
     waitR = value;
 }

void QCanal::numWInc()
{
    lock();
    int d = ((int*)data())[0] + 1;  //читаем и прибавляем
    int *to = (int*)data();
    memcpy(to, &d, sizeof (int));   //записываем
    unlock();
}

void QCanal::numWDec()
{
    lock();
    int d = ((int*)data())[0] - 1;  //читаем и вычитаем
    int *to = (int*)data();
    memcpy(to, &d, sizeof (int));   //записываем
    unlock();
}

void QCanal::numRInc()
{
    lock();
    int d = ((int*)data())[1] + 1;  //читаем и прибавляем
    int *to = &((int*)data())[1];
    memcpy(to, &d, sizeof (int));   //записываем
    unlock();
}

void QCanal::numRDec()
{
    lock();
    int d = ((int*)data())[1] - 1;  //читаем и вычитаем
    int *to = &((int*)data())[1];
    memcpy(to, &d, sizeof (int));   //записываем
    unlock();
}

void QCanal::waitWInc()
{
    lock();
    int d = ((int*)data())[2] + 1;  //читаем и прибавляем
    int *to = &((int*)data())[2];
    memcpy(to, &d, sizeof (int));   //записываем
    unlock();
}

void QCanal::waitWDec()
{
    lock();
    int d = ((int*)data())[2] - 1;  //читаем и вычитаем
    int *to = &((int*)data())[2];
    memcpy(to, &d, sizeof (int));   //записываем
    unlock();
}

void QCanal::waitRInc()
{
    lock();
    int d = ((int*)data())[3] + 1;  //читаем и прибавляем
    int *to = &((int*)data())[3];
    memcpy(to, &d, sizeof (int));   //записываем
    unlock();
}

void QCanal::waitRDec()
{
    lock();
    int d = ((int*)data())[3] - 1;  //читаем и вычитаем
    int *to = &((int*)data())[3];
    memcpy(to, &d, sizeof (int));   //записываем
    unlock();
}
