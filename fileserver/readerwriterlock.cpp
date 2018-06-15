#include "readerwriterlock.h"

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
}
