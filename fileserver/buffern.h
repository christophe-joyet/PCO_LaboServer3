#ifndef BUFFERN_H
#define BUFFERN_H

#include "abstractbuffer.h"
#include <QSemaphore>

const int NoInitTamponN = 10;

//Implementation reprise du cours de PCO 
template<typename T> class BufferN : public AbstractBuffer<T> {
protected:
    T *elements;
    int writePointer, readPointer, nbElements, bufferSize;
    QSemaphore mutex, waitProd, waitConso;
    unsigned nbWaitingProd, nbWaitingConso;

public:

    BufferN(unsigned int size) : mutex(1) {
        if ((elements = new T[size]) != 0) {
            writePointer = readPointer = nbElements = 0;
            nbWaitingProd = nbWaitingConso = 0;
            bufferSize = size;
            return;
        }
        // Exception
        throw NoInitTamponN;
    }

    virtual ~BufferN() {}

    virtual void put(T item) {
        mutex.acquire();
        if (nbElements == bufferSize) {
            nbWaitingProd += 1;
            mutex.release();
            waitProd.acquire();
        }
        elements[writePointer] = item;
        writePointer = (writePointer + 1)
                       % bufferSize;
        nbElements ++;
        if (nbWaitingConso > 0) {
            nbWaitingConso -= 1;
            waitConso.release();
        }
        else {
            mutex.release();
        }
    }

    virtual T get(void) {
        T item;
        mutex.acquire();
        if (nbElements == 0) {
            nbWaitingConso += 1;
            mutex.release();
            waitConso.acquire();
        }
        item = elements[readPointer];
        readPointer = (readPointer + 1)
                      % bufferSize;
        nbElements --;
        if (nbWaitingProd > 0) {
            nbWaitingProd -= 1;
            waitProd.release();
        }
        else {
            mutex.release();
        }
        return item;
    }
};

#endif // BUFFERN_H
