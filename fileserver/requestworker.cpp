#include "requestworker.h"
#include "requesthandler.h"


RequestWorker::~RequestWorker(){

}

void RequestWorker::run(){
    RequestHandler rh(this->request, this->hasDebugLog);
    this->responses->put(rh.handle());
}
