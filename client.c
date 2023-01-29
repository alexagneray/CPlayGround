#include "client.h"
#include <stdio.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "Common.h"

#define CLIENT_ERROR(Msg) ERROR("CLIENT", Msg)
#define CLIENT_SUCCESS(Msg) SUCCESS("CLIENT", Msg)
#define CLIENT_FSUCCESS(Msg,...) FSUCCESS("CLIENT", Msg, ##__VA_ARGS__);
#define CLIENT_FERROR(Msg,...) FERROR("CLIENT",Msg, ##__VA_ARGS__);


void* client_thread_main(void* pArg)
{
    int sock;
    int err;

    struct sockaddr_in srv;
    bzero(&srv, sizeof(srv));
    srv.sin_family = AF_INET;
    srv.sin_addr.s_addr = inet_addr("192.168.1.66");
    srv.sin_port = htons(8000);

    sock = socket(AF_INET, SOCK_STREAM, 0);

    if(sock == -1)
    {
        CLIENT_ERROR("socket()")
    }


    err = connect(sock, &srv, sizeof(srv));
    if(err == -1)
    {
        CLIENT_ERROR("connect() >> FAILED")
    }

    struct TShot SentShot;
    SentShot.eCmd = Join;
    const char* zMsg = "Hello server !";
    memcpy(&SentShot.Buffer[0], zMsg, strlen(zMsg));

    CLIENT_SUCCESS("Sending Join")
    // send(nSocket, &SentShot, sizeof(struct TShot), MSG_DONTWAIT);
    write(sock, &SentShot, sizeof(struct TShot));

    SentShot.eCmd = Tell;
    CLIENT_SUCCESS("Sending Tell")
    // send(nSocket, &SentShot, sizeof(struct TShot), MSG_DONTWAIT);
    write(sock, &SentShot, sizeof(struct TShot));

    SentShot.eCmd = Leave;
    CLIENT_SUCCESS("Sending Leave")
    // send(nSocket, &SentShot, sizeof(struct TShot), MSG_DONTWAIT);
    write(sock, &SentShot, sizeof(struct TShot));

    // freeaddrinfo(srv);

    close(sock);
    return NULL;
}

// void* client_thread_main(void* pArg)
// {
//     printf("Starting client thread.\n");

//     int nSocket;
//     struct addrinfo Hints;
//     struct addrinfo* pSrv;
//     struct sockaddr_in srv;

//     bzero(&srv, sizeof(srv));
//     srv.sin_family = AF_INET;
//     srv.sin_addr.s_addr = inet_addr("192.168.1.66");
//     srv.sin_port = "8000";
//     struct addrinfo* pClt;
//     int nErr;

    

//     memset(&Hints, 0, sizeof(struct addrinfo));
//     Hints.ai_family = AF_INET;
//     Hints.ai_socktype = SOCK_STREAM;

//     nErr = getaddrinfo("192.168.1.66","8000" ,&Hints, &pSrv);
//     if(nErr != 0)
//     {
//         CLIENT_FERROR("srv getaddrinfo : %s", gai_strerror(nErr))
//         return NULL;
//     }
//     else 
//     {
//         CLIENT_SUCCESS("srv getaddrinfo : Success !")
//     }

//     memset(&Hints, 0, sizeof(struct addrinfo));
//     Hints.ai_family = AF_INET;
//     Hints.ai_socktype = SOCK_STREAM;
//     Hints.ai_flags = AI_PASSIVE;
//     nErr = getaddrinfo(NULL, "8000", &Hints, &pClt);
//     if(nErr != 0)
//     {
//         CLIENT_FERROR("clt getaddrinfo : %s", gai_strerror(nErr))
//         return NULL;
//     }
//     else 
//     {
//         CLIENT_SUCCESS("clt getaddrinfo : Success !")
//     }


//     if((nSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
//     {
//         CLIENT_ERROR("Error creating socket.")
//     }
//     else
//     {
//         CLIENT_SUCCESS("Socket successfully created !")
//     }

//     nErr = connect(nSocket, (struct sockaddr_in*) &srv, sizeof(srv));
//     if(nErr<0)
//     {
//         CLIENT_FERROR("connect : %s", gai_strerror(nErr))
//     }
//     else
//     {
//         CLIENT_SUCCESS("Connected to the server !")
//     }

//     // struct TShot SentShot;
//     // SentShot.eCmd = Join;
//     // const char* zMsg = "Hello server !";
//     // memcpy(&SentShot.Buffer[0], zMsg, strlen(zMsg));

//     // CLIENT_SUCCESS("Sending Join")
//     // // send(nSocket, &SentShot, sizeof(struct TShot), MSG_DONTWAIT);
//     // write(nSocket, &SentShot, sizeof(struct TShot));

//     // SentShot.eCmd = Tell;
//     // CLIENT_SUCCESS("Sending Tell")
//     // // send(nSocket, &SentShot, sizeof(struct TShot), MSG_DONTWAIT);
//     // write(nSocket, &SentShot, sizeof(struct TShot));

//     // SentShot.eCmd = Leave;
//     // CLIENT_SUCCESS("Sending Leave")
//     // // send(nSocket, &SentShot, sizeof(struct TShot), MSG_DONTWAIT);
//     // write(nSocket, &SentShot, sizeof(struct TShot));

//     freeaddrinfo(pSrv);

//     close(nSocket);
//     return NULL;
// }