#include "common.h"

/*
    Retourne une socket
*/
int makeSocket() {
    int s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(s<0) {
        printError("Echec de la création de la socket");
    }
    return s;
}

/*
    Retourne une adresse
*/
struct sockaddr_in makeSockAddrIn(char *ip, int port) {
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    if(strlen(ip)==0) {
        addr.sin_addr.s_addr = INADDR_ANY;
    } else {
        addr.sin_addr.s_addr = inet_addr(ip);
    }
    
    return addr;
}

/*
    Affiche une erreur et stop le programme
*/
void printError(char *trace) {
    perror(trace);
    exit(EXIT_FAILURE);
}

/*
    Configure une socket
*/
void bindSocket(int socket, struct sockaddr_in *addr) {
    int b = bind(socket, (struct sockaddr *) addr, sizeof(struct sockaddr_in));
    if (b<0) {
		printError("Echec du bind de la socket");
    }
}