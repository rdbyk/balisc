/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2012 - Scilab Enterprises - Antoine ELIAS
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

#ifndef __H5_READDATATOFILE_H__
#define __H5_READDATATOFILE_H__

#include <hdf5.h>

#define unknown_type    -3
#define sci_insert      -2
#define sci_undefined   -1
#define sci_delete       0

char* getScilabVersionAttribute(int _iFile);
int getSODFormatAttribute(int _iFile);

int isComplexData(int _iDatasetId);

int getVariableNames(int _iFile, char **pstNameList);

int getDataSetId(int  _iFile);

int getDataSetIdFromName(int _iFile, const char *_pstName);
void closeDataSet(int _id);

int getDatasetInfo(int _iDatasetId, int* _iComplex, int* _iDims, int* _piDims);
int getDatasetDims(int _iDatasetId, int *_piRows, int *_piCols);
int getListDims(int _iDatasetId, int *_piItem);

int getScilabTypeFromDataSet(int _iDatasetId);

int getDatasetPrecision(int _iDatasetId, int* _piPrec);

int getSparseDimension(int _iDatasetId, int* _piRows, int * _piCols, int* _piNbItem);

int readEmptyMatrix(int _iDatasetId);

int readDoubleMatrix(int _iDatasetId, double *_pdblData);
int readDoubleComplexMatrix(int _iDatasetId, double *_pdblReal, double *_pdblImg);

int readStringMatrix(int _iDatasetId, char **_pstData);
int freeStringMatrix(int _iDatasetId, char** _pstData);

int readBooleanMatrix(int _iDatasetId, int* _piData);

int readPolyMatrix(int _iDatasetId, char* _pstVarname, int _iDims, int* _piDims, int* _piNbCoef, double **_pdblData);
int readPolyComplexMatrix(int _iDatasetId, char* _pstVarname, int _iDims, int* _piDims, int* _piNbCoef, double **_pdblReal, double **_pdblImg);

int readInteger8Matrix(int _iDatasetId, char* _pcData);
int readInteger16Matrix(int _iDatasetId, short* _psData);
int readInteger32Matrix(int _iDatasetId, int* _piData);
int readInteger64Matrix(int _iDatasetId, long long* _pllData);

int readUnsignedInteger8Matrix(int _iDatasetId, unsigned char* _pucData);
int readUnsignedInteger16Matrix(int _iDatasetId, unsigned short* _pusData);
int readUnsignedInteger32Matrix(int _iDatasetId, unsigned int* _puiData);
int readUnsignedInteger64Matrix(int _iDatasetId, unsigned long long* _pullData);

int readSparseComplexMatrix(int _iDatasetId, int _iRows, int _iCols, int _iNbItem, int* _piNbItemRow,	int* _piColPos, double *_pdblReal, double *_pdblImg);
int readSparseMatrix(int _iDatasetId, int _iRows, int _iCols, int _iNbItem, int* _piNbItemRow,	int* _piColPos, double *_pdblReal);

int readBooleanSparseMatrix(int _iDatasetId, int _iRows, int _iCols, int _iNbItem, int* _piNbItemRow,	int* _piColPos);

int getListItemReferences(int _iDatasetId, hobj_ref_t** _piItemRef);

int getListItemDataset(int _iDatasetId, void* _piItemRef, int _iItemPos, int* _piItemDataset);

int deleteListItemReferences(int _iDatasetId, void* _piItemRef);

 void reset_item_count();

//Scilab 6
int getVariableNames6(int _iFile, char **names);
char* getScilabTypeFromDataSet6(int dataset);
int getListDims6(int dataset, int* items);

#endif /* !__H5_READDATATOFILE_H__ */
