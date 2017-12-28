#include "server.h"
#include "data.h"

void server(int port, int range) {
    int serverSocket;
    struct sockaddr_in serverAdd;

    printf("Démarrage du serveur \n");

    //création de la socket
    serverSocket = makeSocket();

    //définition de l'adresse de reception
    serverAdd = makeSockAddrIn("", port);

    //Rattachement de la socket sur le port d'écoute
    bindSocket(serverSocket, &serverAdd);

    //On définit le nombre de clients max
    if(listen(serverSocket, MAX_CLIENTS)<0) printError("Erreur du listen()");

    printf("Configuration terminée. En attente d'une connexion... \n");

    //On commence l'échange avec les clients
    trade(serverSocket, range);
}

void trade(int serverSocket, int range) {
    int socketClient;
    struct sockaddr_in clientAdd;

    socklen_t len = sizeof(clientAdd);

    //Attente de la connexion d'un client
    socketClient = accept(serverSocket, (struct sockaddr *) &clientAdd, &len);
    
    if(fork()==0) {
        printf("Une borne s'est connectée ! \n");
        Car c;

        //reception de la plaque ou de la classe du véhicule
        char buffer[7];
        int r = recv(socketClient, &c, sizeof(Car), 0);
        printf("J'ai reçu \"%c\" !\n", c.p.category);

        //si la chaine recue est égale à 1 c'est une classe sinon c'est une plaque
        
            printf("Demande de contrat demandée pour un véhicule de classe %c\n", c.p.category);
            
            //TODO: parcourir les forfaits pour trouver les prix pour la classe
            for(int i = 0; i < sizeof(packages[range-1])/sizeof(Package); i++) {
                if(strcmp(&(packages[range-1][i].category), &(c.p.category)) == 1) {
                     c.p.price = packages[range-1][i].price;
                     c.p.out = packages[range-1][i].out;
                     c.p.duration = durationMax[range-1];
                }
            }

            printf("Prix : %f\n", c.p.price);

            send(socketClient, &c, sizeof(Car), 0);

   
            printf("Consultation de contrat pour l'immatriculation %s\n", c.matriculation);

            //TODO: parcourir les voitures stationnées pour trouver celle correspondante à la plaque
        
    } else {
        //on continue de trader avec les bornes
        trade(serverSocket, range);
    }
}