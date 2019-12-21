#include "master.h"

Master::Master(QObject *parent) : QObject(parent)
{
    customerCanal = new QCanal("customerCanal");
    dispatcherCanalOrder = new QCanal("dispatcherCanalOrder");
    courierCanal = new QCanal("courierCanal");
    masterCanal = new QCanal("masterCanal");
    generalCanal = new QCanal("generalCanal");
    dispatcherCanalToMaster = new QCanal("dispatcherCanalToMaster");
    storageCanal = new QCanal("storageCanal");
}


void Master::run()
{
    while (true) {
        //пока в канал мастера не поступит заказ
        while (masterCanal->getIsEmpty());
        QThread::msleep(Message::DELAY);

        if (masterCanal->get().getType() == Message::MAKE_ORDER){
            toFile("получил заказ");
            storageCanal->put(Message::MATERIALS_REQUEST, QVariant("Стул"));    //запрашивает у склада
            toFile("запросил материалы");
            //ждем отказ или материалы
            while (masterCanal->get().getType() != Message::MATERIALS_ARE && masterCanal->get().getType() != Message::MATERIALS_ARE_NOT);
            QThread::msleep(Message::DELAY);
            //материалы поступили
            if (masterCanal->get().getType() == Message::MATERIALS_ARE){

                courierCanal->put(Message::ORDER_COMPLETE, QVariant("Стул"));    //заказ готов, курьер должен забрать
                toFile("передал заказ курьеру");
                masterCanal->unlockCanal();
            }
            else {
                dispatcherCanalOrder->put(Message::REJECTION, QVariant("Стул"));    //передает отказ
                toFile("передал отказ");
                masterCanal->unlockCanal();
            }
        }
        else{
            toFile("Что-то не то: ");
        }
    }

}

void Master::toFile(QString str)
{
    QFile File ("out.txt");
    while (!File.open(QFile::Append));
    QTextStream stream (&File);
    stream <<"Мастер: " + str + "\n";
    File.close();
}
