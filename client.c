#include "client.h"
#include <stdio.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/socket.h>

#include "Common.h"

#define CLIENT_ERROR(Msg) ERROR("CLIENT", Msg)
#define CLIENT_SUCCESS(Msg) SUCCESS("CLIENT", Msg)
#define CLIENT_FSUCCESS(Msg,...) FSUCCESS("CLIENT", Msg, ##__VA_ARGS__);
#define CLIENT_FERROR(Msg,...) FERROR("CLIENT",Msg, ##__VA_ARGS__);

void* client_thread_main(void* pArg)
{
    printf("Starting client thread.\n");

    int nSocket;
    struct addrinfo Hints;
    struct addrinfo* pResults;
    int nErr;

    if((nSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        CLIENT_ERROR("Error creating socket.")
    }
    else
    {
        CLIENT_SUCCESS("Socket successfully created !")
    }

    memset(&Hints, 0, sizeof(struct addrinfo));
    Hints.ai_family = AF_INET;
    Hints.ai_socktype = SOCK_STREAM;

    if((nErr = getaddrinfo("127.0.0.1","8000" ,&Hints, &pResults)) != 0)
    {
        CLIENT_FERROR("getaddrinfo : %s", gai_strerror(nErr))
        return NULL;
    }
    else 
    {
        CLIENT_SUCCESS("getaddrinfo : Success !")
    }
    if((nErr = connect(nSocket, pResults->ai_addr, pResults->ai_addrlen))<0)
    {
        CLIENT_FERROR("connect : %s", gai_strerror(nErr))
    }
    else
    {
        CLIENT_SUCCESS("Connected to the server !")
    }

    struct TShot SentShot;
    SentShot.eCmd = Join;
    const char* zMsg = "Hello server !";
    memcpy(&SentShot.Buffer[0], zMsg, strlen(zMsg));

    CLIENT_SUCCESS("Sending Join")
    // send(nSocket, &SentShot, sizeof(struct TShot), MSG_DONTWAIT);
    write(nSocket, &SentShot, sizeof(struct TShot));

    SentShot.eCmd = Tell;
    CLIENT_SUCCESS("Sending Tell")
    // send(nSocket, &SentShot, sizeof(struct TShot), MSG_DONTWAIT);
    write(nSocket, &SentShot, sizeof(struct TShot));

    SentShot.eCmd = Leave;
    CLIENT_SUCCESS("Sending Leave")
    // send(nSocket, &SentShot, sizeof(struct TShot), MSG_DONTWAIT);
    write(nSocket, &SentShot, sizeof(struct TShot));

    freeaddrinfo(pResults);

    close(nSocket);
    return NULL;
}