#ifndef REQUESTWORKER_H
#define REQUESTWORKER_H

#include <QThread>
#include "abstractbuffer.h"
#include "request.h"
#include "response.h"
#include "readerwritercache.h"

class RequestWorker : public QThread
{
public:
    RequestWorker(AbstractBuffer<Response>* responses, Request request, bool hasDebugLog, ReaderWriterCache* cache): responses(responses), request(request), hasDebugLog(hasDebugLog), cache(cache) {}
    ~RequestWorker();

protected:
    void run();

private:

    AbstractBuffer<Response>* responses;
    ReaderWriterCache* cache;
    Request request;
    bool hasDebugLog;

};

#endif // REQUESTWORKER_H
