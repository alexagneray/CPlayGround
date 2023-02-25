#include "server.h"
#include <Common.h>
#include <network_shot.h>

#include "server_command.h"
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <stdio.h>
#include <stdbool.h>
#include <errno.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <pthread.h>


// Macros d'affichage du serveur
#define SERVER_ERROR(Msg) ERROR("SERVER", Msg)
#define SERVER_SUCCESS(Msg) SUCCESS("SERVER", Msg)
#define SERVER_FSUCCESS(Msg,...) FSUCCESS("SUCCESS",Msg, ##__VA_ARGS__);
#define SERVER_FERROR(Msg,...) FERROR("ERROR",Msg, ##__VA_ARGS__);


int s_nServerSock = -1; /**< Socket serveur */


TCLIENTPTR s_Clients [_I_SERVER_MAX_CLIENTS_COUNT];

pthread_mutex_t s_ClientsMutex;




void* server_client_list_check_thread_main(void* pArgs)
{
    
}


void server_exit()
{
    SERVER_SUCCESS("Exiting server ...")
    close(s_nServerSock);
    pthread_exit(NULL);
}

void server_forced_exit(int code)
{
    SERVER_SUCCESS("Exiting server ...")
    close(s_nServerSock);
    exit(0);
}
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

bool server_execute_command(ECMD eCmd, char* pBuffer)
{
    switch (eCmd)
    {
    case Join:
        server_command_join(pBuffer);
        break;
    case Leave:
        server_exit();
        break;
    case Tell:
        server_command_tell(pBuffer);
        break;
    case AddMsg:
        server_command_add_msg(pBuffer);
        break;
    case ReadMsg:
        server_command_read_msg(pBuffer);
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

    signal(SIGTERM, &server_forced_exit);
    signal(SIGINT, &server_forced_exit);
    signal(SIGSTOP, &server_forced_exit);
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
    TSHOT RecvShot;
    while(1)
    {
        // int nRecvBytes = recv(nClientSocket, &RecvShot, sizeof(struct TShot),MSG_PEEK | MSG_WAITALL);
        // if()
        int ret = read(nClientSocket, &RecvShot, sizeof(TSHOT));
        
        if(!ret)
        {
            SERVER_SUCCESS("The client exited.")
            return;
        }


        SERVER_FSUCCESS("Received Shot %s => %s",CMD_GET_LABEL(RecvShot.eCmd),RecvShot.Buffer);
        server_execute_command(RecvShot.eCmd, RecvShot.Buffer);
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
        return NULL;
    }

    
    err = listen(s_nServerSock, 10);
    SERVER_SUCCESS("Listening ...")
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