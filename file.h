#ifndef _FILE_H
#define _FILE_H

#include "Common.h"
#include <stdbool.h>


typedef enum EFileType
{
    CoupleListFile
} EFILETYPE;

typedef struct TFile
{
    int nDescriptor;
    EFILETYPE eFileType;
    
} TFILE;

typedef TFILE* TFILEPTR;
typedef TFILEPTR HFILE;

/**
 * 
*/
EOC file_open(const char* zFilename, EFILETYPE eFiletype, HFILE* phFile);

/**
 * 
*/
EOC file_create(HFILE hFile, EFILETYPE eFiletype, const char* zFilename);


/**
 * 
*/
EOC file_close(HFILE hFile);

#endif // _FILE_H