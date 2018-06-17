#include "readerwritercache.h"
#include "option.h"
#include <QDateTime>
#include <QList>
#include <QDebug>

ReaderWriterCache::ReaderWriterCache(int invalidationDelaySec, int staleDelaySec):
    invalidationDelaySec(invalidationDelaySec), staleDelaySec(staleDelaySec)
{
    //Création d'un nouveau timer pour le cache
    timer = new InvalidationTimer(this);
    timer->start();
}

ReaderWriterCache::~ReaderWriterCache()
{
    notEnd = false; //arrête la boucle while
    timer->wait();  //attendre la fin du thread timer
    delete timer;   //suppression du pointeur
}

void ReaderWriterCache::putResponse(Response &response)
{
    //création du timer correspondant à la réponses qui va être mise dans la cache
    TimestampedResponse timeStamped = {response, QDateTime::currentMSecsSinceEpoch()/1000};
    lock.lockReading(); //blocage de la lecture du cache
    //Insertion de la réponse dans la cache
    map.insert(response.getRequest().getFilePath(), timeStamped); //insertion d'une réponse dans le cache
    lock.unlockReading();//libération de la lecture du cache
}

Option<Response> ReaderWriterCache::tryGetCachedResponse(Request &request) {
    lock.lockWriting(); //on bloque l'accès au rédacteur au cache
    Option<Response> res = Option<Response>::none();

    auto elementInCache = map.find(request.getFilePath());

    //si on a trouvé l'élément dans la cache grace au filePath
    if(elementInCache != map.end()){
        lock.unlockWriting(); //on débloque l'accès au rédacteur
        return res.some(elementInCache->response);
    }

    lock.unlockWriting(); //on débloque l'accès au rédacteur
    //si on a rien trouvé dans la cache on retourne none()
    return res;
}
