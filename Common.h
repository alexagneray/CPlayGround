#ifndef _COMMON_H
#define _COMMON_H

#include <stdio.h>
#include <string.h>


/**
 * @brief Labellisation des enum.
 * Une enum doit contenir une valeur finale commencant par le nom de l'enum suivi de _Count.
 * Exemple pour l'enum EOutcome -> EOutcome_Count doit etre la derniere valeur de l'enum.
 * 
 */
#define __I_LABELIZER_VAR_NAME g_EnumLabel
#define LABELIZER_DEF(Enum) const char* _I_LABELIZER_VAR_NAME[ (Enum)_Count ];
#define EXTERN_LABELIZER_DEF(Enum) extern LABELIZER_DEF( ##Enum )
#define LABELIZER_ADD_VALUE(Enum, EnumVal, EnumLabel) _I_LABELIZER_VAR_NAME[##EnumVal] = ##EnumLabel;

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
    EOutcome_Count
} EOC;

extern const char* g_OutcomeLabel[];

/**
 * @brief Donne le label de eOutcome.
 * 
 */
#define OUTCOMEGETLABEL(eOutcome) g_OutcomeLabel[eOutcome]



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