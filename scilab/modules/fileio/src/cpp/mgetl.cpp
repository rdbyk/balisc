/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2010 - DIGITEO - Allan CORNET
 * Copyright (C) 2010 - DIGITEO - Antoine ELIAS
 * Copyright (C) 2012 - 2016 - Scilab Enterprises
 * Copyright (C) 2017 - 2018 Dirk Reusch, Kybernetik Dr. Reusch
 *
 * This file is hereby licensed under the terms of the GNU GPL v2.0,
 * pursuant to article 5.3.4 of the CeCILL v.2.1.
 * This file was originally licensed under the terms of the CeCILL v2.1,
 * and continues to be available under such terms.
 * For more information, see the COPYING file which you should have received
 * along with this program.
 *
 */
/*--------------------------------------------------------------------------*/

extern "C"
{
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "mgetl.h"
#include "freeArrayOfString.h"
#include "charEncoding.h"
#include "sci_malloc.h"
#include "strcmp.h"
}
#include "filemanager.hxx"

static const unsigned char UTF8_BOM[] = { 0xEF, 0xBB, 0xBF, 0x00 };

static void remove_linebreak(char* line, size_t n)
{
    if (n && line[--n] == '\n')
    {
        line[n] = '\0';
        if (n && line[--n] == '\r')
        {
            line[n] = '\0';
        }
    }
}

int mgetl(int iFileID, int iLineCount, wchar_t ***pwstLines)
{
    *pwstLines = NULL;

    // get file descriptor
    types::File* pFile = FileManager::getFile(iFileID);
    FILE *fd;
    if (pFile != NULL)
    {
        fd = pFile->getFiledesc();
    }
    else
    {
        return -1;
    }

    if (iLineCount == 0)
    {
        return 0;
    }

    // check file is not empty
    if (ftell(fd) == 0)
    {
        char cValues[4] = { 0x00, 0x00, 0x00, 0x00 };
        if (fgets(cValues, 4 * sizeof(char), fd) != NULL)
        {
            // skip BOM
            if (balisc_strcmp(cValues, (const char*) UTF8_BOM) != 0)
            {
                rewind(fd);
            }
        }
    }

    if (iLineCount > 0)
    {
        *pwstLines = (wchar_t**)MALLOC(iLineCount * sizeof(wchar_t*));
        if (*pwstLines == NULL)
        {
            return -1;
        }

        char *line = NULL;
        size_t len = 0;
        ssize_t nread;
        int iReadLineCount = 0;

        while (iReadLineCount < iLineCount && (nread = getline(&line, &len, fd)) != -1)
        {
            remove_linebreak(line, nread);
            (*pwstLines)[iReadLineCount++] = to_wide_string(line);
        }

        FREE(line);
        return iReadLineCount;
    }
    else
    {
        char *line = NULL;
        size_t len = 0;
        ssize_t nread;
        int iReadLineCount = 0;

        while ((nread = getline(&line, &len, fd)) != -1)
        {
            wchar_t **pwstLinesNew = (wchar_t**)REALLOC(*pwstLines, (iReadLineCount + 1) * sizeof(wchar_t*));
            if (pwstLinesNew == NULL)
            {
                FREE(*pwstLines);
                FREE(line);
                return -1;
            }
            *pwstLines = pwstLinesNew;

            remove_linebreak(line, nread);
            (*pwstLines)[iReadLineCount++] = to_wide_string(line);
        }

        FREE(line);
        return iReadLineCount;
    }
}
