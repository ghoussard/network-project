#include "../../common/common.h"
#include "../../common/struct.h"

//structure représentant un serveur
typedef struct {
    char ip[20];
    int port;
} Server;

//prototypes
void terminal();
void queryServers(Request * req);
int menu();
void newContract();
void viewContract();
void defineServers();
void decodeNCRequest(Request *r);
void decodeVCRequest(Request *r);