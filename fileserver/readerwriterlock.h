#ifndef READERWRITERLOCK_H
#define READERWRITERLOCK_H

#include <QSemaphore>
#include <QWaitCondition>

//Nous sommes partis sur une implémentation de priorité égale comme vu dans le cours

class ReaderWriterLock
{

protected:
    QSemaphore mutex; //pour garantir l'exclusion mutuelle
    QSemaphore fifo;
    QSemaphore writer;
    bool isCacheFree;
    QWaitCondition cond;
    int nbReaders;

public:
    ReaderWriterLock():
        mutex(1),
        fifo(1),
        writer(1),
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
