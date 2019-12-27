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

char* getScilabVersionAttribute(hid_t _iFile);
int getSODFormatAttribute(hid_t _iFile);

int isComplexData(hid_t _iDatasetId);

int getVariableNames(hid_t _iFile, char **pstNameList);

hid_t getDataSetId(hid_t _iFile);

hid_t getDataSetIdFromName(hid_t _iFile, const char *_pstName);
void closeDataSet(hid_t _id);

int getDatasetInfo(hid_t _iDatasetId, int* _iComplex, int* _iDims, int* _piDims);
int getDatasetDims(hid_t _iDatasetId, int *_piRows, int *_piCols);
int getListDims(hid_t _iDatasetId, int *_piItem);

int getScilabTypeFromDataSet(hid_t _iDatasetId);

int getDatasetPrecision(hid_t _iDatasetId, int* _piPrec);

int getSparseDimension(hid_t _iDatasetId, int* _piRows, int * _piCols, int* _piNbItem);

int readEmptyMatrix(hid_t _iDatasetId);

int readDoubleMatrix(hid_t _iDatasetId, double *_pdblData);
int readDoubleComplexMatrix(hid_t _iDatasetId, double *_pdblReal, double *_pdblImg);

int readStringMatrix(hid_t _iDatasetId, char **_pstData);
int freeStringMatrix(hid_t _iDatasetId, char** _pstData);

int readBooleanMatrix(hid_t _iDatasetId, int* _piData);

int readPolyMatrix(hid_t _iDatasetId, char* _pstVarname, int _iDims, int* _piDims, int* _piNbCoef, double **_pdblData);
int readPolyComplexMatrix(hid_t _iDatasetId, char* _pstVarname, int _iDims, int* _piDims, int* _piNbCoef, double **_pdblReal, double **_pdblImg);

int readInteger8Matrix(hid_t _iDatasetId, char* _pcData);
int readInteger16Matrix(hid_t _iDatasetId, short* _psData);
int readInteger32Matrix(hid_t _iDatasetId, int* _piData);
int readInteger64Matrix(hid_t _iDatasetId, long long* _pllData);

int readUnsignedInteger8Matrix(hid_t _iDatasetId, unsigned char* _pucData);
int readUnsignedInteger16Matrix(hid_t _iDatasetId, unsigned short* _pusData);
int readUnsignedInteger32Matrix(hid_t _iDatasetId, unsigned int* _puiData);
int readUnsignedInteger64Matrix(hid_t _iDatasetId, unsigned long long* _pullData);

int readSparseComplexMatrix(hid_t _iDatasetId, int _iRows, int _iCols, int _iNbItem, int* _piNbItemRow,	int* _piColPos, double *_pdblReal, double *_pdblImg);
int readSparseMatrix(hid_t _iDatasetId, int _iRows, int _iCols, int _iNbItem, int* _piNbItemRow,	int* _piColPos, double *_pdblReal);

int readBooleanSparseMatrix(hid_t _iDatasetId, int _iRows, int _iCols, int _iNbItem, int* _piNbItemRow,	int* _piColPos);

int getListItemReferences(hid_t _iDatasetId, hobj_ref_t** _piItemRef);

int getListItemDataset(hid_t _iDatasetId, void* _piItemRef, int _iItemPos, hid_t* _piItemDataset);

int deleteListItemReferences(hid_t _iDatasetId, void* _piItemRef);

void reset_item_count();

//Scilab 6
int getVariableNames6(hid_t _iFile, char **names);
char* getScilabTypeFromDataSet6(hid_t dataset);
int getListDims6(hid_t dataset, int* items);

#endif /* !__H5_READDATATOFILE_H__ */
