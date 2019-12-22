#include "ConsProd.h"

/*
 *
 * ПОТРЕБИТЕЛЬ
 *
 */

Consumer::Consumer(int id, QObject *parent) : QObject(parent)
{
    generalCanal = new QCanal("generalCanal");
    CONSUMER_ID = id; //qrand() % 4999;    //id читателя
}

void Consumer::run(){
    qDebug() << "[Потребитель " << CONSUMER_ID << "] thread started";
    while(true){
        unsigned long delay = static_cast<unsigned long>(qrand()) % MAX_DELAY + 1000 + CONSUMER_ID * 220;
        qDebug() << "[Потребитель " << CONSUMER_ID << "] решил подождать " <<  delay << "мс...";
        QThread::msleep(delay);

//        if (orderCount >= ORDER_MAX){
//            qDebug() << "Заказов - "<< orderCount <<" [Потребитель " << CONSUMER_ID << "] ждет своей очереди сделать заказ";
//            while (orderCount >= ORDER_MAX);
//        }
        qmt.lock();
        ++orderCount;
        qDebug() << "[Потребитель " << CONSUMER_ID << "] сделал заказ";
        conditionProducers.wakeOne();   //будим производителя
        condition.wait(&qmt);       //а сами будем ждать

        --storage;

        qDebug() << "[Потребитель " << CONSUMER_ID << "] получил заказ";
        qmt.unlock();

       }
}

void Consumer::consume()
{
    toFile(QString ("считал данные: ") + QString::number(generalCanal->getData()));
}

void Consumer::toFile(QString str)
{
    QFile File (QString("Reader_") + QString::number(CONSUMER_ID) + QString(".txt"));
    while (!File.open(QFile::Append));
    QTextStream stream (&File);
    stream << QString("читатель_") << QString::number(CONSUMER_ID) << QString(": ") + str + QString("\n");
    stream.flush();
    File.close();
}

/*
 *
 * ПРОИЗВОДИТЕЛЬ
 *
 */

Producer::Producer(int id, QObject *parent) : QObject(parent)
{
    ORDER_MAX++;
    generalCanal = new QCanal("generalCanal");
    PRODUCER_ID = id;//qrand() % 4999 + 5000;    //id
}

void Producer::run(){
    qDebug() << "[Производитель " << PRODUCER_ID << "] thread started";
    while(true){
//        unsigned long delay = static_cast<unsigned long>(qrand()) % MAX_DELAY;
//        //toFile(QString ("решил подождать ") + QString::number(delay) + QString ("мс\n"));
//        QThread::msleep(delay);

        if (orderCount == 0)
            qDebug() << "[Производитель " << PRODUCER_ID << "] засыпает, так как заказов пока нет";
        mutexProducers.lock();          //пытаемся заблокировать мьютекс и становимся в ожидание заказа
        conditionProducers.wait(&mutexProducers);
        mutexProducers.unlock();
        qDebug() << "[Производитель " << PRODUCER_ID << "] начал выполнять задание ";

        qmt.lock();     //блокируем мьютекс
        //while (storage > ORDER_MAX);

        QThread::msleep(PROD_DELAY);

        qDebug() << "[Производитель " << PRODUCER_ID << "] закончил выполнять задание ";
        ++storage;
        condition.wakeOne();
        qmt.unlock();
        --orderCount;
    }
}

void Producer::produce()
{
    toFile(QString ("произвел товар ") + QString::number(generalCanal->getData()));
}

void Producer::toFile(QString str)
{
    QFile File (QString("Producer_") + QString::number(PRODUCER_ID) + QString(".txt"));
    while (!File.open(QFile::Append));
    QTextStream stream (&File);
    stream << QString("производитель_") << QString::number(PRODUCER_ID) << QString(": ") + str + QString("\n");
    stream.flush();
    File.close();
}
