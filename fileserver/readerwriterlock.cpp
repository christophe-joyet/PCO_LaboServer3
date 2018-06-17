//Mesa
#include "readerwriterlock.h"

//Sémantique reprise du cours lecteur - redacteur priorité égale
void ReaderWriterLock::lockReading() {

    mutex.lock();

    // On attend qu'aucun rédacteur soit en train d'écrire dans la cache.
    while(nbWriters != 0){
        waitNoWriters.wait(&mutex);
    }

    // On incrémente le nombre de lecteur
    nbReaders++;

    mutex.unlock();
}

void ReaderWriterLock::unlockReading() {
    mutex.lock();
    // On décrémente le nombre de lecteur
    nbReaders--;

    // On réveil les potentiels rédacteurs en attente
    waitNoReaders.wakeAll();

    mutex.unlock();
}

void ReaderWriterLock::lockWriting() {
    mutex.lock();

    // On attend qu'aucun lecteur ou rédacteur échange avec la cache.
    while (nbWriters != 0 || nbReaders != 0) {
        // S'il y a au moins un rédacteur, on attend qu'il aie terminé.
        if(nbWriters != 0)
            waitNoWriters.wait(&mutex);

        // S'il y a au moins un lecteur, on attend qu'il aie terminé.
        if(nbReaders != 0)
            waitNoReaders.wait(&mutex);
    }

    // Une fois qu'il ne reste plus aucun rédacteur ni lecteur, on incrémente
    // le nombre de rédacteur.
    nbWriters++;

    mutex.unlock();
}

void ReaderWriterLock::unlockWriting() {
    mutex.lock();

    // On décrémente le nombre de rédacteur
    nbWriters--;

    // On réveil les potentiels rédacteur et lecteur en attente
    waitNoWriters.wakeAll();

    mutex.unlock();
}

