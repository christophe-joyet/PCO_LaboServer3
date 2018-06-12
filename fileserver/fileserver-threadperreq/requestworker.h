#ifndef REQUESTWORKER_H
#define REQUESTWORKER_H

#include <QThread>
#include "abstractbuffer.h"
#include "request.h"
#include "response.h"

class RequestWorker : public QThread
{
public:
    RequestWorker(AbstractBuffer<Response>* responses, Request request, bool hasDebugLog): responses(responses), request(request), hasDebugLog(hasDebugLog) {}
    ~RequestWorker();

protected:
    void run();

private:

    AbstractBuffer<Response>* responses;
    Request request;
    bool hasDebugLog;
};

#endif // REQUESTWORKER_H
