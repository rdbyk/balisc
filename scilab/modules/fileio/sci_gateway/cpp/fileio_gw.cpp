/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2010-2010 - DIGITEO - Bruno JOFRET
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

#include "fileio_gw.hxx"
#include "context.hxx"
#include "function.hxx"

extern "C"
{
#include "gw_fileio.h"
}

wchar_t FileioModule::Name[] = L"fileio";

int FileioModule::Load()
{
    symbol::Context::getInstance()->addFunction(types::Function::createFunction(L"cd", &sci_chdir, FileioModule::Name));
    symbol::Context::getInstance()->addFunction(types::Function::createFunction(L"chdir", &sci_chdir, FileioModule::Name));
    symbol::Context::getInstance()->addFunction(types::Function::createFunction(L"pwd", &sci_pwd, FileioModule::Name));
    symbol::Context::getInstance()->addFunction(types::Function::createFunction(L"mopen", &sci_mopen, FileioModule::Name));
    symbol::Context::getInstance()->addFunction(types::Function::createFunction(L"mclose", &sci_mclose, FileioModule::Name));
    symbol::Context::getInstance()->addFunction(types::Function::createFunction(L"mput", &sci_mput, FileioModule::Name));
    symbol::Context::getInstance()->addFunction(types::Function::createFunction(L"mget", &sci_mget, FileioModule::Name));
    symbol::Context::getInstance()->addFunction(types::Function::createFunction(L"mputl", &sci_mputl, FileioModule::Name));
    symbol::Context::getInstance()->addFunction(types::Function::createFunction(L"mgetl", &sci_mgetl, FileioModule::Name));
    symbol::Context::getInstance()->addFunction(types::Function::createFunction(L"pathconvert", &sci_pathconvert, FileioModule::Name));
    symbol::Context::getInstance()->addFunction(types::Function::createFunction(L"isdir", &sci_isdir, FileioModule::Name));
    symbol::Context::getInstance()->addFunction(types::Function::createFunction(L"filesep", &sci_filesep, FileioModule::Name));
    symbol::Context::getInstance()->addFunction(types::Function::createFunction(L"fileparts", &sci_fileparts, FileioModule::Name));
    symbol::Context::getInstance()->addFunction(types::Function::createFunction(L"findfiles", &sci_findfiles, FileioModule::Name));
    symbol::Context::getInstance()->addFunction(types::Function::createFunction(L"basename", &sci_basename, FileioModule::Name));
    symbol::Context::getInstance()->addFunction(types::Function::createFunction(L"isfile", &sci_isfile, FileioModule::Name));
    symbol::Context::getInstance()->addFunction(types::Function::createFunction(L"fileinfo", &sci_fileinfo, FileioModule::Name));
    symbol::Context::getInstance()->addFunction(types::Function::createFunction(L"deletefile", &sci_deletefile, FileioModule::Name));
    symbol::Context::getInstance()->addFunction(types::Function::createFunction(L"getshortpathname", &sci_getshortpathname, FileioModule::Name));
    symbol::Context::getInstance()->addFunction(types::Function::createFunction(L"getlongpathname", &sci_getlongpathname, FileioModule::Name));
    symbol::Context::getInstance()->addFunction(types::Function::createFunction(L"fileext", &sci_fileext, FileioModule::Name));
    symbol::Context::getInstance()->addFunction(types::Function::createFunction(L"createdir", &sci_createdir, FileioModule::Name));
    symbol::Context::getInstance()->addFunction(types::Function::createFunction(L"fullpath", &sci_fullpath, FileioModule::Name));
    symbol::Context::getInstance()->addFunction(types::Function::createFunction(L"copyfile", &sci_copyfile, FileioModule::Name));
    symbol::Context::getInstance()->addFunction(types::Function::createFunction(L"removedir", &sci_removedir, FileioModule::Name));
    symbol::Context::getInstance()->addFunction(types::Function::createFunction(L"meof", &sci_meof, FileioModule::Name));
    symbol::Context::getInstance()->addFunction(types::Function::createFunction(L"mputstr", &sci_mputstr, FileioModule::Name));
    symbol::Context::getInstance()->addFunction(types::Function::createFunction(L"mgetstr", &sci_mgetstr, FileioModule::Name));
    symbol::Context::getInstance()->addFunction(types::Function::createFunction(L"mseek", &sci_mseek, FileioModule::Name));
    symbol::Context::getInstance()->addFunction(types::Function::createFunction(L"mtell", &sci_mtell, FileioModule::Name));
    symbol::Context::getInstance()->addFunction(types::Function::createFunction(L"newest", &sci_newest, FileioModule::Name));
    symbol::Context::getInstance()->addFunction(types::Function::createFunction(L"merror", &sci_merror, FileioModule::Name));
    symbol::Context::getInstance()->addFunction(types::Function::createFunction(L"mclearerr", &sci_mclearerr, FileioModule::Name));
    symbol::Context::getInstance()->addFunction(types::Function::createFunction(L"get_absolute_file_path", &sci_get_absolute_file_path, FileioModule::Name));
    symbol::Context::getInstance()->addFunction(types::Function::createFunction(L"getrelativefilename", &sci_getrelativefilename, FileioModule::Name));
    symbol::Context::getInstance()->addFunction(types::Function::createFunction(L"pathsep", &sci_pathsep, FileioModule::Name));
    symbol::Context::getInstance()->addFunction(types::Function::createFunction(L"mfprintf", &sci_mfprintf, FileioModule::Name));
    symbol::Context::getInstance()->addFunction(types::Function::createFunction(L"mscanf", &sci_mscanf, FileioModule::Name));
    symbol::Context::getInstance()->addFunction(types::Function::createFunction(L"mfscanf", &sci_mfscanf, FileioModule::Name));
    symbol::Context::getInstance()->addFunction(types::Function::createFunction(L"msscanf", &sci_msscanf, FileioModule::Name));
    symbol::Context::getInstance()->addFunction(types::Function::createFunction(L"getdrives", &sci_getdrives, FileioModule::Name));
    symbol::Context::getInstance()->addFunction(types::Function::createFunction(L"fprintfMat", &sci_fprintfMat, FileioModule::Name));
    symbol::Context::getInstance()->addFunction(types::Function::createFunction(L"fscanfMat", &sci_fscanfMat, FileioModule::Name));
    symbol::Context::getInstance()->addFunction(types::Function::createFunction(L"movefile", &sci_movefile, FileioModule::Name));
    symbol::Context::getInstance()->addFunction(types::Function::createFunction(L"tempname", &sci_tempname, FileioModule::Name));
    symbol::Context::getInstance()->addFunction(types::Function::createFunction(L"fflush", &sci_fflush, FileioModule::Name));
    symbol::Context::getInstance()->addFunction(types::Function::createFunction(L"popen", &sci_popen, FileioModule::Name));
    return 1;
}
