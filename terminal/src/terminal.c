#include "terminal.h"
#include "data.h"

void terminal() {
    //execution du menu
    while(1) {

        int action = menu();

        switch(action)
        {
            case 1:
                newContract();
                break;
            case 2:
                viewContract();
                break;
            case 3: 
                defineServers();
                break;
            case 4:
                printf("Merci de votre visite !\n\n");
                exit(0);
        }

    }

}

void queryServers(Request * req) {

    //on interroge chaque serveur 1 par 1
    for(int i = 0; i<NB_SERVERS; i++) {

        //création d'une socket
        int clientSocket = makeSocket();

        //création d'une adresse
        struct sockaddr_in distant = makeSockAddrIn(servers[i].ip, servers[i].port);

        //bindSocket(clientSocket, &distant);

        //on se connecte à un serveur
        int c = connect(clientSocket,(struct sockaddr*)&distant,sizeof(distant));
        if(c<0) {
            printError("Erreur de connexion");
        }

        //on envoie la requete à compléter
        send(clientSocket, req, sizeof(Request), 0);

        //on reçoit la réponse
        recv(clientSocket, req, sizeof(Request), 0);

        if(req->type == 'N') {
            decodeNCRequest(req);
        } else {
            decodeVCRequest(req);
        }

        //on ferme la socket client
        close(clientSocket);

    }

}

int menu() {
    int choix;

    printf("--- BORNE PARKING --- \n\n");

    printf("Que voulez-vous faire ?\n\n");

    printf("[1] - Demander un contrat\n");
    printf("[2] - Consulter un contrat\n");
    printf("[3] - Modifier l'adresse des serveurs distants\n");
    printf("[4] - Quitter\n\n");

    do {
        scanf("%d",&choix);
    } while (choix<1||choix>4);

    return choix;
}

void newContract() {

    printf("Nouveau contrat\n\n");

    //on déclare un nouvel echange
    Request r;

    //on demande les infos nécessaires
    printf("Classe du vehicule : ");
    scanf("%s", &(r.c.p.category));
    printf("Immatriculation : ");
    scanf("%s", r.c.matriculation);
    printf("Durée estimée : ");
    scanf("%d", &(r.c.time));

    printf("Demande en cours...\n");

    r.type = 'N';

    //on envoie la requete aux serveurs
    queryServers(&r);
}


/*
    Interroge les serveurs pour un contrat
*/
void viewContract() {

    printf("Consulter un contrat\n\n");

    //on déclare une nouvelle requete
    Request r;

    //on demande les infos nécéssaires
    printf("Immatriculation du véhicule : ");
    scanf("%s", r.c.matriculation);

    printf("Demande en cours...\n");

    r.type = 'V';

    //on envoie la requete aux serveurs
    queryServers(&r);
}


/*
    Définit les serveurs
*/
void defineServers() {

    printf("Configuration des serveurs distants\n\n");

    //on parcours le tableau de serveurs pour les redéfinir
    for(int i = 0; i<NB_SERVERS; i++) {
        printf("Adresse du serveur %d [%s] : ", i+1, servers[i].ip);
        scanf("%s", servers[i].ip);
        printf("Port [%d] : ", servers[i].port);
        scanf("%d", &servers[i].port);
    }

    printf("\nConfiguration des serveurs terminée\n\n");

}


void decodeNCRequest(Request *r) {
    printf("Prix : %2.f\n", r->c.p.price);
}


void decodeVCRequest(Request *r) {

}