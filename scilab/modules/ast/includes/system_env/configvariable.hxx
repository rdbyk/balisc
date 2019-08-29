/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2008-2008 - DIGITEO - Antoine ELIAS
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

#ifndef __CONFIGVARIABLE_HXX__
#define __CONFIGVARIABLE_HXX__

//disable warnings about exports STL items
#ifdef _MSC_VER
#pragma warning (disable : 4251)
#endif

#include <vector>
#include <list>
#include <map>
#include <string>
#include <memory>
#include <atomic>

#include "visitor.hxx"
#include "context.hxx"

extern "C"
{
#include "dynamiclibrary.h"
}

// Minimal values for iConsoleLines & iConsoleWidth
#define ICONSOLELINES_MIN 0
#define ICONSOLEWIDTH_MIN 10

namespace types
{
class Cell;
class ThreadId;
class Callable;
}

class ConfigVariable
{
    //module list
private :
    static std::list<std::wstring> m_ModuleList;

public :
    static void setModuleList(std::list<std::wstring>& _module_list)
    {
        m_ModuleList = _module_list;
    }

    static std::list<std::wstring> getModuleList()
    {
        return std::list<std::wstring>(m_ModuleList);
    }

    //SCI
private :
    static std::wstring m_SCIPath;

public :
    static void setSCIPath(const std::wstring& _SCIPath)
    {
        m_SCIPath = _SCIPath;
    }

    static std::wstring& getSCIPath()
    {
        return m_SCIPath;
    }
    
    //SCIHOME
private :
    static std::wstring m_SCIHOME;

public :
    static void setSCIHOME(const std::wstring& _m_SCIHOME)
    {
        m_SCIHOME = _m_SCIHOME;
    }

    static std::wstring& getSCIHOME()
    {
        return m_SCIHOME;
    }

    //TMPDIR
private :
    static std::wstring m_TMPDIR;

public :
    static void setTMPDIR(const std::wstring& _TMPDIR)
    {
        m_TMPDIR = _TMPDIR;
    }

    static std::wstring& getTMPDIR()
    {
        return m_TMPDIR;
    }

    // Force Quit
private :
    static bool m_bForceQuit;

public :
    static void setForceQuit(bool _bForceQuit)
    {
        m_bForceQuit = _bForceQuit;
    }

    static bool getForceQuit(void)
    {
        return m_bForceQuit;
    }

    // Exit Status
private :
    static int m_iExitStatus;

public :
    static void setExitStatus(int _iExitStatus)
    {
        m_iExitStatus = _iExitStatus;
    }

    static int getExitStatus(void)
    {
        return m_iExitStatus;
    }

    // Digit precision, ex format function
private :
    static int m_iFormatSize;

public :
    static void setFormatSize(int _iFormatSize)
    {
        m_iFormatSize = _iFormatSize;
    }
    
    static int getFormatSize(void)
    {
        return m_iFormatSize;
    }

    // printf format ( 0 -> "e", 1 -> "v")
private :
    static int m_iFormatMode;

public :
    static void setFormatMode(int _iFormatMode)
    {
        m_iFormatMode = _iFormatMode;
    }
    
    static int getFormatMode(void)
    {
        return m_iFormatMode;
    }

    // Screen console width
private :
    static int m_iConsoleWidth;

public :
    static void setConsoleWidth(int _iConsoleWidth)
    {
        m_iConsoleWidth = std::max(ICONSOLEWIDTH_MIN, _iConsoleWidth);
    }
    
    static int getConsoleWidth(void)
    {
        return m_iConsoleWidth;
    }

    // Screen console lines
private :
    static int m_iConsoleLines;

public :
    static void setConsoleLines(int _iConsoleLines)
    {
        m_iConsoleLines = std::max(ICONSOLELINES_MIN, _iConsoleLines);
    }

    static int getConsoleLines(void)
    {
        return m_iConsoleLines;
    }

    // Scilab mode
private :
    static int m_iScilabMode;

public :
    static void setScilabMode(int _iScilabMode)
    {
        m_iScilabMode = _iScilabMode;
    }

    static int getScilabMode(void)
    {
        return m_iScilabMode;
    }

    //Warning mode
private :
    static bool m_bWarningMode;

public :
    static void setWarningMode(bool _bWarningMode)
    {
        m_bWarningMode = _bWarningMode;
    }

    static bool getWarningMode(void)
    {
        return m_bWarningMode;
    }
    
    // WarningStop
private :
    static bool m_bWarningStop;

public :
    static void setWarningStop(bool _bWarningStop)
    {
        m_bWarningStop = _bWarningStop;
    }

    static bool getWarningStop(void)
    {
        return m_bWarningStop;
    }

    //HOME
private :
    static std::wstring m_HOME;

public :
    static void setHOME(const std::wstring& _m_HOME)
    {
        m_HOME = _m_HOME;
    }

    static std::wstring& getHOME()
    {
        return m_HOME;
    }

    //Clear last error information
public :
    static void setLastErrorClear(void);

    //Clear last error information
private :
    static bool m_bLastErrorCall;
public :
    static void setLastErrorCall(void)
    {
        m_bLastErrorCall = true;
    }

    static void clearLastError(void)
    {
        //if (m_bLastErrorCall == false)
        {
            m_wstError = L"";
            m_iError = 0;
            m_iErrorLine = 0;
            m_wstErrorFunction = L"";
        }
        m_bLastErrorCall = false;
    }

    //Last Error Message
private :
    static std::wstring m_wstError;

public :
    static void setLastErrorMessage(const std::wstring& _wstError)
    {
        m_wstError = _wstError;
    }

    static std::wstring& getLastErrorMessage()
    {
        return m_wstError;
    }

    //Last Error ID
private :
    static int m_iError;
    static bool m_bError;

public :
    static void setLastErrorNumber(int _iError)
    {
        m_iError = _iError;
    }

    static int getLastErrorNumber()
    {
        return m_iError;
    }

    static void setError()
    {
        m_bError = true;
    }

    static bool isError()
    {
        return m_bError;
    }

    static void resetError()
    {
        m_bError = false;
    }

    //Last Error Line
private :
    static int m_iErrorLine;

public :
    static void setLastErrorLine(int _iLine)
    {
        m_iErrorLine = _iLine;
    }

    static int getLastErrorLine()
    {
        return m_iErrorLine;
    }

    //Last Error Function
private :
    static std::wstring m_wstErrorFunction;
public:
    static void setLastErrorFunction(const std::wstring& _wstFunction)
    {
        m_wstErrorFunction = _wstFunction;
    }

    static std::wstring& getLastErrorFunction()
    {
        return m_wstErrorFunction;
    }

    //verbose ";" after instruction
    //set before function call to know status of e.isVerbose in functions
private:
    static bool m_bVerbose;

public :
    static void setVerbose(bool _bVerbose)
    {
        m_bVerbose = _bVerbose;
    }

    static bool getVerbose(void)
    {
        return m_bVerbose;
    }

    //silent error ( try catch, errcatch, ... )
private :
    static bool m_iSilentError;
public:
    static void setSilentError(bool _iSilentError)
    {
        m_iSilentError = _iSilentError;
    }

    static bool isSilentError(void)
    {
        return m_iSilentError;
    }

    //Prompt Mode
public :
    /*
    Prompt mode
    normal = 0,
    silent = -1,
    prompt = 2,
    exec = 1,
    exec3 = 3,
    step = 4,
    step7 = 7
    */

private :
    static int m_iPromptMode;

    static int m_iPrintMode;
    const static int m_iPromptToPrintMode[];

public:
    enum PrintMode : unsigned int
    {
        INPUT       = 1 << 0,
        OUTPUT      = 1 << 1,
        COMPACT     = 1 << 2,
        INTERACTIVE = 1 << 3
    };

    static void setPromptMode(int _iPromptMode);
    
    static int getPromptMode(void)
    {
        return m_iPromptMode;
    }

    static bool isPrintInput(void)
    {
        return m_iPrintMode & PrintMode::INPUT;
    }

    static bool isPrintOutput(void)
    {
        return m_iPrintMode & PrintMode::OUTPUT;
    }

    static bool isPrintInteractive(void)
    {
        return m_iPrintMode & PrintMode::INTERACTIVE;
    }

    static void setPrintCompact(bool val)
    {
        // cf. https://graphics.stanford.edu/~seander/bithacks.html
        m_iPrintMode ^= (-val ^ m_iPrintMode) & PrintMode::COMPACT;
    }

    static bool isPrintCompact(void)
    {
        return m_iPrintMode & PrintMode::COMPACT;
    }

    // Pause level
private :
    static int m_iPauseLevel;
    static std::list<int> m_listScope;

public :
    static void IncreasePauseLevel()
    {
        m_iPauseLevel++;
        m_listScope.push_back(symbol::Context::getInstance()->getScopeLevel());
    }

    static void DecreasePauseLevel()
    {
        m_iPauseLevel--;
        m_listScope.pop_back();
    }

    static int getPauseLevel()
    {
        return m_iPauseLevel;
    }

    static int getActivePauseLevel()
    {
        return m_listScope.back();
    }
    
    // Dynamic Libraries

    typedef struct
    {
        wchar_t* pwstLibraryName;      /** name of dynamic library **/
        DynLibHandle hLib;              /** handle of the library **/
    } DynamicLibraryStr;

    typedef void(*dynlib_ptr)();

    typedef struct
    {
        wchar_t* pwstEntryPointName;    /** name of interface **/
        int iLibIndex;                  /** name of interface **/
        dynlib_ptr functionPtr;         /** entrypoint for the interface **/
        bool bOK;                       /** flag set to TRUE if entrypoint can be used **/
    } EntryPointStr;

private :
    static std::list<EntryPointStr*> m_EntryPointList;
    static std::vector<DynamicLibraryStr*> m_DynLibList;
public :

    /* tools fucntions */
    static void setLibraryName(DynamicLibraryStr* _pDynamicLibrary, wchar_t* _pwstLibraryName);
    static void setEntryPointName(EntryPointStr* _pEntryPoint, wchar_t* _pwstEntryPointName);

    /* "Constructors" */
    static DynamicLibraryStr* getNewDynamicLibraryStr();
    static EntryPointStr* getNewEntryPointStr();

    /* Dynamic libraries functions */
    static std::vector<DynamicLibraryStr*>* getDynamicLibraryList();
    static int addDynamicLibrary(DynamicLibraryStr* _pDynamicLibrary);
    static void removeDynamicLibrary(int _iDynamicLibraryIndex);
    static DynamicLibraryStr* getDynamicLibrary(int _iDynamicLibraryIndex);
    static bool isDynamicLibrary(int _iDynamicLibraryIndex);

    /* Entry point functions */
    static std::list<EntryPointStr*>* getEntryPointList();
    static void addEntryPoint(EntryPointStr* _pEP);
    static void removeEntryPoint(int _iEntryPointIndex);
    static EntryPointStr* getEntryPoint(wchar_t* _pwstEntryPointName, int _iDynamicLibraryIndex = -1);
    static int getEntryPointPosition(wchar_t* _pwstEntryPointName, int _iDynamicLibraryIndex = -1);
    static dynlib_ptr getEntryPointFromPosition(int position);
    static std::vector<std::wstring> getEntryPointNameList();

    //dynamic modules
private :
    static std::map<std::wstring, DynLibHandle> m_DynModules;
public :
    static void addDynModule(const std::wstring& _name, DynLibHandle _lib);
    static void removeDynModule(const std::wstring& _name);
    static DynLibHandle getDynModule(const std::wstring& _name);
    static int getDynModuleCount();
    static DynLibHandle* getAllDynModule();
    static void cleanDynModule();

    // Command Line Arguments
private :
    static std::vector<std::wstring> m_Args;
    static bool m_bTimed;
    static bool m_bSerialize;
public :
    static void setCommandLineArgs(int _iArgs, char** _pstArgs);
    static wchar_t** getCommandLineArgs(int* _piCount);
    static bool getTimed();
    static void setTimed(bool _bTimed);
    static bool getSerialize();
    static void setSerialize(bool _bSerialize);

    //schur function
private :
    static types::Callable* m_schurFunction;

public :
    static void setSchurFunction(types::Callable* _schurFunction);
    static types::Callable* getSchurFunction();

    //grand (module randlib)
private :
    static int m_currentBaseGen;
    static int m_currentClcg4;

public :
    static void setCurrentBaseGen(int _currentBaseGen);
    static int getCurrentBaseGen();

    static void setCurrentClcg4(int _currentClcg4);
    static int getCurrentClcg4();

    //Start and end finish flag
private :
    static bool m_bStartProcessing;
    static bool m_bEndProcessing;

public :
    static void setStartProcessing(bool _bStartProcessing);
    static bool getStartProcessing();
    static void setEndProcessing(bool _bEndFinished);
    static bool getEndProcessing();

    // ieee
private :
    static int m_iIeee;

public :
    static void setIeee(int _iIeee)
    {
        m_iIeee = _iIeee;
    }

    static int getIeee()
    {
        return m_iIeee;
    }

    // simp mode
private :
    static int m_iSimpMode;

public :
    static void setSimpMode(int _iSimpMode);
    static int getSimpMode();

    // funcprot mode
private :
    static int m_iFuncprot;

public :
    static void setFuncprot(int _iFuncprot)
    {
        m_iFuncprot = _iFuncprot;
    }

    static int getFuncprot()
    {
        return m_iFuncprot;
    }

    // where
public :
    // On macro call, some information are pushed to the call stack
    struct WhereEntry
    {
        int m_line;
        int m_absolute_line;
        int m_scope_lvl;
        types::Callable* call;
        const std::wstring* m_file_name;
    };

    // On error, every information is copied back as values from the Callable to avoid being freed on call stack return
    struct WhereErrorEntry
    {
        int m_line;
        int m_absolute_line;
        int m_first_line;
        std::wstring m_function_name;
        std::wstring m_file_name;
    };

    static void where_begin(int _iLineNum, int _iLineLocation, types::Callable* _pCall);

    static void where_end()
    {
        m_Where.pop_back();
    }

    static const std::vector<WhereEntry>& getWhere()
    {
        return m_Where;
    }

    static void fillWhereError(int _iErrorLine);
    
    static void resetWhereError()
    {
        m_WhereError.clear();
    }

    static void macroFirstLine_begin(int _iLine)
    {
        m_FirstMacroLine.push_back(_iLine);
    }

    static void macroFirstLine_end()
    {
        m_FirstMacroLine.pop_back();
    }

    static int getMacroFirstLines()
    {
        if (m_FirstMacroLine.empty())
        {
            return 1;
        }

        return m_FirstMacroLine.back();
    }

    static void setFileNameToLastWhere(const std::wstring* _fileName)
    {
        m_Where.back().m_file_name = _fileName;
    }

    static void whereErrorToString(std::wostringstream &ostr);
private :
    static std::vector<WhereEntry> m_Where;
    static std::vector<WhereErrorEntry> m_WhereError;
    static std::vector<int> m_FirstMacroLine;
    //module called with variable by reference
private :
    static std::list<std::wstring> m_ReferenceModules;
public :
    static bool checkReferenceModule(const std::wstring& _module);
    static void addReferenceModule(const std::wstring& _module);
    static void removeReferenceModule(const std::wstring& _module);
    static std::list<std::wstring> getReferenceModules();

    //analyzer options

private :
    static int m_analyzerOptions;
public :
    static void setAnalyzerOptions(int _val);
    static int getAnalyzerOptions(void);

    //divide by zero
private:
    static bool m_dividebyzero;
public:
    static void setDivideByZero(bool _dividebyzero);
    static bool isDivideByZero(void);

    //mex info
private:
    static std::string mexFunctionName;
public:
    static void setMexFunctionName(const std::string& name);
    static std::string& getMexFunctionName();

    // executed file with exec
private:
    static int m_iFileID;
public:
    static void setExecutedFileID(int _iFileID);
    static int getExecutedFileID();

    // string read from console by scilabRead
private:
    static std::atomic<char*> m_pcConsoleReadStr;
public:
    static void setConsoleReadStr(char* _pcConsoleReadStr);
    static char* getConsoleReadStr();

    // tell if the command return by scilabRead is a scilab command or not
private:
    static std::atomic<int> m_isScilabCommand;
public:
    static void setScilabCommand(int _isciCmd);
    static int isScilabCommand();

    //debugger information
    static bool m_bEnabledebug;
    static std::unique_ptr<ast::ConstVisitor> m_defaultvisitor;

    static bool getEnableDebug();
    static void setEnableDebug(bool _enable);

    static void setDefaultVisitor(ast::ConstVisitor* _default);
    static ast::ConstVisitor* getDefaultVisitor();

    //manage CTRL C in console
private :
    static bool executionbreak;
public :
    static bool isExecutionBreak();
    static void setExecutionBreak();
    static void resetExecutionBreak();
private:
    static int recursionLimit;
    static int recursionLevel;

    // manage recursion stack
public :
    static int getRecursionLimit();
    static int setRecursionLimit(int val);

    static int getRecursionLevel();
    static void resetRecursionLevel();
    static bool increaseRecursion();
    static void decreaseRecursion();
};

#endif /* !__CONFIGVARIABLE_HXX__ */
