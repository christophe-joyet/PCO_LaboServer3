#Laboratoire PCO n°5 serveur - PARTIE 3
##Auteurs: Marc Labie & Christophe Joyet
##Date: 17 juin 2018


###1. Présentation du laboratoire:

Ce laboratoire se déroulera jusqu'à la fin du semestre. Nous devrons créer un serveur en 3 parties distinctes en utilisant pour  
chaque étape soit une implémentation avec des sémaphores soit en utilisant le moniteur de Hoare ou le moniteur de Mesa.  
Chacune de ses implémentations doivent être utilisées au moins une fois.  

###2. But - Partie 3

Dans cette partie, nous devons introduire un cache à notre système. Cette mémoire contiendra les réponses à envoyer au  
dispatcher de réponses. Chaque réponse restera un temps prédéfini dans le cache. Au bout de ce délai, le cache supprimera la  
réponse afin de libérer de l'espace. 


###3. Architecture du code

Nous avons implémenté 2 nouvelles classes :  
  
  - ReaderWriterCache
  - ReaderWriterLock

Nous avons également modifié la fonction run de notre classe RequestWorker

###3.1 ReaderWriterCache
  
Cette classe servira à gérer le cache. Grâce à une classe interne InvalidationTimer qui implémente une fonction run,  
nous pourrons gérer les données à supprimer au bout d'un certain temps dans le cache.  
Nous utilisons dans cette classe l'appel aux fonctions de la classe ReaderWriterLock afin de spécifier qui peut lire  
la donnée ou écrire (lecteurs - redacteurs) une donnée dans le cache.  

###3.2 ReaderWriterLock
  
Afin d'implémenter cette classe, nous nous sommes basés sur le moniteur de Mesa (Le dernier choix possible que nous avions).  
Nous nous avons repris les slides du cours (lecteurs - redacteurs) et avons décidé de codé la classe avec une priorité égale  
entre rédacteur et lecteurs.  
Cela nous semblait la meilleure situation afin de créer le moins de famine possible entre les lecteurs et les redacteurs.  

###3.3 RequestWorker

Nous avons changé la fonction run de cette classe.  
Le thread va donc regarder si la réponse est dans la cache avant d'appeler la fonction handle si nécessaire.  

###4. Questions partie 3

- Le cache améliore-t-il la performance et dans quels cas ?  
Nous avons pu tester le programme et nous voyons clairement que les threads sont utilisés beaucoup moins longtemps pour le traitement  
des requêtes (cf. image du processus en cours d'execution).  

S'il y a beaucoup de requêtes, beaucoup de réponses seront enregistrées dans le cache. Ainsi, les threads pourront aisemment  
trouver les réponses dans le cache et gagner beaucoup de temps à chaque requête (pas obliger d'appeler la fonction handle).  
  
- Y-a-t-il des schémas d’utilisation qui pourraient être problématiques avec votre implémentation ?  
Nous pouvons imaginer le cas où nous ferions beaucoup de requêtes et que notre mémoire arrive à saturation car  
nous ne contrôlons pas le volume de données que nous lui donnons. Nous pourrions trouver un moyen de limiter la taille de  
cette mémoire pour résoudre ce problème.  

###5. Tests

Nous avons lancé indépendamment 2 programmes. Une fois en exécutant le fileServer de base et une fois en exécutant celui implé-  
mentant le cache. Nous avons pu remarquer une très nette différence. Avec le cache, les threads travaillent beaucoup moins  
longtemps et donc chargent les données beaucoup plus rapidement.  
  
###6. Remarques

Notre partie N°2 du laboratoire ne fonctionnant pas à 100%, nous sommes repartis de la partie 1 que nous avions implémentée. 
