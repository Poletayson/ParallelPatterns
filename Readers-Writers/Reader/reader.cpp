#include "reader.h"


Reader::Reader(QObject *parent) : QObject(parent)
{
    generalCanal = new QCanal("generalCanal");
    qsrand(static_cast<unsigned int>(QTime::currentTime().msec()));
    READER_ID = qrand() % 10000;    //id читателя
}

void Reader::run(){
    while(true){
        unsigned long delay = static_cast<unsigned long>(qrand()) % MAX_DELAY;
        toFile(QString ("решил подождать ") + QString::number(delay) + QString ("мс\n"));
        QThread::msleep(delay);
        generalCanal->e->acquire(); // ждем эстафету на ввод
        if(generalCanal->getNumW() > 0) {
            toFile(QString ("ждет, когда писатели закончат работу"));
            generalCanal->waitRInc();   // появился читатель
            generalCanal->e->release();
            generalCanal->r->acquire(); // ждем эстафету на чтение
        }
        generalCanal->numRInc();
        generalCanal->estafeta();   //эстафету получили – работаем!

        read();

        generalCanal->e->acquire(); //  ждем эстафету  -  отметить конец работы
        generalCanal->numRDec();
        generalCanal->estafeta();
       }
}

void Reader::read()
{
    toFile(QString ("считал данные: ") + QString::number(generalCanal->getData()));
}

void Reader::toFile(QString str)
{
    QFile File (QString("Reader_") + QString::number(READER_ID) + QString(".txt"));
    while (!File.open(QFile::Append));
    QTextStream stream (&File);
    stream << QString("читатель_") << QString::number(READER_ID) << QString(": ") + str + QString("\n");
    stream.flush();
    File.close();
}
