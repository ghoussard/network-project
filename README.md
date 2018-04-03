# network-project
Network project in C for my studies.

## Structure des programmes compilation et exécution

Le dossier common contient les déclarations et variables communes au serveur ainsi qu’à la
borne. Le dossier server contient le code du serveur, ainsi qu’un Makefile pour le compiler,
le dossier terminal contient lui le code de la borne avec, également, un Makefile.
Pour les compiler, faites un make dans le dossier server et le dossier terminal.

![alt text](https://image.noelshack.com/fichiers/2018/14/2/1522749487-image2.png)

Pour exécuter le serveur il faut deux arguments, le port sur lequel le serveur va se greffer
ainsi que la “gamme de données” (1, 2 ou 3) : cela permet de démarrer 3 serveurs avec des
données différentes sur chaque serveur.

Si vous n'exécutez pas les serveurs en local, pensez à modifier les adresses IP des
serveurs via la borne avant toutes communications.
Les 3 adresses IP par défaut enregistrées dans la borne sont :
127.0.0.1:8000, 127.0.0.1:8001, 127.0.0.1:8002
