#include "server.h"
#include "../../common/common.h"

int main(int argc, char *argv[]) {
    
    //vérification de la saisie du port et de la gamme
    if(argc < 3) {
        printError("Aucun port ou gamme renseigné");
    }

    //lancement du serveur
    server(atoi(argv[1]), atoi(argv[2]));

    return 0;
}