/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2010 - DIGITEO - Allan CORNET
 * Copyright (C) 2010 - DIGITEO - Bruno JOFRET
 * Copyright (C) 2012 - 2016 - Scilab Enterprises
 * Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
 *
 * This file is hereby licensed under the terms of the GNU GPL v2.0,
 * pursuant to article 5.3.4 of the CeCILL v.2.1.
 * This file was originally licensed under the terms of the CeCILL v2.1,
 * and continues to be available under such terms.
 * For more information, see the COPYING file which you should have received
 * along with this program.
 *
 */

#include <iostream>
#include <sstream>
#include <string>
#include <iterator>
#include <set>
#include <cmath>

#include "BrowseVar.hxx"
#ifdef _MSC_VER
#ifdef max
#undef max
#endif
#ifdef min
#undef min
#endif
#endif
#include "context.hxx"
#include "double.hxx"
#include "string.hxx"

extern "C"
{
#include "BrowseVarManager.h"
#include "localization.h"
#include "sci_malloc.h"
#include "BOOL.h"
#include "getScilabJavaVM.h"
#include "Scierror.h"
#include "freeArrayOfString.h"
#include "os_string.h"
#include "api_scilab.h"
#include "strlen.h"
}

#define N_A             "N/A"
#define EMPTY_MATRIX    "[ ]"
#define LOCAL_STR       "local"
#define GLOBAL_STR      "global"
#define INHERITED_STR   "inherited"
#define STRUCT_STR      "st"
#define NEG_INF_STR     "-Inf"
#define INF_STR         "Inf"
#define NAN_STR         "NaN"
#define PLUS_STR        " + "
#define MINUS_STR       " - "
#define I_STR           "i"
#define LBRACKET_STR    "["
#define RBRACKET_STR    "]"
#define COMMA_STR       ", "
#define SEMICOLON_STR   "; "

using namespace org_scilab_modules_ui_data;
using std::string;

static std::set<string> createScilabDefaultVariablesSet();
static char * getListName(char * variableName);
static std::string formatMatrix(int nbRows, int nbCols, double *pdblReal, double *pdblImg);
static char * valueToDisplay(types::InternalType* pIT, int variableType, int nbRows, int nbCols);
void OpenBrowseVar()
{
    BrowseVar::openVariableBrowser(getScilabJavaVM());
    SetBrowseVarData();
}

void UpdateBrowseVar()
{
    if (BrowseVar::isVariableBrowserOpened(getScilabJavaVM()))
    {
        SetBrowseVarData();
    }
}

void SetBrowseVarData()
{
    SciErr err;
    int iLocalVariablesUsed = 0;
    int i = 0;

    symbol::Context* ctx = symbol::Context::getInstance();

    std::list<symbol::Variable*> lstVars;
    std::list<symbol::Library*> lstLibs;

    iLocalVariablesUsed = ctx->getVarsToVariableBrowser(lstVars);
    iLocalVariablesUsed += ctx->getLibsToVariableBrowser(lstLibs);

    char **pstAllVariableNames = new char*[iLocalVariablesUsed]();
    char **pstAllVariableVisibility = new char*[iLocalVariablesUsed]();
    char **pstAllVariableListTypes = new char*[iLocalVariablesUsed]();
    int *piAllVariableBytes = new int[iLocalVariablesUsed]();
    char **pstAllVariableSizes = new char*[iLocalVariablesUsed]();
    int *piAllVariableTypes = new int[iLocalVariablesUsed]();
    int *piAllVariableIntegerTypes = new int[iLocalVariablesUsed]();
    bool *piAllVariableFromUser = new bool[iLocalVariablesUsed]();
    /* Necessary for the plots in the var browser */
    int *piAllVariableNbRows = new int[iLocalVariablesUsed]();
    int *piAllVariableNbCols = new int[iLocalVariablesUsed]();

    int nbRows, nbCols;
    char *sizeStr = NULL;

    std::set<string> scilabDefaultVariablesSet = createScilabDefaultVariablesSet();
    int iLevel = ctx->getScopeLevel();

    // for each local variable get information
    for (auto var : lstVars)
    {
        //get top level value
        symbol::ScopedVariable* sv = var->top();
        //get value
        types::InternalType* pIT = sv->m_pIT;

        // get name
        pstAllVariableNames[i] = wide_string_to_UTF8(var->getSymbol().getName().data());

        // get visibility
        if (sv->m_globalVisible == true)
        {
            pstAllVariableVisibility[i] = os_strdup(GLOBAL_STR);
            pIT = var->getGlobalValue();
        }
        else if (sv->m_iLevel != iLevel)
        {
            pstAllVariableVisibility[i] = os_strdup(INHERITED_STR);
        }
        else
        {
            pstAllVariableVisibility[i] = os_strdup(LOCAL_STR);
        }

        // type
        err = getVarType(NULL, (int*)pIT, &piAllVariableTypes[i]);
        if (!err.iErr)
        {
            piAllVariableBytes[i] = 0;
            err = getVarDimension(NULL, (int*)pIT, &nbRows, &nbCols);
        }

        if (err.iErr)
        {
            pstAllVariableSizes[i] = os_strdup(N_A);
        }
        else if (nbRows * nbCols == 0)
        {
            pstAllVariableSizes[i] = os_strdup(EMPTY_MATRIX);
        }
        else
        {
            pstAllVariableSizes[i] = valueToDisplay(pIT, piAllVariableTypes[i], nbRows, nbCols);
            piAllVariableNbRows[i] = nbRows;
            piAllVariableNbCols[i] = nbCols;
        }

        if (piAllVariableTypes[i] == sci_ints)
        {
            // Integer case
            int iPrec       = 0;
            err = getMatrixOfIntegerPrecision(NULL, (int*)pIT, &iPrec);
            switch (iPrec)
            {
                case SCI_INT8:
                    piAllVariableIntegerTypes[i] = 8;
                    break;
                case SCI_INT16:
                    piAllVariableIntegerTypes[i] = 16;
                    break;
                case SCI_INT32:
                    piAllVariableIntegerTypes[i] = 32;
                    break;
#ifdef __SCILAB_INT64__
                case SCI_INT64:
                    piAllVariableIntegerTypes[i] = 64;
                    break;
#endif
                default:
                    piAllVariableIntegerTypes[i] = 0; // Should never occurs
                    break;
            }
        }
        else
        {
            piAllVariableIntegerTypes[i] = -1;
        }

        if (pIT->isTList() || pIT->isMList())
        {
            pstAllVariableListTypes[i] = getListName(pstAllVariableNames[i]);
        }
        else if (pIT->isStruct())
        {
            pstAllVariableListTypes[i] = os_strdup(STRUCT_STR);
        }
        else
        {
            pstAllVariableListTypes[i] = os_strdup("");
        }

        if (scilabDefaultVariablesSet.find(string(pstAllVariableNames[i])) == scilabDefaultVariablesSet.end() && piAllVariableTypes[i] != sci_lib)
        {
            piAllVariableFromUser[i] = TRUE;
        }
        else
        {
            piAllVariableFromUser[i] = FALSE;
        }

        ++i;
    }

    for (auto lib : lstLibs)
    {
        //get top level value
        symbol::ScopedLibrary* sl = lib->top();

        // get name
        pstAllVariableNames[i] = wide_string_to_UTF8(lib->getSymbol().getName().data());

        // get visibility
        if (sl->m_iLevel != iLevel)
        {
            pstAllVariableVisibility[i] = os_strdup(INHERITED_STR);
        }
        else
        {
            pstAllVariableVisibility[i] = os_strdup(LOCAL_STR);
        }
        //type
        piAllVariableTypes[i] = sci_lib;

        piAllVariableBytes[i] = 0;
        pstAllVariableSizes[i] = os_strdup(N_A);
        piAllVariableIntegerTypes[i] = -1;
        pstAllVariableListTypes[i] = os_strdup("");
        piAllVariableFromUser[i] = FALSE;
        piAllVariableNbRows[i] = 1;
        piAllVariableNbCols[i] = 1;

        ++i;
    }
    // Launch Java Variable Browser through JNI
    BrowseVar::setVariableBrowserData(getScilabJavaVM(),
                                      pstAllVariableNames, iLocalVariablesUsed,
                                      piAllVariableBytes, iLocalVariablesUsed,
                                      piAllVariableTypes, iLocalVariablesUsed,
                                      piAllVariableIntegerTypes, iLocalVariablesUsed,
                                      pstAllVariableListTypes, iLocalVariablesUsed,
                                      pstAllVariableSizes, iLocalVariablesUsed,
                                      piAllVariableNbRows, iLocalVariablesUsed,
                                      piAllVariableNbCols, iLocalVariablesUsed,
                                      pstAllVariableVisibility, iLocalVariablesUsed,
                                      piAllVariableFromUser, iLocalVariablesUsed);

    for (int i = 0; i < iLocalVariablesUsed; ++i)
    {
        FREE(pstAllVariableNames[i]);
        FREE(pstAllVariableVisibility[i]);
        FREE(pstAllVariableSizes[i]);
        FREE(pstAllVariableListTypes[i]);
    }

    delete[] pstAllVariableNames;
    delete[] pstAllVariableVisibility;
    delete[] pstAllVariableSizes;
    delete[] pstAllVariableListTypes;

    delete[] piAllVariableFromUser;
    delete[] piAllVariableBytes;
    delete[] piAllVariableTypes;
    delete[] piAllVariableIntegerTypes;
    delete[] piAllVariableNbRows;
    delete[] piAllVariableNbCols;
}

/*--------------------------------------------------------------------------*/
static std::set<string> createScilabDefaultVariablesSet()
{
    string arr[] = { "home",
                     "PWD",
                     "%tk",
                     "%pvm",
                     "MSDOS",
                     "%F",
                     "%T",
                     "%f",
                     "%t",
                     "%e",
                     "%pi",
                     "%modalWarning",
                     "%nan",
                     "%inf",
                     "SCI",
                     "WSCI",
                     "SCIHOME",
                     "TMPDIR",
                     "%gui",
                     "%fftw",
                     "%helps",
                     "%eps",
                     "%io",
                     "%i",
                     "demolist",
                     "%z",
                     "%s",
                     "$",
                     "%toolboxes",
                     "%toolboxes_dir",
                     "TICTOC",
                     "%helps_modules",
                     "%_atoms_cache",
                     "evoid", // Constant for external object
                     "jvoid", // Constant for external object Java (jims)
                     "jnull", // Constant for external object Java (jims)
                     "enull"  // Constant for external object
                   };
    int i = 0;

#define NBELEMENT 37
    std::set<string> ScilabDefaultVariables;

    for (i = 0; i < NBELEMENT; i++)
    {
        ScilabDefaultVariables.insert(arr[i]);
    }

    return ScilabDefaultVariables;
}

static char * getListName(char * variableName)
{
    SciErr sciErr;
    int *piAddr = NULL;
    int* piAddr1 = NULL;
    int iRows = 0;
    int iCols = 0;
    char **pstType;
    char *tmpChar;
    sciErr = getVarAddressFromName(NULL, variableName, &piAddr);
    if (sciErr.iErr)
    {
        return os_strdup("");
    }

    sciErr = getListItemAddress(NULL, piAddr, 1, &piAddr1);
    if (sciErr.iErr)
    {
        return os_strdup("");
    }

    if (getAllocatedMatrixOfString(NULL, piAddr1, &iRows, &iCols, &pstType))
    {

        return os_strdup("");
    }
    tmpChar = os_strdup(pstType[0]);
    freeAllocatedMatrixOfString(iRows, iCols, pstType);
    return tmpChar;
}

static char * valueToDisplay(types::InternalType* pIT, int variableType, int nbRows, int nbCols)
{
    // FIXME: Redesign and rewrite this function in clean way ...

    if (pIT->isDouble() && pIT->getAs<types::Double>()->getDims() <= 2 && pIT->getAs<types::Double>()->getSize() <= 4)
    {
        // Double 2D matrix with up to 4 elements
        types::Double* pD = pIT->getAs<types::Double>();
        return os_strdup(formatMatrix(pD->getRows(), pD->getCols(), pD->get(), pD->getImg()).c_str());
    }
    else if (pIT->isBool() &&  pIT->getAs<types::Bool>()->getSize() == 1)
    {
        // Bool scalar
        if (pIT->getAs<types::Bool>()->getFirst())
        {
            return os_strdup("%t");
        }
        else
        {
            return os_strdup("%f");
        }
    }
    else if (pIT->isString() &&  pIT->getAs<types::String>()->getSize() == 1)
    {
        // single String
        // In case of a large string (> 20 characters), we truncate it
        // and append "..."

        wchar_t ws[21];

        wcsncpy(ws, pIT->getAs<types::String>()->getFirst(), 20);
        if (ws[19] != L'\0')
        {
            ws[20] = L'\0';
        }

        char* s = wide_string_to_UTF8(ws);
        char* qs = (char *)MALLOC((balisc_strlen(s) + 4 + 1)* sizeof(char));

        if (ws[19] == L'\0')
        {
            sprintf(qs, "\"%s\"", s);
        }
        else
        {
            sprintf(qs, "\"%s...", s);
        }

        FREE(s);
        return qs;
    }
    else
    {
        if (pIT->isGenericType()) // FIXME: Is this check needed?
        {
            // size of arrays "n1 x n2 x .. x nd"
            types::GenericType* pG = pIT->getAs<types::GenericType>();
            int n = pG->getDims();
            int* d = pG->getDimsArray();
            char* s = (char *)MALLOC(12 * n * sizeof(char));

            char* ss = s;
            for (int i = 0; i < n - 1; ++i)
            {
                ss += sprintf(ss, "%dx", d[i]);
            }
            ss += sprintf(ss, "%d", d[n-1]);

            return s;
        }
        else
        {
            // FIXME: is this dead code?
            char *sizeStr = NULL;
            // 11 =strlen("2147483647")+1 (1 for security)
            sizeStr = (char *)MALLOC((11 + 11 + 1 + 1) * sizeof(char));
            sprintf(sizeStr, "%dx%d", nbRows, nbCols);
            return sizeStr;
        }
    }
}

std::string addDouble(double dbl)
{
#define PRECISION_DISPLAY 3
    std::ostringstream os;
    if (ISNAN(dbl))
    {
        os << NAN_STR;
    }
    else if (finite(dbl))
    {
        os.precision(PRECISION_DISPLAY);
        os << dbl; // Convert the double to string
    }
    else
    {
        if (dbl > 0)
        {
            os << INF_STR;
        }
        else
        {
            os << NEG_INF_STR;
        }
    }

    return os.str();
}
std::string formatMatrix(int nbRows, int nbCols, double *pdblReal, double *pdblImg)
{
    if (nbRows * nbCols == 1)
    {
        std::ostringstream os;
        std::string formated = addDouble(pdblReal[0]);

        if (pdblImg)
        {
            double img = pdblImg[0];

            if (std::signbit(img))
            {
                formated += MINUS_STR;
            }
            else
            {
                formated += PLUS_STR;
            }

            formated += addDouble(std::fabs(img));
            formated += I_STR;
        }
        return formated;
    }

    std::string formated = LBRACKET_STR;

    for (int j = 0 ; j < nbRows ; j++)
    {
        for (int i = 0 ; i < nbCols ; i++)
        {
            formated += addDouble(pdblReal[i * nbRows + j]);
            if (pdblImg)
            {
                double img = pdblImg[i * nbRows + j];

                if (std::signbit(img))
                {
                    formated += MINUS_STR;
                }
                else
                {
                    formated += PLUS_STR;
                }

                formated += addDouble(std::fabs(img));
                formated += I_STR;
            }


            if (i + 1 != nbCols) // Not the last element of the matrix
            {
                formated += COMMA_STR;
            }
        }
        if (j + 1 != nbRows) // Not the last line of the matrix
        {
            formated += SEMICOLON_STR;
        }
    }
    return formated + "]";
}
