#include "../../common/common.h"

//nombre de clients max par serveur
#define MAX_CLIENTS 5

//définition d'un forfait
typedef struct {
    char category;
    double price;
    double out;
    int duration;
} Package;

//définition d'une voiture stationnée
typedef struct {
    char matriculation[7];
    char class[7];
    int time;
    Package p;
} Car;

//prototypes
void server(int port, int range);
void trade(int serverSocket, int range);