#ifndef REQUESTDISPATCHERTHREAD_H
#define REQUESTDISPATCHERTHREAD_H
#include <QObject>
#include <QThread>
#include <QDebug>
#include "abstractbuffer.h"
#include "request.h"
#include "response.h"
#include "requestworker.h"
#include "readerwritercache.h"

class RequestDispatcherThread: public QThread
{
    Q_OBJECT

public:
    RequestDispatcherThread(AbstractBuffer<Request>* requests, AbstractBuffer<Response>* responses,bool hasDebugLog, int invalidationDelaySec, int staleDelaySec): requests(requests), responses(responses), hasDebugLog(hasDebugLog) {
        if (hasDebugLog)
            qDebug() << "Created request dispatcher thread";
        qRegisterMetaType<Request>("Request");

        cache = new ReaderWriterCache(invalidationDelaySec,staleDelaySec); //création du cache
    }

protected:
    void run();

private:
    AbstractBuffer<Request>* requests;
    AbstractBuffer<Response>* responses;
    bool hasDebugLog;
    QList<RequestWorker*> ptrListOnRW; //liste de pointeurs sur les request worker
    ReaderWriterCache* cache;

signals:
    void requestReady(Request request);
};

#endif // REQUESTDISPATCHERTHREAD_H
