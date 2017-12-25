#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int makeSocket();
struct sockaddr_in makeSockAddrIn(int port);
void printError(char *trace);
void bindSocket(int socket, struct sockaddr_in *add);