#include "../../libs/utils/utils.h"
#define NB_SERVERS 3

typedef struct {
    char ip[20];
    int port;
} Server;

void terminal();
void connectServers();
int menu();
void newContract();
void viewContract();
void defineServers();