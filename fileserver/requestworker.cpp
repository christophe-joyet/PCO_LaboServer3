#include "requestworker.h"
#include "requesthandler.h"
#include "readerwritercache.h"


RequestWorker::~RequestWorker(){

}

void RequestWorker::run(){

    //vérification que la reponse n'est pas dans le cache
    if(cache->tryGetCachedResponse(this->request).hasValue()){
        //si la réponse est dans le cache, on la met directement dans le dispatcher de réponse
        this->responses->put(cache->tryGetCachedResponse(this->request).value());
    } else{
        //sinon on appelle la fonction handle
        RequestHandler rh(this->request, this->hasDebugLog);
        Response response = rh.handle();
        this->responses->put(response);
        //On met la réponse dans le cache pour une utilisation future
        cache->putResponse(response);
    }


}
