#ifndef READERWRITERLOCK_H
#define READERWRITERLOCK_H

#include <QSemaphore>
#include <QWaitCondition>

//Nous sommes partis sur une implémentation de priorité au lecteur en reprenant
//la structure du cours

class ReaderWriterLock
{

protected:
    QSemaphore mutexReaders;
    QSemaphore mutexWriters;
    QSemaphore writer;
   // QWaitCondition isReading;
    int nbReaders;

public:
    ReaderWriterLock():
        mutexReaders(1),
        mutexWriters(1),
        writer(1),
       // isReading(false),
        nbReaders(0){}

    /**
     * @brief lockReading : Permet de bloquer la lecture dans la cache
     */
    void lockReading();

    /**
     * @brief lockWriting : Permet de bloquer l'écriture dans la cache
     */
    void lockWriting();
    void unlockReading();
    void unlockWriting();
};

#endif // READERWRITERLOCK_H
