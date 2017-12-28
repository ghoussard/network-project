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

void queryServers(int type, char string[]) {

    //on interroge chaque serveur 1 à 1
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

        //on envoie la chaine
        write(clientSocket, string, 7);
        
        //on s'endort pour attendre la réponse
        sleep(1);

        /*
            réponse du serveur : au préalable, on appelle cette fonction avec 1 ou 2 
            pour savoir à quelle structure de retour s'attendre
        */
        if(type==1) {
            //traitement de la structure retournée pour une demande de contrat
        } else {
            //traitement de la structure retournée pour une consultation de contrat
        }

        //on ferme la socket client
        close(clientSocket);

    }

}

void queryServers2(int type, Car * car) {

    //on interroge chaque serveur 1 à 1
    for(int i = 0; i<NB_SERVERS; i++) {

        //création d'une socket
        int clientSocket = makeSocket();

        //création d'une adresse
        struct sockaddr_in distant = makeSockAddrIn(servers[i].ip, servers[i].port);

        //bindSocket(clientSocket, &distant);

        //on se connecte à un serveur
        int c = connect(clientSocket,(struct sockaddr*)&distant,sizeof(distant));
        if(c<0) {
            perror("Erreur de connexion");
        }

        //on envoie la chaine
        send(clientSocket, car, sizeof(Car), 0);
        
        //on s'endort pour attendre la réponse
        //sleep(1);

        recv(clientSocket, car, sizeof(Car), 0);

        /*
            réponse du serveur : au préalable, on appelle cette fonction avec 1 ou 2 
            pour savoir à quelle structure de retour s'attendre
        */
        if(type==1) {
            //traitement de la structure retournée pour une demande de contrat
        } else {
            //traitement de la structure retournée pour une consultation de contrat
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

    //on déclare une nouvelle voiture
    Car c;

    //on demande les infos nécessaires
    char class[7];
    printf("Classe du vehicule : ");
    scanf("%s", &(c.p.category));
    char matriculation[7];
    printf("Immatriculation : ");
    scanf("%s", c.matriculation);
    int duration;
    printf("Durée estimée : ");
    scanf("%d", &(c.time));

    printf("Demande en cours...\n");

    //on envoie la chaine aux serveurs
    queryServers2(1, &c);

    printf("Prix : %f\n", c.p.price);

}

void viewContract() {
    printf("Consulter un contrat\n\n");

    //on demande les infos nécéssaires
    char matriculation[7];
    printf("Immatriculation du véhicule : ");
    scanf("%s", matriculation);

    printf("Demande en cours...\n");

    //on envoie la chaine au serveur
    queryServers(1, matriculation);
}

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