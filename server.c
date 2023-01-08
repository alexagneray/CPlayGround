#include "server.h"
#include "Common.h"
#include "server_command.h"
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <stdio.h>
#include <stdbool.h>
#include <errno.h>
#include <unistd.h>


#define SERVER_ERROR(Msg) ERROR("SERVER", Msg)
#define SERVER_SUCCESS(Msg) SUCCESS("SERVER", Msg)
#define SERVER_FSUCCESS(Msg,...) FSUCCESS("SUCCESS",Msg, ##__VA_ARGS__);
#define SERVER_FERROR(Msg,...) FERROR("ERROR",Msg, ##__VA_ARGS__);
static int s_nServerSock = -1; /**< Socket serveur */

#define _I_SERVER_MAX_CLIENTS_COUNT 10

/**
 * Enregistrement des informations d'un client.
*/
typedef struct TClient
{
    unsigned long long uTs; // Ts fourni par le client.
    int nSeed; // Seed fourni par le client.
    int nId; // Correspond à l'id dans le tableau client.
    unsigned long long uLastAction; // Ts de la derniere action du client.
} TCLIENT;

typedef TCLIENT* TCLIENTPTR;
typedef TCLIENTPTR HCLIENT;

/**
 * Tableau des clients.
 * Un nombre de clients max est défini !
 * Lorsque le tableau est plein, on ne peut plus gérer de client.
*/
TCLIENTPTR s_Clients [_I_SERVER_MAX_CLIENTS_COUNT];



bool server_check_shot(int nClientId, const TSHOT* pShot)
{
    HCLIENT hClient = s_Clients[nClientId];
    if(!hClient)
    {
        return false;
    }

    if(hClient->nSeed != pShot->CmdCheck.nSeed)
    {
        return false;
    }

    if(hClient->uTs != pShot->CmdCheck.uTs)
    {
        return false;
    }

    return true;

}

bool server_execute_command(enum ECmd eCmd, char* pBuffer)
{
    switch (eCmd)
    {
    case Join:
        server_command_join();
        break;
    
    default:
        break;
    }
    return true;
}


bool server_net_init()
{
    int nErr = 0;

    struct addrinfo Hints;
    
    struct addrinfo* pResults;

    
    if((s_nServerSock = socket(AF_INET, SOCK_STREAM,IPPROTO_TCP)) < 0 )
    {
        SERVER_ERROR("Error during Socket creation.")
        return false;
    }
    else
    {
        SERVER_SUCCESS("Socket successfully created !")
    }

    memset(&Hints, 0, sizeof(struct addrinfo));
    Hints.ai_family = AF_INET;
    Hints.ai_socktype = SOCK_STREAM;
    Hints.ai_flags = AI_PASSIVE;

    if((nErr = getaddrinfo(NULL, "8000", &Hints, &pResults)) != 0)
    {
        SERVER_FERROR("getaddrinfo : %s", gai_strerror(nErr))
        return false;
    }
    else 
    {
        SERVER_SUCCESS("getaddrinfo : Success !")
    }

    nErr = bind(s_nServerSock, pResults->ai_addr, pResults->ai_addrlen);
    freeaddrinfo(pResults);

    if(nErr < 0)
    {
        SERVER_ERROR("Error during Bind().")
        close(s_nServerSock);
        return false;
    }

    return true;
}

void server_handle_client(int nClientSocket)
{
    struct TShot RecvShot;
    while(1)
    {
        // int nRecvBytes = recv(nClientSocket, &RecvShot, sizeof(struct TShot),MSG_PEEK | MSG_WAITALL);
        // if()
        read(nClientSocket, &RecvShot, sizeof(struct TShot));
        


        SERVER_FSUCCESS("Received Shot %s => %s",CMD_GET_LABEL(RecvShot.eCmd),RecvShot.Buffer);
        sleep(1);
    }
}

/**
 * Appelée une fois au démarrage du serveur.
*/
void server_init_proc()
{
    memset(s_Clients, 0, _I_SERVER_MAX_CLIENTS_COUNT * sizeof(TCLIENT *));
}

void* server_thread_main(void* pArg)
{
    int err;
    SERVER_SUCCESS("Starting server thread.")

    server_init_proc();

    if(server_net_init())
    {
        SERVER_SUCCESS("Server socket initialized !")
    }
    else
    {
        SERVER_SUCCESS("Socket not initialized.")
    }

    err = listen(s_nServerSock, 10);
    err = errno;
    int nClientSocket;

    while(1)
    {
        nClientSocket = accept(s_nServerSock, NULL, NULL);

        switch (fork())
        {
        case 0:
            server_handle_client(nClientSocket);
            break;
        case -1:
            SERVER_FERROR("Error while creating fork. errno %d", err)
            break;
        
        default:
            close(nClientSocket);
        }
    }
    return NULL;
}