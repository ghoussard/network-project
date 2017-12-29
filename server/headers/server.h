#include "../../common/common.h"
#include "../../common/struct.h"

//nombre de clients max par serveur
#define MAX_CLIENTS 5

//prototypes
void server(int port, int argrange);
void trade(int serverSocket);
void processNewContract(Request *r);
void processViewContract(Request *r);
int convertCategorytoInt(char c);