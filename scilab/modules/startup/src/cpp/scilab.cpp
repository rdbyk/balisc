/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2006-2008 - DIGITEO - Bruno JOFRET
 * Copyright (C) 2013 - Scilab Enterprises - Antoine ELIAS
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


#ifdef _MSC_VER
#pragma comment(lib,"../../../../../bin/libintl.lib")
#endif

#include <cstdio>
#include <iostream>
#include <string.h>
#include <setjmp.h>

extern "C"
{
#ifdef __APPLE__
#include "initMacOSXEnv.h"
#endif
#include "InitScilab.h"
#include "charEncoding.h"
#include "scilabRead.h"
#include "ConsoleRead.h"
#include "version.h"
#include "sci_malloc.h"
#include "lasterror.h"
#include "getpipeline.h"

    extern char *getCmdLine(void);

#ifdef _MSC_VER
#include "FilesAssociations.h"
#include "PATH_MAX.h"
    jmp_buf ScilabJmpEnv;
#include "WindowShow.h"
#else
#include "cliDisplayManagement.h"
    extern jmp_buf ScilabJmpEnv;
#endif
#include "isatty.hxx"
}

#include "configvariable.hxx"
#include "exit_status.hxx"
#include "scilabWrite.hxx"

#define INTERACTIVE     -1

extern "C"
{
#ifdef ENABLE_MPI
#include "initMPI.h"
#endif
#include "strcmp.h"
}

/*
** Usage
**
** Display usage : options available
*/
static void usage(void)
{
    std::cerr << "Usage: Scilab <options>" << std::endl;
    std::cerr << "      -e Instruction   : execute the scilab instruction given in Instruction argument." << std::endl;
    std::cerr << "                         -e and -f arguments are mutually exclusive." << std::endl;
    std::cerr << "      -f File          : execute the scilab script given in File argument." << std::endl;
    std::cerr << "                         -e and -f arguments are mutually exclusive." << std::endl;
    std::cerr << "      -quit            : force scilab exit after execution of script from -e or -f argument." << std::endl;
    std::cerr << "                         this flag is ignored if it is not used with -e or -f argument." << std::endl;
    std::cerr << "      -l lang          : Change the language of scilab ( default : en_US )." << std::endl;
    std::cerr << "      -nw              : Enable console mode." << std::endl;
    std::cerr << "      -nwni            : Enable terminal mode." << std::endl;
    std::cerr << "      -ns              : Don't execute etc/scilab.start." << std::endl;
    std::cerr << "      --help           : Display this help." << std::endl;
    std::cerr << "      -scihome <dir>   : Force SCIHOME to <dir>." << std::endl;
    std::cerr << "Developer Trace arguments:" << std::endl;
    std::cerr << "      --parse-trace    : Display bison state machine evolution." << std::endl;
    std::cerr << "      --AST-trace      : Display ASCII-art AST to be human readable." << std::endl;
    std::cerr << "      --pretty-print   : Display pretty-printed code, standard Scilab syntax." << std::endl;
    std::cerr << " " << std::endl;
    std::cerr << "Developer Timer arguments:" << std::endl;
    std::cerr << "      --AST-timed      : Time each AST node." << std::endl;
    std::cerr << "      --timed          : Time global execution." << std::endl;
    std::cerr << " " << std::endl;
    std::cerr << "Developer Debug arguments:" << std::endl;
    std::cerr << "      --no-exec        : Only do Lexing/parsing do not execute instructions." << std::endl;
    std::cerr << "      --context-dump   : Display context status." << std::endl;
    std::cerr << "      --exec-verbose   : Display command before running it." << std::endl;
    std::cerr << "      --timeout delay  : Kill the Scilab process after a delay." << std::endl;
}

/*
** Get Options
**
*/
static int get_option(const int argc, char *argv[], ScilabEngineInfo* _pSEI)
{
    int i = 0;

#ifdef DEBUG
    std::cerr << "-*- Getting Options -*-" << std::endl;
#endif

    for (i = 1; i < argc; ++i)
    {
        if (!balisc_strcmp("--parse-trace", argv[i]))
        {
            _pSEI->iParseTrace = 1;
        }
        else if (!balisc_strcmp("--pretty-print", argv[i]))
        {
            _pSEI->iPrintAst = 1;
        }
        else if (!balisc_strcmp("--help", argv[i]))
        {
            usage();
            exit(WELL_DONE);
        }
        else if (!balisc_strcmp("--AST-trace", argv[i]))
        {
            _pSEI->iDumpAst = 1;
        }
        else if (!balisc_strcmp("--no-exec", argv[i]))
        {
            _pSEI->iExecAst = 0;
        }
        else if (!balisc_strcmp("--context-dump", argv[i]))
        {
            _pSEI->iDumpStack = 1;
        }
        else if (!balisc_strcmp("--timed", argv[i]))
        {
            _pSEI->iTimed = 1;
            ConfigVariable::setTimed(true);
        }
        else if (!balisc_strcmp("--serialize", argv[i]))
        {
            _pSEI->iSerialize = 1;
            ConfigVariable::setSerialize(true);
        }
        else if (!balisc_strcmp("--AST-timed", argv[i]))
        {
            std::cout << "Timed execution" << std::endl;
            _pSEI->iAstTimed = 1;
        }
        else if (!balisc_strcmp("--parse-file", argv[i]))
        {
            i++;
            if (argc >= i)
            {
                _pSEI->pstParseFile = argv[i];
            }
        }
        else if (!balisc_strcmp("-quit", argv[i]))
        {
            _pSEI->iForceQuit = 1;
        }
        else if (!balisc_strcmp("-version", argv[i]))
        {
            i++;
            if (argc >= i)
            {
                _pSEI->iShowVersion = 1;
            }
        }
        else if (!balisc_strcmp("-f", argv[i]))
        {
            i++;
            if (argc >= i)
            {
                _pSEI->pstFile = argv[i];
            }
        }
        else if (!balisc_strcmp("-e", argv[i]))
        {
            i++;
            if (argc >= i)
            {
                _pSEI->pstExec = argv[i];
            }
        }
        else if (!balisc_strcmp("-O", argv[i]))
        {
            i++;
            if (argc >= i)
            {
                _pSEI->pstExec = argv[i];
                _pSEI->iCodeAction = 0;
            }
        }
        else if (!balisc_strcmp("-X", argv[i]))
        {
            i++;
            if (argc >= i)
            {
                _pSEI->pstExec = argv[i];
                _pSEI->iCodeAction = 1;
            }
        }
        else if (!balisc_strcmp("-P", argv[i]))
        {
            i++;
            if (argc >= i)
            {
                _pSEI->pstExec = argv[i];
                _pSEI->iCodeAction = 2;
            }
        }
        else if (!balisc_strcmp("-l", argv[i]))
        {
            i++;
            if (argc >= i)
            {
                _pSEI->pstLang = argv[i];
            }
        }
        else if (!balisc_strcmp("-nw", argv[i]))
        {
            _pSEI->iConsoleMode = 1;
        }
        else if (!balisc_strcmp("-nwni", argv[i]))
        {
            _pSEI->iConsoleMode = 1;
            _pSEI->iNoJvm = 1;
        }
        else if (!balisc_strcmp("-ns", argv[i]))
        {
            _pSEI->iNoStart = 1;
        }
        else if (!balisc_strcmp("-nb", argv[i]))
        {
            _pSEI->iNoBanner = 0;
        }
        else if (!balisc_strcmp("--exec-verbose", argv[i]))
        {
            _pSEI->iExecVerbose = 1;
        }
        else if (!balisc_strcmp("-nocolor", argv[i]))
        {
#ifndef _MSC_VER
            setCLIColor(FALSE);
#endif
        }
        else if (!balisc_strcmp("--timeout", argv[i]))
        {
            i++;
            if (argc > i)
            {
                char* timeout = argv[i];

                char* str_end = NULL;
                int iTimeoutDelay = strtol(timeout, &str_end, 0);

                int modifier;
                switch (*str_end)
                {
                    case 'd':
                        modifier = 86400;
                        break;
                    case 'h':
                        modifier = 3600;
                        break;
                    case 'm':
                        modifier = 60;
                        break;
                    case 's':
                    case '\0': // no modifiers
                        modifier = 1;
                        break;
                    default:
                        std::cerr << "Invalid timeout delay unit: s (for seconds, default), m (for minutes), h (for hours), d (for days) are supported" << std::endl;
                        exit(EXIT_FAILURE);
                        break;
                }

                _pSEI->iTimeoutDelay = iTimeoutDelay * modifier;
            }
            else
            {
                std::cerr << "Unspecified timeout delay" << std::endl;
                exit(EXIT_FAILURE);
            }

        }
        else if (!balisc_strcmp("-keepconsole", argv[i]))
        {
            _pSEI->iKeepConsole = 1;
        }
        else if (!balisc_strcmp("--webmode", argv[i]))
        {
            _pSEI->iWebMode = 1;
        }
        else if (!strcmp("-scihome", argv[i]))
        {
            i++;
            if (argc >= i)
            {
                _pSEI->pstSciHome = argv[i];
            }
        }
    }

    ConfigVariable::setCommandLineArgs(argc, argv);
    return 0;
}

extern "C"
{
#include <stdio.h>

#ifndef _MSC_VER
#include <unistd.h>
#endif
    extern char *getCmdLine(void);
    extern void ConsolePrintf(const char *);
}

static void TermPrintf(const char *text)
{
    //std::cout << text;
    printf("%s", text);
}

/*
** -*- MAIN -*-
*/
#if defined(_WIN32) && !defined(WITHOUT_GUI) && defined(WITH_CONSOLE_JAVA)
int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR szCmdLine, int iCmdShow)
{
    LPWSTR *szArglist = NULL;
    int argc = 0;
    szArglist = CommandLineToArgvW(GetCommandLineW(), &argc);
    char** argv = new char*[argc];
    for (int i = 0; i < argc; ++i)
    {
        argv[i] = wide_string_to_UTF8(szArglist[i]);
    }

    setWindowShowMode(iCmdShow);

#else
int main(int argc, char *argv[])
{
#endif
    int iRet = 0;

#ifdef ENABLE_MPI
    initScilabMPI();
#endif

    ScilabEngineInfo* pSEI = InitScilabEngineInfo();
#ifdef WITHOUT_GUI
    /* Building Scilab-cli-bin. We won't ever had the gui nor the jvm */
    pSEI->iConsoleMode = 1;
    pSEI->iNoJvm = 1;
    setScilabMode(SCILAB_NWNI);
#else
    setScilabMode(SCILAB_STD);
#endif

    //#if defined(_WIN32) && !defined(WITHOUT_GUI)
    //    {
    //        LPSTR my_argv[256];
    //        int nArgs = 0;
    //        LPWSTR *szArglist = CommandLineToArgvW(GetCommandLineW(), &nArgs);
    //        if (szArglist)
    //        {
    //            for (int i = 0; i < nArgs; i++)
    //            {
    //                my_argv[i] = wide_string_to_UTF8(szArglist[i]);
    //            }
    //            LocalFree(szArglist);
    //        }
    //        get_option(nArgs, my_argv, pSEI);
    //    }
    //#else
    get_option(argc, argv, pSEI);
    //#endif

    // if WITHOUT_GUI is defined
    // force Terminal IO -> Terminal IO + StartScilabEngine

    // WITHOUT_GUI (All Platform) => Terminal IO + StartScilabEngine
    // GUI (MacOSX) =>      [no option]     -> Console IO + InitMacOSXEnv
    //                      | [-nwni]       -> Terminal IO + StartScilabEngine
    //                      | [-nw]         -> Terminal IO + InitMacOSXEnv
#ifndef WITHOUT_GUI
#ifdef _MSC_VER
    #ifndef WITH_CONSOLE_JAVA
        pSEI->iConsoleMode = SCILAB_NW;
    #endif
#endif
    if (pSEI->iConsoleMode)
    {
        setScilabMode(SCILAB_NW);
        setScilabInputMethod(&getCmdLine);
        setScilabOutputMethod(&TermPrintf);
#if defined(__APPLE__)
        if (pSEI->iNoJvm == 0)
        {
            return initMacOSXEnv(pSEI);
        }
#endif // !defined(__APPLE__)
    }
    else
    {
        setScilabMode(SCILAB_STD);
        setScilabInputMethod(&ConsoleRead);
        setScilabOutputMethod(&ConsolePrintf);

#ifdef _MSC_VER
        if (pSEI->iCodeAction != -1)
        {
            //manage calls from explorer ( double click on sce file , ... )
            char* Cmd = (char*)MALLOC(((PATH_MAX * 2) + 1) * sizeof(char));
            strcpy(Cmd, "");
            int ret = CommandByFileExtension(pSEI->pstExec, pSEI->iCodeAction, Cmd);

            if (ret && Cmd[0] != '\0')
            {
                pSEI->pstExec = Cmd; //Cmd must be freed in StartScilabEngine after process.
            }
            else
            {
                pSEI->iCodeAction = -1;
            }
        }
#endif

#if defined(__APPLE__)
        return initMacOSXEnv(pSEI);
#endif // !defined(__APPLE__)
    }
#else
    setScilabMode(SCILAB_NWNI);
    setScilabInputMethod(&getCmdLine);
    setScilabOutputMethod(&TermPrintf);
#endif // defined(WITHOUT_GUI)

#ifdef _MSC_VER
    /* if file descriptor returned is -2 stdin is not associated with an input stream */
    /* example : echo plot3d | scilex -nw -e */

    if (!isatty(_fileno(stdin)) && (_fileno(stdin) != -2) && getScilabMode() != SCILAB_STD)
#else
    if (!isatty(fileno(stdin)))
#endif
    {
        // We are in a pipe
        setScilabInputMethod(&getPipeLine);
    }

    if (pSEI->iShowVersion == 1)
    {
        disp_scilab_version();
        exit(0);
    }

    int val = setjmp(ScilabJmpEnv);
    if (!val)
    {
        iRet = StartScilabEngine(pSEI);
        if (iRet == 0)
        {
            iRet = RunScilabEngine(pSEI);
        }

        StopScilabEngine(pSEI);
        FREE(pSEI);
        return iRet;
    }
    else
    {
        // We probably had a segfault so print error
        std::wcerr << getLastErrorMessage() << std::endl;
        return val;
    }

#if defined(_WIN32) && !defined(WITHOUT_GUI) && defined(WITH_CONSOLE_JAVA)
    LocalFree(szArglist);
#endif
}

