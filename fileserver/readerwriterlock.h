//Mesa
#ifndef READERWRITERLOCK_H
#define READERWRITERLOCK_H

#include <QSemaphore>
#include <QWaitCondition>
#include <QMutex>

//Nous sommes partis sur une implémentation de priorité égale lecteurs - redacteurs comme vu dans le cours

class ReaderWriterLock
{

protected:
    QMutex mutex; //pour garantir l'exclusion mutuelle
    int nbReaders;
    int nbWriters;
    QWaitCondition waitNoReaders;
    QWaitCondition waitNoWriters;


public:
    ReaderWriterLock():
        mutex(),
        nbReaders(0),
        nbWriters(0),
        waitNoReaders(),
        waitNoWriters(){}

    /**
     * @brief lockReading : Permet de bloquer la lecture dans le cache
     */
    void lockReading();

    /**
     * @brief lockWriting : Permet de bloquer l'écriture dans le cache
     */
    void lockWriting();

    /**
     * @brief unlockReading : Permet de débloquer la lecture dans le cache
     */
    void unlockReading();

    /**
     * @brief unlockWriting : Permet de débloquer l'écriture dans le cache
     */
    void unlockWriting();
};

#endif // READERWRITERLOCK_H

