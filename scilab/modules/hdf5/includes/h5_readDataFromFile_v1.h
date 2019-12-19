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

#ifndef __H5_READDATATOFILE_V1_H__
#define __H5_READDATATOFILE_V1_H__

#include <hdf5.h>

#define unknown_type    -2
#define sci_undefined   -1
#define sci_delete       0

int isComplexData_v1(hid_t _iDatasetId);

int getVariableNames_v1(hid_t _iFile, char **pstNameList);

hid_t getDataSetId_v1(hid_t _iFile);

hid_t getDataSetIdFromName_v1(hid_t _iFile, char *_pstName);
void closeDataSet_v1(hid_t _id);

int getDatasetDims_v1(hid_t _iDatasetId, int *_piRows, int *_piCols);
int getListDims_v1(hid_t _iDatasetId, int *_piItem);

int getScilabTypeFromDataSet_v1(hid_t _iDatasetId);

int getDatasetPrecision_v1(hid_t _iDatasetId, int* _piPrec);

int getSparseDimension_v1(hid_t _iDatasetId, int* _piRows, int * _piCols, int* _piNbItem);

int readEmptyMatrix_v1(hid_t _iDatasetId);

int readDoubleMatrix_v1(hid_t _iDatasetId, int _iRows, int _iCols, double *_pdblData);
int readDoubleComplexMatrix_v1(hid_t _iDatasetId, int _iRows, int _iCols, double *_pdblReal, double *_pdblImg);

int readStringMatrix_v1(hid_t _iDatasetId, int _iRows, int _iCols, char **_pstData);

int readBooleanMatrix_v1(hid_t _iDatasetId, int _iRows, int _iCols, int* _piData);

int readPolyMatrix_v1(hid_t _iDatasetId, char* _pstVarname, int _iRows, int _iCols, int* _piNbCoef, double **_pdblData);
int readPolyComplexMatrix_v1(hid_t _iDatasetId, char* _pstVarname, int _iRows, int _iCols, int* _piNbCoef, double **_pdblReal, double **_pdblImg);

int readInteger8Matrix_v1(hid_t _iDatasetId, int _iRows, int _iCols, char* _pcData);
int readInteger16Matrix_v1(hid_t _iDatasetId, int _iRows, int _iCols, short* _psData);
int readInteger32Matrix_v1(hid_t _iDatasetId, int _iRows, int _iCols, int* _piData);
int readInteger64Matrix_v1(hid_t _iDatasetId, int _iRows, int _iCols, long long* _pllData);

int readUnsignedInteger8Matrix_v1(hid_t _iDatasetId, int _iRows, int _iCols, unsigned char* _pucData);
int readUnsignedInteger16Matrix_v1(hid_t _iDatasetId, int _iRows, int _iCols, unsigned short* _pusData);
int readUnsignedInteger32Matrix_v1(hid_t _iDatasetId, int _iRows, int _iCols, unsigned int* _puiData);
int readUnsignedInteger64Matrix_v1(hid_t _iDatasetId, int _iRows, int _iCols, unsigned long long* _pullData);

int readSparseComplexMatrix_v1(hid_t _iDatasetId, int _iRows, int _iCols, int _iNbItem, int* _piNbItemRow,	int* _piColPos, double *_pdblReal, double *_pdblImg);
int readSparseMatrix_v1(hid_t _iDatasetId, int _iRows, int _iCols, int _iNbItem, int* _piNbItemRow,	int* _piColPos, double *_pdblReal);

int readBooleanSparseMatrix_v1(hid_t _iDatasetId, int _iRows, int _iCols, int _iNbItem, int* _piNbItemRow,	int* _piColPos);

int getListItemReferences_v1(hid_t _iDatasetId, hobj_ref_t** _piItemRef);

int getListItemDataset_v1(hid_t _iDatasetId, void* _piItemRef, int _iItemPos, hid_t* _piItemDataset);

int deleteListItemReferences_v1(hid_t _iDatasetId, void* _piItemRef);

void reset_item_count();

#endif /* !__H5_READDATATOFILE_V1_H__ */
