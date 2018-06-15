#include "readerwriterlock.h"

void ReaderWriterLock::lockReading() {
    fifo.acquire();
    mutex.acquire();
    nbReaders++;
    while (nbReaders==1){
        //isCacheFree.wait(&mutex); // on attend qu'il n'y ait plus de lecteurs
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
    fifo.acquire();
    writer.acquire();
}

void ReaderWriterLock::unlockWriting() {
    writer.release();
    fifo.release();
}
