#ifndef _SERVER_COMMAND_H
#define _SERVER_COMMAND_H

#include <stdbool.h>

bool server_command_join();

bool server_command_tell();

bool server_command_leave();

bool server_add_msg();

bool server_read_msg();

#endif // _SERVER_COMMAND_H