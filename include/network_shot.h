#ifndef NETWORK_SHOT_H
#define NETWORK_SHOT_H

#include <Common.h>

#define _I_SHORT_SHOT_BUFFER_SIZE_ 512
#define _I_MEDIUM_SHOT_BUFFER_SIZE_ 4*_I_SHORT_SHOT_BUFFER_SIZE_
#define _I_BIG_SHOT_BUFFER_SIZE_ 4*_I_MEDIUM_SHOT_BUFFER_SIZE_

enum ShotType
{
    ShotInfoType, /**< Query infos about the server */
    ShotSendType, /**< Send data to the server */
    ShotRecvType, /**< Recv data from the server */
    ShotAlertType /**< Send alert to the server */
};

// __flags IN | CN

// IN : initiator -> who sent the first message (1 for client, 0 for server)
// BG : beginning -> the client want to connect to the server
// DT : data -> the client wants to send data
typedef struct TShotHeader
{
    int __id; /**< Identifier for the shot */
    int __flags; /**< Flags indicating infos on data */
    ECMD _cmd; /**< Query command */
    int _size; /**< */
} TSHOTHEADER;

typedef struct TShortShot
{
    TSHOTHEADER __header;
    char _buffer[_I_SHORT_SHOT_BUFFER_SIZE_];
} TSHORTSHOT;

typedef struct TMediumShot
{
    TSHOTHEADER __header;
    char _buffer[_I_MEDIUM_SHOT_BUFFER_SIZE_];
} TMEDIUMSHOT;

typedef struct TBigShot
{
    TSHOTHEADER __header;
    char _buffer[_I_BIG_SHOT_BUFFER_SIZE_];
} TBIGSHOT;

typedef struct TShot
{
    ECMD eCmd;
    TSHOTCHECK CmdCheck;
    char Buffer[_I_SHORT_SHOT_BUFFER_SIZE_];
} TSHOT;

#endif // NETWORK_SHOT_H