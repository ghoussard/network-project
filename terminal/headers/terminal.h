#include "../../common/common.h"

//structure représentant un serveur
typedef struct {
    char ip[20];
    int port;
} Server;

//définition d'un forfait
typedef struct {
    char category;
    double price;
    double out;
} Package;

//définition d'une voiture stationnée
typedef struct {
    char matriculation[7];
    char class[7];
    int time;
    Package p;
} Car;

//prototypes
void terminal();
void queryServers(int type, char string[7]);
int menu();
void newContract();
void viewContract();
void defineServers();