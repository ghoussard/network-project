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

        //reception de la plaque ou de la classe du véhicule
        char buffer[7];
        int r = read(socketClient, buffer, 7);
        printf("J'ai reçu \"%s\" de taille %d !\n",buffer, (int)strlen(buffer));

        //si la chaine recue est égale à 1 c'est une classe sinon c'est une plaque
        if((int)strlen(buffer)==1) {
            printf("Demande de contrat demandée pour un véhicule de classe %s\n", buffer);
            
            //TODO: parcourir les forfaits pour trouver les prix pour la classe

        } else {
            printf("Consultation de contrat pour l'immatriculation %s\n", buffer);

            //TODO: parcourir les voitures stationnées pour trouver celle correspondante à la plaque
        }
    } else {
        //on continue de trader avec les bornes
        trade(serverSocket, range);
    }
}