/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2012 - Scilab Enterprises - Antoine ELIAS
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

#ifndef __H5_WRITEDATATOFILE_H__
#define __H5_WRITEDATATOFILE_H__

#include <hdf5.h>

int updateFileVersion(int _iFile);
int updateScilabVersion(int _iFile);

char* createGroupName(const char* _pstGroupName);
char* createPathName(char* _pstGroupName, int _iIndex);
int deleteHDF5Var(int _iFile, const char* _pstName);

int writeDoubleMatrix(int _iFile, char* _pstDatasetName, int _iDims, int* _piDims, double *_pdblData);
int writeDoubleComplexMatrix(int _iFile, char* _pstDatasetName, int _iDims, int* _piDims, double *_pdblReal, double *_pdblImg);

int writeStringMatrix(int _iFile, char* _pstDatasetName, int _iDims, int* _piDims, char **_pstData);

int writeBooleanMatrix(int _iFile, char* _pstDatasetName, int _iDims, int* _piDims, int *_piData);

int writePolyMatrix(int _iFile, char* _pstDatasetName, char* _pstVarName, int _iDims, int* _piDims, int* _piNbCoef, double** _pdblData);
int writePolyComplexMatrix(int _iFile, char* _pstDatasetName, char* _pstVarName, int _iDims, int* _piDims, int* _piNbCoef, double** _pdblReal, double** _pdblImg);

int writeInteger8Matrix(int _iFile, char* _pstDatasetName, int _iDims, int* _piDims, char* _piData8);
int writeInteger16Matrix(int _iFile, char* _pstDatasetName, int _iDims, int* _piDims, short* _piData16);
int writeInteger32Matrix(int _iFile, char* _pstDatasetName, int _iDims, int* _piDims, int* _piData32);
int writeInteger64Matrix(int _iFile, char* _pstDatasetName, int _iDims, int* _piDims, long long* _piData64);

int writeUnsignedInteger8Matrix(int _iFile, char* _pstDatasetName, int _iDims, int* _piDims, unsigned char* _piData8);
int writeUnsignedInteger16Matrix(int _iFile, char* _pstDatasetName, int _iDims, int* _piDims, unsigned short* _piData16);
int writeUnsignedInteger32Matrix(int _iFile, char* _pstDatasetName, int _iDims, int* _piDims, unsigned int* _piData32);
int writeUnsignedInteger64Matrix(int _iFile, char* _pstDatasetName, int _iDims, int* _piDims, unsigned long long* _piData64);

int writeSparseMatrix(int _iFile, char* _pstDatasetName, int _iRows, int _iCols, int _iNbItem, int* _piNbItemRow, int* _piColPos, double* _pdblReal);
int writeSparseComplexMatrix(int _iFile, char* _pstDatasetName, int _iRows, int _iCols, int _iNbItem, int* _piNbItemRow, int* _piColPos, double* _pdblReal, double* _pdblImg);

int writeBooleanSparseMatrix(int _iFile, char* _pstDatasetName, int _iRows, int _iCols, int _iNbItem, int* _piNbItemRow, int* _piColPos);

int writeVoid(int _iFile, char* _pstDatasetName);
int writeUndefined(int _iFile, char* _pstDatasetName);

void* openList(int _iFile, char* pstDatasetName, int _iNbItem);
int addItemInList(int _iFile, void* _pvList, int _iPos, char* _pstItemName);
int closeList(int _iFile,  void* _pvList, char* _pstListName, int _iNbItem, int _iVarType);


/*scilab 6*/

int writeDoubleMatrix6(int parent, const char* name, int dims, int* pdims, double* data);
int writeDoubleComplexMatrix6(int parent, const char* name, int dims, int* pdims, double* real, double* img);
int writeStringMatrix6(int parent, const char* name, int dims, int* pdims, char** data);
int writeBooleanMatrix6(int parent, const char* name, int dims, int* pdims, int* data);
int writeIntegerMatrix6(int parent, const char* name, int type, const char* prec, int dims, int* pdims, void* data);

int openList6(int parent, const char *name, const char* type);
int closeList6(int lst);
int addItemStruct6(int dataset, hobj_ref_t * refs, int pos, const char *name);
int writeStructField6(int parent, const char* name, int dims, int* pdims, hobj_ref_t * refs);
int writeVoid6(int parent, const char* name);
int writeUndefined6(int parent, const char* name);

#endif /* !__H5_WRITEDATATOFILE_H__ */
