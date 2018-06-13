#include "readerwriterlock.h"

void ReaderWriterLock::lockReading() {
    fifo.acquire();
    mutex.acquire();
    nbReaders++;
    if (nbReaders==1) {
       //isFree.wait(&mutexReaders);
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
