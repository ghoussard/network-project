#include "server.h"
#include "../../libs/utils/utils.h"

int main(int argc, char *argv[]) {
    
    //vérification de la saisie du port
    if(argc < 2) {
        printError("Aucun port renseigné");
    }

    //lancement du serveur
    server(atoi(argv[1]));

    return 0;
}