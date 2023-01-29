#ifndef _FILE_H
#define _FILE_H

#include "Common.h"
#include <stdbool.h>


typedef enum EFileType
{
    SimpleListFile,
    CoupleListFile,
    EFileType_Count
} EFILETYPE;

typedef struct TFile
{
    int nDescriptor;
    EFILETYPE eFileType;
    
} TFILE;

typedef TFILE* TFILEPTR;
typedef TFILEPTR HFILE;

#define HFILEDESCRIPTOR(hFile) (hFile)->nDescriptor
#define HFILETYPE(hFile) (hFile)->eFileType
#define SETHFILEDESCRIPTOR(hFile, nFd) (hFile)->nDescriptor = nFd;
#define SETHFILETYPE(hFile, eType) (hFile)->eFileType = eType;
#define ALLOCHFILE(hFile) hFile = malloc(sizeof(TFILE));
#define FREEHFILE(hFile) free(hFile)
extern const char* g_fileTypeLabel[];
extern const char* g_fileTypeExt[];

/**
 * Donne le label de eFileType.
 * \return const char*
*/
#define FILETYPELABEL(eFileType) g_fileTypeLabel[eFileType]

/**
 * Donne l'extension de eFileType.
 * \return const char*
*/
#define FILETYPEEXT(eFileType) g_fileTypeExt[eFileType]

/**
 * @brief Creation d'un fichier selon le type choisi.
 * 
 * @param zFilename Nom du fichier sans extension.
 * @param eFiletype Type de fichier.
 * @param phFile HFILE généré.
 * @return EOC 
 * 
 * \note Toute extension presente dans zFilename sera ignoree !
 */
EOC file_create(const char* zFilename, EFILETYPE eFiletype, HFILE* phFile);

/**
 * @brief 
 * 
 * @param hFile 
 * @param eFiletype 
 * @param zFilename 
 * @return EOC 
 */
EOC file_open(const char* zFilename, EFILETYPE eFiletype, HFILE* hFile);


/**
 * 
*/
EOC file_close(HFILE* hFile);

EOC file_add_simple(HFILE hFile, const char* zElem);

EOC file_add_couple(HFILE hFile, const char* zElemA, const char* zElemB);

#endif // _FILE_H