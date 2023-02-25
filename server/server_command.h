#ifndef _SERVER_COMMAND_H
#define _SERVER_COMMAND_H

#include <stdbool.h>

/**
 * @brief Command process functions.
 *  
 * @param pBuffer The data received for the command execution. 
 * @return true 
 * @return false 
 */
bool server_command_join(char* pBuffer);

bool server_command_tell(char* pBuffer);

bool server_command_leave(char* pBuffer);

bool server_command_add_msg(char* pBuffer);

bool server_command_read_msg(char* pBuffer);

#endif // _SERVER_COMMAND_H