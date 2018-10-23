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

#ifndef __H5_WRITEDATATOFILE_H__
#define __H5_WRITEDATATOFILE_H__

#include <hdf5.h>

int updateFileVersion(int _iFile);
int updateScilabVersion(int _iFile);

int deleteHDF5Var(int _iFile, const char* _pstName);

int writeDoubleMatrix6(int parent, const char* name, int dims, int* pdims, double* data);
int writeDoubleComplexMatrix6(int parent, const char* name, int dims, int* pdims, double* real, double* img);
int writeStringMatrix6(int parent, const char* name, int dims, int* pdims, char** data);
int writeBooleanMatrix6(int parent, const char* name, int dims, int* pdims, int* data);
int writeIntegerMatrix6(int parent, const char* name, int type, const char* prec, int dims, int* pdims, void* data);

int openList6(int parent, const char *name, const char* type);
int closeList6(int lst);

int addItemStruct6(int dataset, hobj_ref_t * refs, int pos, const char *name);
int writeStructField6(int parent, const char* name, int dims, int* pdims, hobj_ref_t * refs);

int writeDelete(int parent, const char* name);
int writeUndefined6(int parent, const char* name);

#endif /* !__H5_WRITEDATATOFILE_H__ */
