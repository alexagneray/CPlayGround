#include "server_command.h"
#include <stdio.h>

#define SRV_COMMAND_BEGIN_LOG(Cmd) printf("Executing " #Cmd " Command !\n");

bool server_command_join(char* pBuffer)
{
    SRV_COMMAND_BEGIN_LOG(Join)
}

bool server_command_tell(char* pBuffer)
{
    SRV_COMMAND_BEGIN_LOG(Tell)
}

bool server_command_leave(char* pBuffer)
{
    SRV_COMMAND_BEGIN_LOG(Leave)
}

bool server_command_add_msg(char* pBuffer)
{
    SRV_COMMAND_BEGIN_LOG(AddMsg)
    
}

bool server_command_read_msg(char* pBuffer)
{
    SRV_COMMAND_BEGIN_LOG(ReadMsg)
}