#ifndef READERWRITERCACHE_H
#define READERWRITERCACHE_H
#include <QHash>
#include <QThread>
#include <QMutex>
#include <QDateTime>
#include "option.h"
#include "request.h"
#include "response.h"
#include "readerwriterlock.h"

class ReaderWriterCache
{
private:
	struct TimestampedResponse {
		Response response;
		long timestamp;
	};

	class InvalidationTimer: public QThread {
		friend ReaderWriterCache;

	private:
		ReaderWriterCache* cache;

	public:
		InvalidationTimer(ReaderWriterCache* cache): cache(cache) {}

	protected:
		void run() {
            while(cache->notEnd){
                //temps de vérification entre deux intervalles
                sleep(cache->invalidationDelaySec);
                //vérification si le temps est dépassé pour toutes les données contenue dans la cache
                for(auto it = cache->map.begin(); it != cache->map.end();){
                    //Si le temps courant est > ou = au temps enregistré + le delay accordé
                    if(QDateTime::currentMSecsSinceEpoch()/1000 >= it->timestamp + cache->staleDelaySec){
                        it = cache->map.erase(it); //erase retourne le prochain iterateur
                    }else {
                        ++it;
                    }
                }
            }
		}
	};

    QHash<QString, TimestampedResponse> map; //mémoire cache
    int invalidationDelaySec; //definit l'intervalle entre deux verifications
    int staleDelaySec; // temps après lequel une donnée est considérée comme obsolète
	InvalidationTimer* timer;
	ReaderWriterLock lock;
    bool notEnd = true;

public:
	ReaderWriterCache(int invalidationDelaySec, int staleDelaySec);
    ~ReaderWriterCache();

	Option<Response> tryGetCachedResponse(Request& request);
	void putResponse(Response& response);
};

#endif // READERWRITERCACHE_H
