#include "reader.h"

Reader::Reader(QObject *parent) : QObject(parent)
{
//    customerCanal = new QCanal("customerCanal");
//    dispatcherCanalOrder = new QCanal("dispatcherCanalOrder");
//    courierCanal = new QCanal("courierCanal");
    generalCanal = new QCanal("generalCanal");
}

void Reader::run(){
//    toFile(dispatcherCanalOrder->key() + " " + QString(dispatcherCanalOrder->isAttached()));
     //ORDER_COUNT;
    while(true){
        e.P(); // ждем эстафету на ввод
        if(numW>0 ) {waitR++; // появился читатель
            e.V(); r.P(); // ждем эстафету на чтение
             }
             numR++;
             estafeta();   //эстафету получили – работаем!
            <read data>
            e.P(); //  ждем эстафету  -  отметить конец работы
            numR--;
           estafeta();
       }

//    for (int counter = 0; counter < ORDER_COUNT; counter++) {


//        //ждем пока канал непуст
//        while (!dispatcherCanalOrder->getIsEmpty());
//        QThread::msleep(Message::DELAY);
//        dispatcherCanalOrder->put(Message::MAKE_ORDER, QVariant("Стул"));   //делаем заказ
//        toFile("\nзаказал стул");
//        customerCanal->unlockCanal();

//        while (customerCanal->getIsEmpty());
//        QThread::msleep(Message::DELAY);
//        if (customerCanal->get().getType() == Message::REJECTION)
//            toFile("получил отказ");
//        else if(customerCanal->get().getType() == Message::ORDER_COMPLETE){
//            toFile("получил готовый заказ");
//            courierCanal->put(Message::MONEY_TRANSFER, QVariant(""));   //делаем заказ
//            toFile("передал деньги");
//        }
//        customerCanal->unlockCanal();
//    }
}

void Reader::toFile(QString str)
{
    QFile File ("Customer.txt");
    while (!File.open(QFile::Append));
    QTextStream stream (&File);
    stream <<"Заказчик: " + str + "\n";
    File.close();
}
