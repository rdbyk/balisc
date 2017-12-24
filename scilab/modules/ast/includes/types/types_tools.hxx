/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2011 - DIGITEO - Antoine ELIAS
 * Copyright (C) 2012 - 2016 - Scilab Enterprises
 * Copyrigth (C) 2017 - Dirk Reusch, Kybernetik Dr. Reusch
 *
 * This file is hereby licensed under the terms of the GNU GPL v2.0,
 * pursuant to article 5.3.4 of the CeCILL v.2.1.
 * This file was originally licensed under the terms of the CeCILL v2.1,
 * and continues to be available under such terms.
 * For more information, see the COPYING file which you should have received
 * along with this program.
 *
 */

#ifndef __TYPES_TOOLS_HXX__
#define __TYPES_TOOLS_HXX__

#include "types.hxx"
#include "function.hxx"
#include "double.hxx"

namespace types
{
bool getScalarIndex(GenericType* _pRef, typed_list* _pArgsIn, int* index);
bool getArgsDims(typed_list* _pArgsIn, std::vector<int>& dims); //only for insertNew
bool getImplicitIndex(GenericType* _pRef, typed_list* _pArgsIn, std::vector<int>& index, std::vector<int>& dims);
bool getScalarImplicitIndex(GenericType* _pRef, typed_list* _pArgsIn, std::vector<double>& index);

int checkIndexesArguments(InternalType* _pRef, typed_list* _pArgsIn, typed_list* _pArgsOut, int* _piMaxDim, int* _piCountDim);
void cleanIndexesArguments(typed_list* _pArgsOrig, typed_list* _pArgsNew);
void getIndexesWithDims(int _iIndex, int* _piIndexes, const int* _piDims, int _iDims);
int getIndexWithDims(int* _piIndexes, const int* _piDims, int _iDims);
types::Function::ReturnValue VariableToString(types::InternalType* pIT, const wchar_t* wcsVarName);

//commom function
int computeTuples(int* _piCountDim, int _iCurrentDim, int* _piIndex);
Double* createDoubleVector(int _iSize);
bool checkArgValidity(typed_list& _pArg);
}

#endif /* !__TYPES_TOOLS_HXX__ */
