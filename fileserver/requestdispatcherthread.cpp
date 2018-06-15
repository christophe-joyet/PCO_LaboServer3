#include "requestdispatcherthread.h"
#include "request.h"
#include "requestworker.h"
#include <QDebug>

void RequestDispatcherThread::run()
{
    while(true) {

        //boucle qui permet de terminer un workerThread si celui-ci a fini son execution
        if (hasDebugLog)
            qDebug() << "Waiting for requests...";
        Request req = requests->get();   // block until a request is available

        // Création d'un worker threadé qui va s'occuper de gérer les requête
        RequestWorker* rw = new RequestWorker(responses,req,hasDebugLog, cache);

        // On ajoute le request worker à la liste des request worker en cours
        // d'execution pour pouvoir les delete une fois terminé.
        ptrListOnRW.append(rw);

        rw->start();

        //boucle qui permet de terminer un workerThread si celui-ci a fini son execution
        for(RequestWorker* tmp : ptrListOnRW){
            if(tmp->isFinished()){
               ptrListOnRW.removeOne(tmp);
               delete tmp;
            }
        }


    }
}
