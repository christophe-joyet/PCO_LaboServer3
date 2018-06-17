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
                        cache->lock.lockReading(); //on bloque l'accès aux lecteurs
                        it = cache->map.erase(it); //erase retourne le prochain iterateur
                        cache->lock.unlockReading();//on libère l'accès aux lecteurs
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

    /**
     * @brief ReaderWriterCache : Constructeur
     * @param invalidationDelaySec : definit l'intervalle entre deux verifications
     * @param staleDelaySec : temps après lequel une donnée est considérée comme obsolète
     */
	ReaderWriterCache(int invalidationDelaySec, int staleDelaySec);

    /**
      * @brief ~ReaderWriterCache : Destructeur
      */
    ~ReaderWriterCache();

    /**
     * @brief tryGetCachedResponse : Permet de regarder si une réponse est déjà dans le cache
     * @param request
     * @return S'il y a une réponse de disponible alors retourne cette réponse
     */
	Option<Response> tryGetCachedResponse(Request& request);

    /**
     * @brief putResponse : Permet de mettre une réponse dans le cache
     * @param response
     */
	void putResponse(Response& response);
};

#endif // READERWRITERCACHE_H
