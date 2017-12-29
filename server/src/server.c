#include "server.h"
#include "data.h"

//gamme du serveur
int range;


/*
    Fonction principale du serveur
*/
void server(int port, int argrange) {
    range = argrange;

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
    trade(serverSocket);
}


/*
    Communique avec la borne
*/
void trade(int serverSocket) {
    int socketClient;
    struct sockaddr_in clientAdd;

    socklen_t len = sizeof(clientAdd);

    //Attente de la connexion d'un client
    socketClient = accept(serverSocket, (struct sockaddr *) &clientAdd, &len);
    
    if(fork()==0) {

        printf("Une borne s'est connectée !\n");

        Request r;

        //reception de la requete
        recv(socketClient, &r, sizeof(Request), 0);

        //on remplit la requete selon la demande
        if(r.type == 'N') {
            processNewContract(&r);
        } else {
            processViewContract(&r);
        }

        //on écrit le nom du parking dans la requete
        strcpy(r.serverName, serverNames[range-1]);

        //on renvoie la requete
        send(socketClient, &r, sizeof(Request), 0);

        printf("Réponse envoyée !\n");
        
    } else {
        //on continue de trader avec les bornes
        trade(serverSocket);
    }
}


/*
    Selectionne le forfait pour un nouveau contrat
*/
void processNewContract(Request *r) {

    printf("Demande de contrat demandée pour un véhicule de classe %c\n", r->c.p.category);

    printf("Traitement... \n");

    //on regarde si il reste de la place pour cette catégorie et si elle est gérée
    int category = convertCategorytoInt(r->c.p.category);
    r->available = 0;
    if(category>=0) {
        r->available = availableSpaces[range-1][category];
    }

    //si il y a des places dispo on remplit le forfait
    if(r->available>0) {
        printf("Place disponible ! \n");
        printf("Selection du forfait...\n");
        for(int i = 0; i < sizeof(packages[range-1])/sizeof(Package); i++) {
            if(packages[range-1][i].category == r->c.p.category) {
                r->c.p.price = packages[range-1][i].price;
                r->c.p.out = packages[range-1][i].out;
                r->c.p.maxDuration = maxDuration[range-1];
            }
        }
    }
}


/*
    Affiche l'état d'un contrat selon l'immatriculation
*/
void processViewContract(Request *r) {

    printf("Consultation de contrat pour l'immatriculation %s\n", r->c.matriculation);

    printf("Traitement... \n");

    r->present = 0;
    for(int i =0; i < sizeof(storedCars[range-1])/sizeof(Car); i++) {
        if(strcmp(storedCars[range-1][i].matriculation, r->c.matriculation) == 0) {
            printf("Immatriculation trouvée !\n");
            r->present = 1;
            r->c = storedCars[range-1][i];
            r->pricetopay = getPrice(storedCars[range-1][i].p.category, storedCars[range-1][i].duration);
            break;
        }
    }
    
    if(r->present==0) {
        printf("Immatriculation non trouvée\n");
    }
}


/*
    Convertit les classes de voiture en int
*/
int convertCategorytoInt(char c) {
    switch(c) {
        case 'A':
            return 0;
            break;
        case 'B':
            return 1;
            break;
        case 'C':
            return 2;
            break;
        case 'D':
            return 3;
            break;
        case 'E':
            return 4;
            break;
        default:
            return -1;
            break;
    }
}


/*
    Retourne le prix selon la classe et le temps de stationnement d'une voiture
*/
double getPrice(char c, int duration) {

    double price, out;

    for(int i = 0; i < sizeof(packages[range-1])/sizeof(Package); i++) {
        if(packages[range-1][i].category == c) {
            price = packages[range-1][i].price;
            out = packages[range-1][i].out;
        }
    }

    int max = maxDuration[range-1];

    if(duration>max) {
        double inprice = max*price;
        double outprice = (duration-max)*out;
        return inprice+outprice;
    } else {
        return duration*price;
    }

    return 0;
}