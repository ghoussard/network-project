#include "../../common/common.h"

//structure représentant un serveur
typedef struct {
    char ip[20];
    int port;
} Server;

//prototypes
void terminal();
void queryServers(int type, char string[7]);
int menu();
void newContract();
void viewContract();
void defineServers();