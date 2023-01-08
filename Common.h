#ifndef _COMMON_H
#define _COMMON_H

#include <stdio.h>
#include <string.h>


/**
 * Valeurs de retour des fonctions.
 * 
*/
typedef enum EOutcome
{
    EOC_OK,
    EOC_NOK,
    EOC_UNKNOWN,
    EOC_ALREADY_EXISTS,
    EOC_INVALID_ARGUMENT,
    EOC_INTERNAL_ERROR,

} EOC;





#define SUCCESS(Src,Msg) printf("[" #Src "] " #Msg "\n");
#define ERROR(Src,Msg) fprintf(stderr, "[" #Src "]" #Msg "\n");
#define FSUCCESS(Src,Msg,...) printf("[" #Src "] " #Msg "\n", ##__VA_ARGS__);
#define FERROR(Src,Msg,...) fprintf(stderr, "[" #Src "] "#Msg "\n", ##__VA_ARGS__);

#define _I_SHOT_BUFFER_SIZE_ 512

enum ECmd
{
    Join,
    Tell,
    Leave
};

/**
 * Structure en-tête de commande.
 * Envoyée juste après le ECmd dans le buffer.
*/
typedef struct TShotCheck
{
    unsigned long uTs;
    int nSeed;
} TSHOTCHECK;

typedef struct TJoinArgs
{
    
} TJOINARGS;

typedef struct TTellArgs
{

} TTELLARGS;

typedef struct TLeaveArgs
{

} TLEAVEARGS;



extern const char* g_CmdLabel [];

#define CMD_GET_LABEL(eCmd) g_CmdLabel[eCmd]

typedef struct TShot
{
    enum ECmd eCmd;
    TSHOTCHECK CmdCheck;
    char Buffer[_I_SHOT_BUFFER_SIZE_];
} TSHOT;
#endif // _COMMON_H