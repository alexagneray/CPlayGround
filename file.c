#include "file.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

#define __I_MAX_STRING_SIZE 255
#define __I_MAX_EXT_SIZE 32

const char* g_fileTypeLabel[] =
{
    "SimpleListFile",
    "CoupleListFile"
};

const char* g_fileTypeExt[] =
{
    ".sp.list",
    ".cp.list"
};

EOC file_create(const char* zFilename, EFILETYPE eFiletype, HFILE* phFile)
{
    if(eFiletype >= EFileType_Count
        || strlen(zFilename) > __I_MAX_STRING_SIZE)
    {
        return EOC_INVALID_ARGUMENT;
    }

    const char* zExt = FILETYPEEXT(eFiletype);

    char* pSavePtr;
    char zCompleteFilename[__I_MAX_STRING_SIZE + __I_MAX_EXT_SIZE + 1];
    strcpy(&zCompleteFilename[0], zFilename);

    // On supprime toute extension presente dans zFileName
    strtok_r(zCompleteFilename, ".", &pSavePtr);

    strcat(zCompleteFilename, zExt);

    int fd;
    fd = open(zCompleteFilename, O_CREAT | O_RDWR);
    
    if(fd < 0)
    {
        ERROR("FILE:create_couple_list_file", "Erreur lors de la création du fichier.")
        return EOC_ALREADY_EXISTS;
    }

    ALLOCHFILE(*phFile)
    SETHFILEDESCRIPTOR(*phFile, fd)
    SETHFILETYPE(*phFile, eFiletype)

    return EOC_OK;
}

EOC file_open(const char* zFilename, EFILETYPE eFiletype, HFILE* phFile)
{
    if(eFiletype >= EFileType_Count
        || strlen(zFilename) > __I_MAX_STRING_SIZE)
    {
        return EOC_INVALID_ARGUMENT;
    }

    const char* zExt = FILETYPEEXT(eFiletype);

    char* pSavePtr;
    char zCompleteFilename[__I_MAX_STRING_SIZE + __I_MAX_EXT_SIZE + 1];
    strcpy(&zCompleteFilename[0], zFilename);

    // On supprime toute extension presente dans zFileName
    strtok_r(zCompleteFilename, ".", &pSavePtr);

    strcat(zCompleteFilename, zExt);

    int fd = open(zCompleteFilename, O_WRONLY);

    ALLOCHFILE(*phFile);
    SETHFILEDESCRIPTOR(*phFile, fd)
    SETHFILETYPE(*phFile, eFiletype)

    return EOC_OK;

}

EOC file_close(HFILE hFile)
{
    close(HFILEDESCRIPTOR(hFile));
}