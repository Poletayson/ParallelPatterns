#include "writer.h"


Writer::Writer(QObject *parent) : QObject(parent)
{
    generalCanal = new QCanal("generalCanal");
    qsrand(static_cast<unsigned int>(QTime::currentTime().msec()));
    WRITER_ID = qrand() % 10000;    //id читателя
}

void Writer::run(){
    while(true){
        unsigned long delay = static_cast<unsigned long>(qrand()) % MAX_DELAY + 500;
        toFile(QString ("решил подождать ") + QString::number(delay) + QString ("мс\n"));
        QThread::msleep(delay);
        generalCanal->e->acquire(); // ждем эстафету на ввод
        if(generalCanal->getNumW() > 0 || generalCanal->getNumR() > 0) {
            toFile(QString ("ждет своей очереди"));
            generalCanal->waitWInc();   // появился еще один писатель
            generalCanal->e->release();
            generalCanal->w->acquire(); // ждем эстафету на запись
        }
        generalCanal->numWInc();
        generalCanal->estafeta();   //эстафету получили – работаем!

        write();

        generalCanal->e->acquire(); //  ждем эстафету  -  отметить конец работы
        generalCanal->numWDec();
        generalCanal->estafeta();
       }
}

void Writer::write()
{
    QThread::msleep(static_cast<unsigned long>(qrand()) % 100 + 50);
    generalCanal->put(WRITER_ID);
    toFile(QString ("записал данные: ") + QString::number(generalCanal->getData()));
}

void Writer::toFile(QString str)
{
    QFile File (QString("Writer_") + QString::number(WRITER_ID) + QString(".txt"));
    while (!File.open(QFile::Append));
    QTextStream stream (&File);
    stream << QString("писатель_") << QString::number(WRITER_ID) << QString(": ") + str + QString("\n");
    stream.flush();
    File.close();
}
