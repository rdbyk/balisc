/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2008-2008 - DIGITEO - Antoine ELIAS
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

#include "configvariable.hxx"
#include "callable.hxx"
#include "cell.hxx"
#include "context.hxx"
#include "execvisitor.hxx"
#include "macrofile.hxx"
#include "threadId.hxx"
#include "threadmanagement.hxx"
#include <iomanip>
#include <list>
#include <vector>

extern "C"
{
#include "FileExist.h"
#include "elem_common.h"
#include "os_string.h"
#include "sci_malloc.h"
#include "strsubst.h"
}

/*
** Module List
** \{
*/
std::list<std::wstring> ConfigVariable::m_ModuleList;
/*
** \}
*/

/*
** SCI
** \{
*/
std::wstring ConfigVariable::m_SCIPath;
/*
** \}
*/

/*
** SCIHOME
** \{
*/
std::wstring ConfigVariable::m_SCIHOME;
/*
** \}
*/

/*
** TMPDIR
** \{
*/
std::wstring ConfigVariable::m_TMPDIR;
/*
** \}
*/

/*
** Force Quit
** \{
*/
bool ConfigVariable::m_bForceQuit = false;
/*
** \}
*/

/*
** Exit Status
** \{
*/
int ConfigVariable::m_iExitStatus = 0;
/*
** \}
*/

/*
** Digit precision, ex format function
** \{
*/
int ConfigVariable::m_iFormatSize = 0;
int ConfigVariable::m_iFormatMode = 0;
/*
** \}
*/

/*
** Screen console width
** \{
*/
int ConfigVariable::m_iConsoleWidth = 0;
/*
** \}
*/

/*
** Screen console lines
** \{
*/
int ConfigVariable::m_iConsoleLines = 0; //console lines default value
/*
** \}
*/

/*
** Scilab mode
** \{
*/
int ConfigVariable::m_iScilabMode = 1; //SCILAB_API = 1  Scilab is launch as an API
/*
** \}
*/

/*
** Warning Mode
** \{
*/
bool ConfigVariable::m_bWarningMode = true;
/*
** \}
*/
/*
** \}
*/

/*
** Warning Stop
** \{
*/
bool ConfigVariable::m_bWarningStop = false;
/*
** \}
*/

/*
** HOME
** \{
*/
std::wstring ConfigVariable::m_HOME;
/*
** \}
*/

/*
** Clear last error information
** \{
*/
bool ConfigVariable::m_bLastErrorCall = false;
/*
** \}
*/

/*
** Last Error Message
** \{
*/
std::wstring ConfigVariable::m_wstError;
/*
** \}
*/

/*
** Last Error ID
** \{
*/
int ConfigVariable::m_iError = 0;
bool ConfigVariable::m_bError = false;
/*
** \}
*/

/*
** Last Error Line
** \{
*/
int ConfigVariable::m_iErrorLine = 0;
/*
** \}
*/

/*
** Last Error Function
** \{
*/
std::wstring ConfigVariable::m_wstErrorFunction = L"";
/*
** \}
*/

/* verbose */
bool ConfigVariable::m_bVerbose = true;

/* silent error */
bool ConfigVariable::m_iSilentError = false;

/* Prompt Mode */
int ConfigVariable::m_iPromptMode = 0;

// Prompt  Print Mode
// mode    (bits: input,output,compact,interactive)
//--------------------------------------------------
//  -1      0000
//   0      0110
//   1      1110
//   2      0100
//   3      1100
//   4      1111
//   7      1101

int ConfigVariable::m_iPrintMode = ConfigVariable::PrintMode::INPUT | ConfigVariable::PrintMode::OUTPUT;

const int ConfigVariable::m_iPromptToPrintMode[] =
{
    // Prompt Mode
    // -1
    ConfigVariable::PrintMode::COMPACT,
    // 0
    ConfigVariable::PrintMode::OUTPUT |
    ConfigVariable::PrintMode::COMPACT,
    // 1 = 5
    ConfigVariable::PrintMode::INPUT |
    ConfigVariable::PrintMode::OUTPUT |
    ConfigVariable::PrintMode::COMPACT,
    // 2
    ConfigVariable::PrintMode::OUTPUT,
    // 3
    ConfigVariable::PrintMode::INPUT |
    ConfigVariable::PrintMode::OUTPUT,
    // 4
    ConfigVariable::PrintMode::INPUT |
    ConfigVariable::PrintMode::OUTPUT |
    ConfigVariable::PrintMode::COMPACT |
    ConfigVariable::PrintMode::INTERACTIVE,
    // 5 = 1
    ConfigVariable::PrintMode::INPUT |
    ConfigVariable::PrintMode::OUTPUT |
    ConfigVariable::PrintMode::COMPACT,
    // 6 = 7
    ConfigVariable::PrintMode::INPUT |
    ConfigVariable::PrintMode::OUTPUT |
    ConfigVariable::PrintMode::INTERACTIVE,
    // 7 = 6
    ConfigVariable::PrintMode::INPUT |
    ConfigVariable::PrintMode::OUTPUT |
    ConfigVariable::PrintMode::INTERACTIVE
};

void ConfigVariable::setPromptMode(int _iPromptMode)
{
    int i = _iPromptMode;

    m_iPromptMode = i;
    // map prompt mode (-1 .. 7) to index of print mode array (0 .. 8)
    // if index is out of range (0 .. 8), then we use 0 as default
    m_iPrintMode = m_iPromptToPrintMode[(unsigned int)(++i) <= 8 ? i : 0];
}

/*
** Prompt Mode
** \{
*/

int ConfigVariable::m_iPauseLevel = 0;
std::list<int> ConfigVariable::m_listScope;
/*
** \}
*/

/*
** Dynamic Link
** \{
*/

std::vector<ConfigVariable::DynamicLibraryStr*> ConfigVariable::m_DynLibList;
std::list<ConfigVariable::EntryPointStr*> ConfigVariable::m_EntryPointList;

ConfigVariable::DynamicLibraryStr* ConfigVariable::getNewDynamicLibraryStr()
{
    DynamicLibraryStr* pDL = (DynamicLibraryStr*)MALLOC(sizeof(DynamicLibraryStr));
    pDL->pwstLibraryName = NULL;
    pDL->hLib = 0;
    return pDL;
}

ConfigVariable::EntryPointStr* ConfigVariable::getNewEntryPointStr()
{
    EntryPointStr* pEP = (EntryPointStr*)MALLOC(sizeof(EntryPointStr));
    pEP->bOK = false;
    pEP->functionPtr = NULL;
    pEP->iLibIndex = -1;
    pEP->pwstEntryPointName = NULL;
    return pEP;
}

void ConfigVariable::setLibraryName(ConfigVariable::DynamicLibraryStr* _pDynamicLibrary, wchar_t* _pwstLibraryName)
{
    if (_pDynamicLibrary)
    {
        if (_pDynamicLibrary->pwstLibraryName)
        {
            FREE(_pDynamicLibrary->pwstLibraryName);
        }
        _pDynamicLibrary->pwstLibraryName = os_wcsdup(_pwstLibraryName);
    }
}

void ConfigVariable::setEntryPointName(ConfigVariable::EntryPointStr* _pEntryPoint, wchar_t* _pwstEntryPointName)
{
    if (_pEntryPoint)
    {
        if (_pEntryPoint->pwstEntryPointName)
        {
            FREE(_pEntryPoint->pwstEntryPointName);
        }
        _pEntryPoint->pwstEntryPointName = os_wcsdup(_pwstEntryPointName);
    }
}

/* Dynamic libraries functions */
int ConfigVariable::addDynamicLibrary(ConfigVariable::DynamicLibraryStr* _pDynamicLibrary)
{
    for (int i = 0; i < (int)m_DynLibList.size(); i++)
    {
        if (m_DynLibList[i] == NULL)
        {
            m_DynLibList[i] = _pDynamicLibrary;
            return i;
        }
    }

    m_DynLibList.push_back(_pDynamicLibrary);
    return (int)m_DynLibList.size() - 1;
}

void ConfigVariable::removeDynamicLibrary(int _iDynamicLibraryIndex)
{
    if (_iDynamicLibraryIndex < (int)m_DynLibList.size())
    {
        std::list<EntryPointStr*>::const_iterator it;
        for (it = m_EntryPointList.begin(); it != m_EntryPointList.end();)
        {
            //clear all entry points linked to removed dynamic library
            if ((*it)->iLibIndex == _iDynamicLibraryIndex)
            {
                EntryPointStr* pEP = *it;
                m_EntryPointList.remove(*it);
                FREE(pEP->pwstEntryPointName);
                FREE(pEP);
                if (m_EntryPointList.size() == 0)
                {
                    break;
                }
                it = m_EntryPointList.begin();
            }
            else
            {
                ++it;
            }
        }
        //remove dynamic library
        FREE(m_DynLibList[_iDynamicLibraryIndex]->pwstLibraryName);
        FREE(m_DynLibList[_iDynamicLibraryIndex]);
        m_DynLibList[_iDynamicLibraryIndex] = NULL;
    }

    //clean dynamic library vector
    while (m_DynLibList.size() != 0 && m_DynLibList.back() == NULL)
    {
        m_DynLibList.pop_back();
    }
}

ConfigVariable::DynamicLibraryStr* ConfigVariable::getDynamicLibrary(int _iDynamicLibraryIndex)
{
    if (_iDynamicLibraryIndex < (int)m_DynLibList.size())
    {
        return m_DynLibList[_iDynamicLibraryIndex];
    }
    return NULL;
}

bool ConfigVariable::isDynamicLibrary(int _iDynamicLibraryIndex)
{
    if (_iDynamicLibraryIndex < (int)m_DynLibList.size())
    {
        if (m_DynLibList[_iDynamicLibraryIndex] != NULL)
        {
            return true;
        }
    }
    return false;
}

void ConfigVariable::addEntryPoint(ConfigVariable::EntryPointStr* _pEP)
{
    if (_pEP != NULL)
    {
        m_EntryPointList.push_back(_pEP);
    }
}

ConfigVariable::EntryPointStr* ConfigVariable::getEntryPoint(wchar_t* _pwstEntryPointName, int _iDynamicLibraryIndex)
{
    std::list<EntryPointStr*>::const_iterator it;
    for (it = m_EntryPointList.begin() ; it != m_EntryPointList.end() ; ++it)
    {
        //by pass iLibIndex check if _iDynamicLibraryIndex == -1
        if (_iDynamicLibraryIndex == -1 || (*it)->iLibIndex == _iDynamicLibraryIndex)
        {
            if (wcscmp((*it)->pwstEntryPointName, _pwstEntryPointName) == 0)
            {
                return *it;
            }
        }
    }
    return NULL;
}

dynlib_ptr ConfigVariable::getEntryPointFromPosition(int position)
{
    std::list<EntryPointStr*>::const_iterator it;
    int pos = 0;
    for (it = m_EntryPointList.begin(); it != m_EntryPointList.end(); ++it, ++pos)
    {
        if (pos == position)
        {
            return (*it)->functionPtr;
        }
    }
    return NULL;
}

int ConfigVariable::getEntryPointPosition(wchar_t* _pwstEntryPointName, int _iDynamicLibraryIndex)
{
    int pos = 0;
    std::list<EntryPointStr*>::const_iterator it;
    for (it = m_EntryPointList.begin(); it != m_EntryPointList.end(); ++it, ++pos)
    {
        //by pass iLibIndex check if _iDynamicLibraryIndex == -1
        if (_iDynamicLibraryIndex == -1 || (*it)->iLibIndex == _iDynamicLibraryIndex)
        {
            if (wcscmp((*it)->pwstEntryPointName, _pwstEntryPointName) == 0)
            {
                return pos;
            }
        }
    }
    return -1;
}

std::vector<std::wstring> ConfigVariable::getEntryPointNameList()
{
    std::vector<std::wstring> EntryPointNames;
    std::list<EntryPointStr*>::const_iterator it;
    for (it = m_EntryPointList.begin() ; it != m_EntryPointList.end() ; ++it)
    {
        EntryPointNames.push_back((*it)->pwstEntryPointName);
    }
    return EntryPointNames;
}

std::vector<ConfigVariable::DynamicLibraryStr*>* ConfigVariable::getDynamicLibraryList()
{
    return &m_DynLibList;
}

std::list<ConfigVariable::EntryPointStr*>* ConfigVariable::getEntryPointList()
{
    return &m_EntryPointList;
}

//dynamic modules
std::map<std::wstring, DynLibHandle> ConfigVariable::m_DynModules;

void ConfigVariable::addDynModule(const std::wstring& _name, DynLibHandle _lib)
{
    m_DynModules[_name] = _lib;
}

void ConfigVariable::removeDynModule(const std::wstring& _name)
{
    m_DynModules.erase(_name);
}

DynLibHandle ConfigVariable::getDynModule(const std::wstring& _name)
{
    std::map<std::wstring, DynLibHandle>::iterator it;
    it = m_DynModules.find(_name);
    if (it != m_DynModules.end())
    {
        return it->second;
    }

    return 0;
}

int ConfigVariable::getDynModuleCount()
{
    return (int)m_DynModules.size();
}

DynLibHandle* ConfigVariable::getAllDynModule()
{
    DynLibHandle* moduleList = new DynLibHandle[m_DynModules.size()];
    std::map<std::wstring, DynLibHandle>::iterator it = m_DynModules.begin();
    std::map<std::wstring, DynLibHandle>::iterator itEnd = m_DynModules.end();
    for (int i = 0; it != itEnd; ++it, ++i)
    {
        moduleList[i] = it->second;
    }

    return moduleList;
}

void ConfigVariable::cleanDynModule()
{
    m_DynModules.clear();
}

// Command Line Arguments
std::vector<std::wstring> ConfigVariable::m_Args;
bool ConfigVariable::m_bTimed = false;
bool ConfigVariable::m_bSerialize = false;

void ConfigVariable::setCommandLineArgs(int _iArgs, char** _pstArgs)
{
    m_Args.clear();
    for (int i = 0; i < _iArgs; i++)
    {
        wchar_t* ws = to_wide_string(_pstArgs[i]);
        m_Args.push_back(ws);
        FREE(ws);
    }
}

wchar_t** ConfigVariable::getCommandLineArgs(int* _piCount)
{
    wchar_t** pwstArgs = NULL;
    *_piCount = (int)m_Args.size();
    if (*_piCount != 0)
    {
        pwstArgs = (wchar_t**)MALLOC(*_piCount * sizeof(wchar_t*));
        for (int i = 0; i < *_piCount; i++)
        {
            pwstArgs[i] = os_wcsdup(m_Args[i].c_str());
        }
    }
    return pwstArgs;
}

bool ConfigVariable::getTimed()
{
    return m_bTimed;
}

void ConfigVariable::setTimed(bool _bTimed)
{
    m_bTimed = _bTimed;
}

bool ConfigVariable::getSerialize()
{
    return m_bSerialize;
}

void ConfigVariable::setSerialize(bool _bSerialize)
{
    m_bSerialize = _bSerialize;
}

/*
** \}
*/

///*
//** Input Method
//** \{
//*/
//
//SCILAB_INPUT_METHOD ConfigVariable::m_pInputMethod = NULL;
//
//void ConfigVariable::setInputMethod(SCILAB_INPUT_METHOD _pInputMethod)
//{
//    m_pInputMethod = _pInputMethod;
//}
//
//SCILAB_INPUT_METHOD ConfigVariable::getInputMethod(void)
//{
//    return m_pInputMethod;
//}
//
///*
//** \}
//*/
//
///*
//** Output Method
//** \{
//*/
//
//SCILAB_OUTPUT_METHOD ConfigVariable::m_pOutputMethod = NULL;
//
//void ConfigVariable::setOutputMethod(SCILAB_OUTPUT_METHOD _pOutputMethod)
//{
//    m_pOutputMethod = _pOutputMethod;
//}
//
//SCILAB_OUTPUT_METHOD ConfigVariable::getOutputMethod(void)
//{
//    return m_pOutputMethod;
//}
//
///*
//** \}
//*/

/*
** schur function
** \{
*/

types::Callable* ConfigVariable::m_schurFunction = NULL;

void ConfigVariable::setSchurFunction(types::Callable* _schurFunction)
{
    m_schurFunction = _schurFunction;
}

types::Callable* ConfigVariable::getSchurFunction()
{
    return m_schurFunction;
}

/*
** \}
*/

/*
** grand (module randlib)
** \{
*/

int ConfigVariable::m_currentBaseGen = 0;
int ConfigVariable::m_currentClcg4 = 0;

void ConfigVariable::setCurrentBaseGen(int _gen)
{
    m_currentBaseGen = _gen;
}

int ConfigVariable::getCurrentBaseGen()
{
    return m_currentBaseGen;
}

void ConfigVariable::setCurrentClcg4(int _clcg4)
{
    m_currentClcg4 = _clcg4;
}

int ConfigVariable::getCurrentClcg4()
{
    return m_currentClcg4;
}
/*
** \}
*/

/*
** Start finish flag
** \{
*/
bool ConfigVariable::m_bStartProcessing = false;
bool ConfigVariable::m_bEndProcessing = false;

void ConfigVariable::setStartProcessing(bool _bStartProcessing)
{
    m_bStartProcessing = _bStartProcessing;
}

bool ConfigVariable::getStartProcessing()
{
    return m_bStartProcessing;
}

void ConfigVariable::setEndProcessing(bool _bEndProcessing)
{
    m_bEndProcessing = _bEndProcessing;
}

bool ConfigVariable::getEndProcessing()
{
    return m_bEndProcessing;
}
/*
** \}
*/

/*
** ieee
** \{
*/
int ConfigVariable::m_iIeee = 2;
/*
** \}
*/

/*
** simp Mode
** \{
*/
int ConfigVariable::m_iSimpMode = 1;

void ConfigVariable::setSimpMode(int _iSimpMode)
{
    m_iSimpMode = _iSimpMode;
}

int ConfigVariable::getSimpMode()
{
    return m_iSimpMode;
}
/*
** \}
*/

/*
** funcprot Mode
** \{
*/
int ConfigVariable::m_iFuncprot = 1;
/*
** \}
*/

/*
** where
** \{
*/

std::vector<ConfigVariable::WhereEntry> ConfigVariable::m_Where;
std::vector<ConfigVariable::WhereErrorEntry> ConfigVariable::m_WhereError;
std::vector<int> ConfigVariable::m_FirstMacroLine;
void ConfigVariable::where_begin(int _iLineNum, int _iLineLocation, types::Callable* _pCall)
{
    const std::wstring* wstrFileName = nullptr;
    types::Callable* pCall = _pCall;
    if (pCall->isMacroFile())
    {
        types::Macro* pM = pCall->getAs<types::MacroFile>()->getMacro();
        wstrFileName = &pM->getFileName();
        pCall = pM;
    }
    else if (pCall->isMacro())
    {
        types::Macro* pM = pCall->getAs<types::Macro>();
        wstrFileName = &pM->getFileName();
    }

    m_Where.push_back({_iLineNum, _iLineLocation, symbol::Context::getInstance()->getScopeLevel(), pCall, wstrFileName});
}

void ConfigVariable::whereErrorToString(std::wostringstream& ostr)
{
    int iLenName = 1;
    bool isExecstr = false;
    bool isExecfile = false;

    // get max length of functions name and check if exec or execstr have been called.
    for (auto& where : m_WhereError)
    {
        if (isExecstr == false && where.m_function_name == L"execstr")
        {
            isExecstr = true;
            continue;
        }
        else if (isExecfile == false && where.m_function_name == L"exec")
        {
            isExecfile = true;
            continue;
        }

        iLenName = std::max((int)where.m_function_name.length(), iLenName);

        // in case of bin file, the file path and line is displayed only if the associated .sci file exists
        if (!where.m_file_name.empty() && where.m_file_name.find(L".bin") != std::wstring::npos)
        {
            std::size_t pos = where.m_file_name.find_last_of(L".");
            where.m_file_name.replace(pos, pos + 4, L".sci");
            if (FileExistW(const_cast<wchar_t*>(where.m_file_name.c_str())) == false)
            {
                where.m_file_name = L"";
            }
        }
    }

    // add margin
    iLenName++;

    // initialize localized strings
    std::wstring wstrBuiltin(_W("in builtin "));
    std::wstring wstrAtLine(_W("at line % 5d of function "));
    std::wstring wstrExecStr(_W("at line % 5d of executed string "));
    std::wstring wstrExecFile(_W("at line % 5d of executed file "));

    // compute max size between "at line xxx of function" and "in builtin "
    // +1 : line number is pad to 5. length of "% 5d" + 1 == 5
    int iMaxLen = std::max(wstrAtLine.length() + 1, wstrBuiltin.length());
    if (isExecstr)
    {
        iMaxLen = std::max(((int)wstrExecStr.length()) + 1, iMaxLen);
    }

    if (isExecstr)
    {
        iMaxLen = std::max(((int)wstrExecFile.length()) + 1, iMaxLen);
    }

    // print call stack
    ostr << std::left;
    ostr.fill(L' ');
    for (auto& where : m_WhereError)
    {
        ostr.width(iMaxLen);
        if (where.m_line == 0)
        {
            ostr << wstrBuiltin;
        }
        else
        {
            if (where.m_function_name == L"execstr")
            {
                isExecstr = true;
                wchar_t wcsTmp[bsiz];
                os_swprintf(wcsTmp, bsiz, wstrExecStr.c_str(), where.m_line);
                ostr << wcsTmp << std::endl;
                continue;
            }
            else if (where.m_function_name == L"exec")
            {
                wchar_t wcsTmp[bsiz];
                os_swprintf(wcsTmp, bsiz, wstrExecFile.c_str(), where.m_line);
                ostr << wcsTmp << where.m_file_name << std::endl;
                continue;
            }
            else
            {
                wchar_t wcsTmp[bsiz];
                os_swprintf(wcsTmp, bsiz, wstrAtLine.c_str(), where.m_line);
                ostr << wcsTmp;
            }
        }

        ostr.width(iLenName);
        ostr << where.m_function_name;

        if (!where.m_file_name.empty())
        {
            // -1 because the first line of a function dec is : "function myfunc()"
            ostr << L"( " << where.m_file_name << L" " << _W("line") << L" " << where.m_first_line + where.m_line - 1 << L" )";
        }

        ostr << std::endl;
    }

    ostr << std::endl
         << std::resetiosflags(std::ios::adjustfield);
}

void ConfigVariable::fillWhereError(int _iErrorLine)
{
    if (m_WhereError.empty())
    {
        int iTmp = 0;
        if (_iErrorLine != 0)
        {
            // +1 because the first line of the funtionDec "function func()" is the line 1.
            iTmp = _iErrorLine - getMacroFirstLines() + 1;
        }

        m_WhereError.reserve(m_Where.size());
        for (auto where = m_Where.rbegin(); where != m_Where.rend(); ++where)
        {
            if (where->m_file_name != nullptr)
            {
                m_WhereError.push_back({iTmp, where->m_absolute_line, where->call->getFirstLine(), where->call->getName(), *where->m_file_name});
            }
            else
            {
                m_WhereError.push_back({iTmp, where->m_absolute_line, where->call->getFirstLine(), where->call->getName(), L""});
            }

            iTmp = where->m_line;
        }
    }
}
/*
** \}
*/

/*
** module called with variable by reference
** \{
*/

std::list<std::wstring> ConfigVariable::m_ReferenceModules;

bool ConfigVariable::checkReferenceModule(const std::wstring& _module)
{
    for (auto ref : m_ReferenceModules)
    {
        if (ref == _module)
        {
            return true;
        }
    }

    return false;
}

void ConfigVariable::addReferenceModule(const std::wstring& _module)
{
    if (checkReferenceModule(_module) == false)
    {
        m_ReferenceModules.push_back(_module);
    }
}

void ConfigVariable::removeReferenceModule(const std::wstring& _module)
{
    if (checkReferenceModule(_module))
    {
        m_ReferenceModules.remove(_module);
    }
}

std::list<std::wstring> ConfigVariable::getReferenceModules()
{
    std::list<std::wstring> l(m_ReferenceModules);
    return l;
}

/*
** \}
*/

/*
** analyzer options
** \{
*/

int ConfigVariable::m_analyzerOptions = 0;
void ConfigVariable::setAnalyzerOptions(int _val)
{
    m_analyzerOptions = _val;
}

int ConfigVariable::getAnalyzerOptions(void)
{
    return m_analyzerOptions;
}

/*
** \}
*/

/*
** divide by zero
** \{
*/

bool ConfigVariable::m_dividebyzero = false;
void ConfigVariable::setDivideByZero(bool _dividebyzero)
{
    m_dividebyzero = _dividebyzero;
}

bool ConfigVariable::isDivideByZero(void)
{
    return m_dividebyzero;
}
/*
** \}
*/

//mex info
std::string ConfigVariable::mexFunctionName;
void ConfigVariable::setMexFunctionName(const std::string& name)
{
    mexFunctionName = name;
}

std::string& ConfigVariable::getMexFunctionName()
{
    return mexFunctionName;
}

/*
** \}
*/
// executed file with exec
int ConfigVariable::m_iFileID = 0;
void ConfigVariable::setExecutedFileID(int _iFileID)
{
    m_iFileID = _iFileID;
}

int ConfigVariable::getExecutedFileID()
{
    return m_iFileID;
}

/*
** string read from console by scilabRead
** \{
*/
std::atomic<char*> ConfigVariable::m_pcConsoleReadStr(nullptr);
void ConfigVariable::setConsoleReadStr(char* _pcConsoleReadStr)
{
    m_pcConsoleReadStr = _pcConsoleReadStr;
}

char* ConfigVariable::getConsoleReadStr()
{
    ThreadManagement::LockScilabRead();
    char* tmp = m_pcConsoleReadStr.exchange(NULL);
    ThreadManagement::UnlockScilabRead();
    return tmp;
}
/*
** \}
*/

/*
** Tell to the console thread if the scilabRead return
** is a scilab command or not.
** \{
*/
std::atomic<int> ConfigVariable::m_isScilabCommand(1);
void ConfigVariable::setScilabCommand(int _isciCmd)
{
    m_isScilabCommand = _isciCmd;
}

int ConfigVariable::isScilabCommand()
{
    return m_isScilabCommand.exchange(1);
}
/*
** \}
*/

//debugger information
bool ConfigVariable::m_bEnabledebug = false;
std::unique_ptr<ast::ConstVisitor> ConfigVariable::m_defaultvisitor(nullptr);

bool ConfigVariable::getEnableDebug()
{
    return m_bEnabledebug;
}

void ConfigVariable::setEnableDebug(bool _enable)
{
    m_bEnabledebug = _enable;
}

void ConfigVariable::setDefaultVisitor(ast::ConstVisitor* _default)
{
    m_defaultvisitor.reset(_default);
}

ast::ConstVisitor* ConfigVariable::getDefaultVisitor()
{
    if (m_defaultvisitor.get() == nullptr)
    {
        m_defaultvisitor.reset(new ast::ExecVisitor());
    }
    return m_defaultvisitor->clone();
}

bool ConfigVariable::executionbreak = false;

bool ConfigVariable::isExecutionBreak()
{
    return executionbreak;
}

void ConfigVariable::setExecutionBreak()
{
    executionbreak = true;
}

void ConfigVariable::resetExecutionBreak()
{
    executionbreak = false;
}

#ifdef _DEBUG
int ConfigVariable::recursionLimit = 25;
#else
int ConfigVariable::recursionLimit = 1000;
#endif
int ConfigVariable::recursionLevel = 0;

int ConfigVariable::getRecursionLimit()
{
    return recursionLimit;
}

int ConfigVariable::setRecursionLimit(int val)
{
    int old = recursionLimit;
    recursionLimit = std::max(10, val);
    return old;
}

int ConfigVariable::getRecursionLevel()
{
    return recursionLevel;
}

bool ConfigVariable::increaseRecursion()
{
    if (recursionLevel < recursionLimit)
    {
        ++recursionLevel;
        return true;
    }

    return false;
}

void ConfigVariable::decreaseRecursion()
{
    //recursionLevel = std::max(--recursionLevel, 0);
    --recursionLevel;
}

void ConfigVariable::resetRecursionLevel()
{
    recursionLevel = 0;
}

//webmode
bool ConfigVariable::webMode = true;

bool ConfigVariable::getWebMode()
{
    return webMode;
}

void ConfigVariable::setWebMode(bool _mode)
{
    webMode = _mode;
}
