#Laboratoire PCO n°5 serveur
##Auteurs: Marc Labie & Christophe Joyet
##Date: 23 Mai 2018


###Présentation du laboratoire:

Ce laboratoire se déroulera jusqu'à la fin du semestre. Nous devrons créer un serveur en 3 parties distinctes en utilisant pour  
chaque étape soit une implémentation avec des sémaphores soit en utilisant le moniteur de Hoare ou le moniteur de Mesa.  
Chacune de ses implémentations doivent être au moins utilisées une fois.  

###But:

Dans la première partie, nous devrons réaliser un serveur qui supportera le traitement de requêtes simulatinées. Nous utiliserons  
la méthode producteur-consommateur comme vu dans le cours.  

Dans la seconde partie, nous devrons introduire une threadpool afin de contrôler le flux des requêtes.  

Enfin, dans la troisième et dernière partie, nous devrons gêrer l'ajout d'une mémoire cache.  

###Architecture du code:
####Général

Nous avons créé la classe BufferN héritant de la classe AbstractBuffer en se référant aux slides du cours.  
Cette classe contient 2 méthodes put() et get() qui permettent de prendre des données et en mettre dans un tampon.

####Partie 1

Après avoir créé et implémenté la classe RequestDispatcherThread, nous avons décider de créer une classe RequestWorker. Cette  
classe, héritant de la classe Thread, permet de récupérer une requête du RequestDispatcherThread et de remplir le  
ResponseDispatcherThread. Pour cela, la classe RequestWorker créé un objet RequestHandler et appelle la fonction handle de la  
classe RequestHandler qui permettra de mettre une reponse dans le buffer qui contient les réponses.  
  
Afin de ne pas créer des threads à l'infini, la classe RequestDispatcherThread dispose d'une liste des threads qu'elle créée.  
Ainsi à chaque fois que la méthode run() est lancée, nous vérifions si les threads sont terminés à l'aide de la méthode  
isFinished() et si c'est le cas, nous detruisons le thread et nous l'enlevons de la liste. 

###Tests
####Partie 1
Aucun test de performance n'a été effectué pour cette partie, néamoins nous avons mis quelques annotations quant au  
fonctionnement de cette première partie dans les remarques.  

###Remarques

####Partie 1
Le serveur est rapidement surchargé et plante lorsque le nombre de requêtes devient trop conséquent.  
De plus, nous ne controlons pas la quantité de threads pouvant être créés.  
Il se peut que s'il y en a un trop grand nombre, cela entraine un nombre de changement de contexte trop important.  
Il serait probablement plus judicieux de définir un nombre de threads approprié au nombre disponible sur le CPU pour permettre à une tâche de se terminer avant d'en traiter une autre.