#include "terminal.h"
#include "data.h"

/*
    Fonction principale de la borne
*/
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

    printf("\n\n");

    }

}


/*
    Interroge les serveur 1 à 1
*/
void queryServers(Request * req) {

    //on interroge chaque serveur 1 par 1
    for(int i = 0; i<NB_SERVERS; i++) {

        //création d'une socket
        int clientSocket = makeSocket();

        //création d'une adresse
        struct sockaddr_in distant = makeSockAddrIn(servers[i].ip, servers[i].port);

        //Rattachement de la socket sur le port d'écoute
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

        printf("\nRéponse du parking \"%s\" : \n", req->serverName);
        if(req->type == 'N') {
            decodeNCRequest(req);
        } else {
            decodeVCRequest(req);
        }

        //on ferme la socket client
        close(clientSocket);
    }
}


/*
    Menu de la borne
*/
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

/*
    Demande de contrat
*/
void newContract() {

    printf("\nNouveau contrat :\n\n");

    //on déclare un nouvel echange
    Request r;

    //on demande les infos nécessaires
    printf("Classe du vehicule [A-E] : ");
    scanf("%s", &(r.c.p.category));
    printf("Immatriculation [AAXXXAA] : ");
    scanf("%s", r.c.matriculation);
    printf("Durée estimée : ");
    scanf("%d", &(r.c.duration));

    printf("\nDemande en cours...\n");

    r.type = 'N';

    //on envoie la requete aux serveurs
    queryServers(&r);
}


/*
    Consultation de contrat
*/
void viewContract() {

    printf("\nConsulter un contrat :\n\n");

    //on déclare une nouvelle requete
    Request r;

    //on demande les infos nécéssaires
    printf("Immatriculation du véhicule : ");
    scanf("%s", r.c.matriculation);

    printf("\nDemande en cours...\n");

    r.type = 'V';

    //on envoie la requete aux serveurs
    queryServers(&r);
}


/*
    Définit les serveurs
*/
void defineServers() {

    printf("\nConfiguration des serveurs distants : \n\n");

    //on parcours le tableau de serveurs pour les redéfinir
    for(int i = 0; i<NB_SERVERS; i++) {
        printf("Adresse du serveur %d [%s] : ", i+1, servers[i].ip);
        scanf("%s", servers[i].ip);
        printf("Port [%d] : ", servers[i].port);
        scanf("%d", &servers[i].port);
    }

    printf("\nConfiguration des serveurs terminée\n\n");

}


/*
    Décode la réponse reçue à une demande de contrat
*/
void decodeNCRequest(Request *r) {
    if(r->available<1) {
        printf("Pas de place disponible pour cette classe\n");
    } else {
        printf("Cout de stationnement pour le véhicule immatriculé %s de classe %c :\n", r->c.matriculation, r->c.p.category);
        printf("%.2f€/H pendant %dH, puis %.2f€/H\n", r->c.p.price, r->c.p.maxDuration, r->c.p.out);
        if(r->c.duration>r->c.p.maxDuration) {
            double price = r->c.p.maxDuration*r->c.p.price;
            double outprice = (r->c.duration-r->c.p.maxDuration)*r->c.p.out;
            printf("%dH : %.2f€\n", r->c.duration, price+outprice);
            printf("%dH : %.2f€\n", r->c.duration+1, price+outprice+r->c.p.out);
            printf("%dH : %.2f€\n", r->c.duration*2, price+outprice+r->c.p.out*r->c.duration);
        } else {
            double price = r->c.duration*r->c.p.price;
            printf("%dH : %.2f€\n", r->c.duration, price);
            if(r->c.duration+1>r->c.p.maxDuration) {
                printf("%dH : %.2f€\n", r->c.duration+1, price+r->c.p.out);
            } else {
                printf("%dH : %.2f€\n", r->c.duration+1, price+r->c.p.price);
            }
            if(r->c.duration*2>r->c.p.maxDuration) {
                double price = r->c.p.maxDuration*r->c.p.price;
                double outprice = (r->c.duration*2-r->c.p.maxDuration)*r->c.p.out;
                printf("%dH : %.2f€\n", r->c.duration*2, price+outprice);
            } else {
                printf("%dH : %.2f€\n", r->c.duration*2, price+r->c.p.price*r->c.duration);
            }
        }
    }
}


/*
    Décode la requete de réponse à une consultation de contrat
*/
void decodeVCRequest(Request *r) {
    if(r->present==0) {
        printf("Cette immatriculation n'est pas présente dans ce parking\n");
    } else {
        printf("Immatriculation présente :\n");
        printf("Classe du véhicule : %c\n", r->c.p.category);
        printf("Durée de stationnement : %d\n", r->c.duration);
        printf("Prix à payer : %.2f€\n", r->pricetopay);
    }
}