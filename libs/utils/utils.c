#include "utils.h"

int makeSocket() {
    int s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(s<0) {
        perror("Echec de la création de la socket");
        exit(EXIT_FAILURE);
    }
    return s;
}