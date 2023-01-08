#include "file.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

EOC file_create(HFILE hFile, EFILETYPE eFiletype, const char* zFilename)
{
    int fd;
    fd = open(zFilename, O_CREAT | O_RDWR);

    if(fd < 0)
    {
        ERROR("FILE:create_couple_list_file", "Erreur lors de la création du fichier.")
        return false;
    }

    return true;
}

EOC file_open(const char* zFilename, EFILETYPE eFiletype, HFILE* phFile)
{

}

EOC file_close(HFILE hFile)
{
    
}