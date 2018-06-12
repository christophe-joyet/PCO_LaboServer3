#include "readerwritercache.h"
#include "option.h"
#include <QDateTime>
#include <QList>
#include <QDebug>

ReaderWriterCache::ReaderWriterCache(int invalidationDelaySec, int staleDelaySec):
    invalidationDelaySec(invalidationDelaySec), staleDelaySec(staleDelaySec)
{
    timer = new InvalidationTimer(this);
    timer->start();
}

ReaderWriterCache::~ReaderWriterCache()
{
    notEnd = false; //arrête la boucle while
    timer->wait();  //attendre la fin du thread timer
    delete timer;
}

void ReaderWriterCache::putResponse(Response &response)
{
    //création du timer correspondant à la réponses qui va être mise dans la cache
    TimestampedResponse timeStamped = {response, QDateTime::currentMSecsSinceEpoch()/1000};
    //Insertion de la réponse dans la cache
    map.insert(response.getRequest().getFilePath(), timeStamped);
}

Option<Response> ReaderWriterCache::tryGetCachedResponse(Request &request) {
    Option<Response> res = Option<Response>::none();

    auto elementInCache = map.find(request.getFilePath());

    //si on a trouvé l'élément dans la cache grace au filePath
    if(elementInCache != map.end()){
        return res.some(elementInCache->response);
    }

    //si on a rien trouvé dans la cache on retourne none()
    return res;
}
