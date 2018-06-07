/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2010-2010 - DIGITEO - Antoine ELIAS
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

#ifndef AST_VISITOR_COMMON_HXX
#define AST_VISITOR_COMMON_HXX

#include "internal.hxx"
#include "struct.hxx"
#include "list.hxx"
#include "exp.hxx"
#include "symbol.hxx"
#include <list>
#include "expHistory.hxx"

types::InternalType* AddElementToVariable(
    types::InternalType* _poDest,
    types::InternalType* _poSource,
    int _iRows, int _iCols);

const std::wstring* getStructNameFromExp(const ast::Exp* _pExp);

bool getFieldsFromExp(ast::Exp* _pExp, std::list<ExpHistory*>& fields);

types::InternalType* evaluateFields(const ast::Exp* _pExp, std::list<ExpHistory*>& fields, types::InternalType* pIT);

types::InternalType* callOverload(const ast::Exp& e,
                                  const std::wstring& _strType,
                                  types::typed_list* _pArgs,
                                  types::InternalType* _source,
                                  types::InternalType* _dest);

types::InternalType* callOverload(const std::wstring& strType, types::InternalType* _paramL, types::InternalType* _paramR);

types::InternalType* insertionCall(const ast::Exp& e, types::typed_list* _pArgs, types::InternalType* _pVar, types::InternalType* _pInsert);

void callOnPrompt(void);
ast::Exp* callTyper(ast::Exp* _tree, std::wstring _msg = std::wstring(L""));

void printLine(const std::string& _stPrompt, const std::string& _stLine, bool _bLF);
std::string printExp(std::ifstream& _File, ast::Exp* _pExp, const std::string& _stPrompt, int* _piLine /* in/out */, int* _piCol /* in/out */, std::string& _stPreviousBuffer);

#endif //!AST_VISITOR_COMMON_HXX
