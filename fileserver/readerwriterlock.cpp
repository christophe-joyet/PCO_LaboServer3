/*#include "readerwriterlock.h"

//Sémantique reprise du cours lecteur - redacteur priorité égale
void ReaderWriterLock::lockReading() {
    fifo.acquire();
    mutex.acquire();
    nbReaders++;
    if (nbReaders==1){
        writer.acquire();
    }
    mutex.release();
    fifo.release();
}

void ReaderWriterLock::unlockReading() {
    mutex.acquire();
    nbReaders -= 1;
    if (nbReaders==0) {
        writer.release();
    }
    mutex.release();
}

void ReaderWriterLock::lockWriting() {
    mutex.acquire();

    fifo.acquire();
    writer.acquire();

    mutex.release();
}

void ReaderWriterLock::unlockWriting() {
    mutex.acquire();

    writer.release();
    fifo.release();

    mutex.release();
}*/

//Mesa
#include "readerwriterlock.h"

//Sémantique reprise du cours lecteur - redacteur priorité égale
void ReaderWriterLock::lockReading() {
    //fifo.acquire();
    mutex.lock();
    //nbReaders++;

    while(nbWriters != 0){
        waitNoWriters.wait(&mutex);
    }
    //writers.lock();
    nbReaders++;

    /*if (nbReaders==1){
        writer.acquire();
    }*/
    mutex.unlock();
}

void ReaderWriterLock::unlockReading() {
    mutex.lock();
    nbReaders--;
    // On réveil tous les rédacteur, au cas où il n'y
    // aurait plus de rédacteur.
    waitNoReaders.wakeAll();
    /*if (nbReaders==0) {
        writer.release();
    }*/
    mutex.unlock();
}

void ReaderWriterLock::lockWriting() {
    mutex.lock();

    while (nbWriters != 0 || nbReaders != 0) {
        if(nbWriters != 0)
            waitNoWriters.wait(&mutex);

        if(nbReaders != 0)
            waitNoReaders.wait(&mutex);
    }

    nbWriters++;

    /*fifo.acquire();
    writer.acquire();*/

    mutex.unlock();
}

void ReaderWriterLock::unlockWriting() {
    mutex.lock();


    nbWriters--;
    waitNoWriters.wakeAll();
    /*writer.release();
    fifo.release();*/

    mutex.unlock();
}

