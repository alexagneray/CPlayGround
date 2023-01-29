#include "file.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <netdb.h>

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
    fd = open(zCompleteFilename, O_CREAT | O_RDWR, 0777);
    
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

    int fd = open(zCompleteFilename, O_WRONLY | O_APPEND);
    int nErr = errno;
    
    if(fd == -1)
    {
        printf("%s\n", gai_strerror(nErr));
    }

    ALLOCHFILE(*phFile);
    SETHFILEDESCRIPTOR(*phFile, fd)
    SETHFILETYPE(*phFile, eFiletype)

    return EOC_OK;

}

EOC file_close(HFILE* hFile)
{
    EOC eoc = EOC_OK;
    if(close(HFILEDESCRIPTOR(*hFile)) == -1)
    {
        eoc = EOC_UNKNOWN;
    }
    FREEHFILE(*hFile);
    *hFile = NULL;

    return eoc;
}


EOC __i_file_write_line(HFILE hFile, const char* zLine)
{
    int fd = hFile->nDescriptor;
    int nBufSize = strlen(zLine);
    
    int ret = write(hFile->nDescriptor, zLine, nBufSize);
    if(ret == -1)
    {
        return EOC_INTERNAL_ERROR;
    }

    ret = (hFile->nDescriptor, "\r\n", 2);
    if(ret == -1)
    {
        return EOC_INTERNAL_ERROR;
    }

    return EOC_OK;
}

EOC file_add_simple(HFILE hFile, const char* zElem)
{
    if(!hFile)
    {
        return EOC_FILE_NOT_OPENED;
    }

    if(hFile->eFileType != SimpleListFile)
    {
        return EOC_WRONG_FILETYPE;
    }

    return __i_file_write_line(hFile, zElem);
    
}

EOC file_add_couple(HFILE hFile, const char* zElemA, const char* zElemB)
{
    if(!hFile)
    {
        return EOC_FILE_NOT_OPENED;
    }

    if(hFile->eFileType != SimpleListFile)
    {
        return EOC_WRONG_FILETYPE;
    }

    int nSizeA = strlen(zElemA);
    int nSizeB = strlen(zElemB);
    int nBufSize = nSizeA + nSizeB + 2;

    char zLine[nBufSize];
    strcpy(&zLine[0], zElemA);
    strcat(zLine, " ");
    strcat(zLine, zElemB);

    return __i_file_write_line(hFile, zLine);
}