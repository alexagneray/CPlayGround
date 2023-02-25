#ifndef _SERVER_H
#define _SERVER_H


#include <pthread.h>

extern int s_nServerSock; /**< Socket serveur */


#define _I_SERVER_MAX_CLIENTS_COUNT 10 /**< Nombre de clients max sur le serveur */

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

typedef TCLIENT* TCLIENTPTR; /**< Pointeur sur une structure de client */
typedef TCLIENTPTR HCLIENT; /**< Handle client */

/**
 * Tableau des clients.
 * Un nombre de clients max est défini !
 * Lorsque le tableau est plein, on ne peut plus gérer de client.
*/
extern TCLIENTPTR s_Clients [_I_SERVER_MAX_CLIENTS_COUNT];

extern pthread_mutex_t s_ClientsMutex; /**< Accés au tableau s_Clients */

void* server_thread_main(void* pArg);

#endif // _SERVER_COMMAND_H