/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2009-2010 - DIGITEO - Bruno JOFRET
 * Copyright (C) 2009-2009 - DIGITEO - Antoine ELIAS
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

#ifndef __MACROFILE_HXX__
#define __MACROFILE_HXX__

#include <string>
#include "callable.hxx"
#include "macro.hxx"

namespace types
{
class MacroFile : public Callable
{
public :
    MacroFile(): Callable() {};
    MacroFile(const std::wstring& _stName, const std::wstring& _stPath, const std::wstring& _stModule);
    virtual                 ~MacroFile();

    //FIXME : Should not return NULL
    MacroFile*              clone() override;

    inline ScilabType       getType(void) override
    {
        return ScilabMacroFile;
    }
    inline ScilabId         getId(void) override
    {
        return IdMacroFile;
    }

    bool                    isMacroFile() override
    {
        return true;
    }

    bool                    toString(std::wostringstream& ostr) override;

    Callable::ReturnValue   call(typed_list &in, optional_list &opt, int _iRetCount, typed_list &out) override;
    bool                    parse(void);

    Macro*                  getMacro(void);

    void                    setLines(int _iFirstLine, int _iLastLine) override;

    bool                    getMemory(int* _piSize, int* _piSizePlusType) override;

    /* return type as string ( double, int, cell, list, ... )*/
    virtual std::wstring    getTypeStr() const override
    {
        return L"function";
    }
    /* return type as short string ( s, i, ce, l, ... )*/
    virtual std::wstring    getShortTypeStr() const override
    {
        return L"function";
    }

    inline const std::wstring & getPath()
    {
        return m_stPath;
    }

    virtual int getNbInputArgument(void) override;
    virtual int getNbOutputArgument(void) override;

    bool operator==(const InternalType& it) override;

private :
    std::wstring            m_stPath;
    Macro*                  m_pMacro;
};
}

#endif /* !__MACROFILE_HXX__ */
