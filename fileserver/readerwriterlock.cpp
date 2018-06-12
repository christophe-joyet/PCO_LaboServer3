#include "readerwriterlock.h"

void ReaderWriterLock::lockReading() {
    mutexReaders.acquire();
    nbReaders++;
    while (nbReaders==1) {
      writer.acquire();
    }
    mutexReaders.release();
}

void ReaderWriterLock::unlockReading() {
    mutexReaders.acquire();
     nbReaders--;
     if (nbReaders==0) {
       writer.release();
     }
     mutexReaders.release();
}

void ReaderWriterLock::lockWriting() {
    mutexWriters.acquire();
      writer.acquire();
}

void ReaderWriterLock::unlockWriting() {
    writer.release();
      mutexWriters.release();
}
