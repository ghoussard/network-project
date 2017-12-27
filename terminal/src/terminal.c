#include "terminal.h"

Server servers[NB_SERVERS] = {
    {"127.0.0.1", 8000},
    {"127.0.0.1", 8001},
    {"127.0.0.1", 8002}
};

void terminal() {

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

void connectServers() {
    for(int i = 0; i<NB_SERVERS; i++) {
        int clientSocket = makeSocket();
        struct sockaddr_in distant = makeSockAddrIn(servers[i].ip, servers[i].port);
        int c = connect(clientSocket,(struct sockaddr*)&distant,sizeof(distant));
        if(c<0) {
            perror("Erreur de connexion");
            exit(EXIT_FAILURE);
        }
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
}

void viewContract() {
    printf("Consulter un contrat\n\n");
}

void defineServers() {
    printf("Configurer les serveurs distants\n\n");
}