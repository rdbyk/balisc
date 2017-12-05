/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2007 - INRIA - Allan CORNET
 * Copyright (C) 2012 - 2016 - Scilab Enterprises
 * Copyright (C) 2017 - Dirk Reusch, Kybernetik Dr. Reusch
 *
 * This file is hereby licensed under the terms of the GNU GPL v2.0,
 * pursuant to article 5.3.4 of the CeCILL v.2.1.
 * This file was originally licensed under the terms of the CeCILL v2.1,
 * and continues to be available under such terms.
 * For more information, see the COPYING file which you should have received
 * along with this program.
 *
 */
#include <string.h>
#include "commandwords.h"
#include "sci_malloc.h"
#include "BOOL.h"
#include "os_string.h"
#include "strcmp.h"

/*--------------------------------------------------------------------------*/
/* if you update command.f , please update this file too ... */
/*--------------------------------------------------------------------------*/
static const int nbrCommands = 29;
/*--------------------------------------------------------------------------*/
static char *CommandWords[] =
{
    "abort",
    "apropos",
    "break",
    "case",
    "catch",
    "clc",
    "clear",
    "continue",
    "do",
    "else",
    "elseif",
    "end",
    "endfunction",
    "exit",
    "function",
    "for",
    "help",
    "if",
    "pause",
    "pwd",
    "quit",
    "resume",
    "return",
    "select",
    "then",
    "try",
    "what",
    "while",
    "who"
};
/*--------------------------------------------------------------------------*/
char **getcommandkeywords(int *sizearray)
{
    char **keywords = NULL;

    keywords = (char**)MALLOC(sizeof(char*) * nbrCommands);

    if (keywords)
    {
        int i = 0;
        for (i = 0; i < nbrCommands; i++)
        {
            keywords[i] = os_strdup(CommandWords[i]);
        }
        *sizearray =  nbrCommands;
    }
    else
    {
        *sizearray = 0;
    }

    return keywords;
}
/*--------------------------------------------------------------------------*/
