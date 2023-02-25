#ifndef SERVER_MSG_CONTAINER_H
#define SERVER_MSG_CONTAINER_H

#include "../server_data_defines.h"
#include <stdbool.h>

#define SERVER_MSG_DATA_FOLDER SERVER_DATA_FOLDER "Msg"

/**
 * @brief Contains a message that can be stored by the server.
 * 
 */
typedef struct msg_t
{
    char head[1024];
    char content[2048];
    char tail[1024];
} MSG;


/**
 * @brief Containes meta data about a struct msg_t.
 * 
 */
typedef struct msgmeta_t
{
    char author[64];
    unsigned long long date;
} MSGMETA;

/**
 * @brief Save a message on the server data storage.
 * 
 * @param msg 
 * @param msgmeta 
 * @param data_id_t 
 * @return true 
 * @return false 
 */
bool save_msg(const MSG* msg, const MSGMETA* msgmeta, int* data_id_t);

/**
 * @brief Load a message from the server data storage.
 * 
 * @param data_id_t 
 * @param msg 
 * @param msgmeta 
 * @return true 
 * @return false 
 */
bool load_msg( int data_id_t, MSG* msg, MSGMETA* msgmeta );

#endif