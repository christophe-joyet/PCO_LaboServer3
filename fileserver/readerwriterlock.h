//Mesa
#ifndef READERWRITERLOCK_H
#define READERWRITERLOCK_H

#include <QSemaphore>
#include <QWaitCondition>
#include <QMutex>

//Nous sommes partis sur une implémentation de priorité égale comme vu dans le cours

class ReaderWriterLock
{

protected:
    QMutex mutex; //pour garantir l'exclusion mutuelle
    bool isCacheFree;
    QWaitCondition waitNoWriters;
    QWaitCondition waitNoReaders;
    int nbReaders;
    int nbWriters;

public:
    ReaderWriterLock():
        mutex(),
        nbReaders(0),
        nbWriters(0),
        waitNoReaders(),
        waitNoWriters(){}

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

