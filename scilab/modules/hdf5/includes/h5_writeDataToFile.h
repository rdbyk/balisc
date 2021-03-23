/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2012 - Scilab Enterprises - Antoine ELIAS
 * Copyright (C) 2012 - 2016 - Scilab Enterprises
 * Copyright (C) 2017 - 2021 Dirk Reusch, Kybernetik Dr. Reusch
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

int updateFileVersion(hid_t _iFile);
int updateScilabVersion(hid_t _iFile);

int deleteHDF5Var(hid_t _iFile, const char* _pstName);

int writeDoubleMatrix6(hid_t parent, const char* name, int dims, int* pdims, double* data, hid_t xfer_plist);
int writeDoubleComplexMatrix6(hid_t parent, const char* name, int dims, int* pdims, double* real, double* img, hid_t xfer_plist);
int writeStringMatrix6(hid_t parent, const char* name, int dims, int* pdims, char** data, hid_t xfer_plist);
int writeBooleanMatrix6(hid_t parent, const char* name, int dims, int* pdims, int* data, hid_t xfer_plist);
int writeIntegerMatrix6(hid_t parent, const char* name, hid_t type, const char* prec, int dims, int* pdims, void* data, hid_t xfer_plist);

hid_t openList6(hid_t parent, const char* name, const char* type);
int closeList6(hid_t lst);

int addItemStruct6(hid_t dataset, hobj_ref_t* refs, int pos, const char* name);
int writeStructField6(hid_t parent, const char* name, int dims, int* pdims, hobj_ref_t* refs, hid_t xfer_plist);

int writeDelete(hid_t parent, const char* name, hid_t xfer_plist);
int writeUndefined6(hid_t parent, const char* name, hid_t xfer_plist);

#endif /* !__H5_WRITEDATATOFILE_H__ */
