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

#define H5_USE_16_API

#include <hdf5.h>
#include <sci_malloc.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "sci_types.h"
#include "version.h"
#include "core_math.h"
#include "h5_writeDataToFile.h"
#include "h5_readDataFromFile.h"
#include "h5_attributeConstants.h"
#include "doublecomplex.h"

static hid_t enableCompression(int _iLevel, int _iRank, const hsize_t * _piDims)
{
    return H5P_DEFAULT;
}

static hsize_t* convertDims(int* _piRank, int* _piDims, int* _piSize)
{
    int iSize = 1;
    int i = 0;
    hsize_t* piDims = (hsize_t*)malloc(sizeof(hsize_t) **_piRank);
    for (i = 0 ; i < *_piRank ; i++)
    {
        //reverse dimensions to improve rendering in external tools
        piDims[i] = _piDims[*_piRank - 1 - i];
        iSize *= (int)piDims[i];
    }
    /*
     * Fix bug under Linux due to this HDF5 error:
     * HDF5-DIAG: Error detected in HDF5 (1.8.4-patch1) thread 140525686855488:
     *   #000: ../../../src/H5S.c line 1335 in H5Screate_simple(): zero sized dimension for non-unlimited dimension
     *     major: Invalid arguments to routine
     *     minor: Bad value
     */
    if (iSize == 0)
    {
        *_piRank = 0;
    }

    *_piSize = iSize;
    return piDims;
}

static herr_t addIntAttribute(int _iDatasetId, const char *_pstName, const int _iVal)
{
    hsize_t attributeDims[1] = { 1 };
    hid_t attributeTypeId, attributeSpace;
    herr_t status;

    //Create attribute dataspace.  Setting maximum size to NULL sets the maximum size to be the current size.
    attributeSpace = H5Screate_simple(1, attributeDims, NULL);

    //Create the attribute and write it.
    attributeTypeId = H5Acreate(_iDatasetId, _pstName, H5T_NATIVE_INT, attributeSpace, H5P_DEFAULT, H5P_DEFAULT);
    if (attributeTypeId < 0)
    {
        return -1;
    }

    status = H5Awrite(attributeTypeId, H5T_NATIVE_INT, &_iVal);
    if (status < 0)
    {
        return -1;
    }

    //Close and release resources.
    status = H5Aclose(attributeTypeId);
    if (status < 0)
    {
        return -1;
    }

    status = H5Sclose(attributeSpace);
    if (status < 0)
    {
        return -1;
    }

    return 0;
}

static herr_t addAttribute(int _iDatasetId, const char *_pstName, const char *_pstValue)
{
    hsize_t attributeDims[1] = { 1 };
    hid_t attributeTypeId, attributeSpace, attr;
    herr_t status;

    //Create attribute dataspace.  Setting maximum size to NULL sets the maximum size to be the current size.
    attributeSpace = H5Screate_simple(1, attributeDims, NULL);

    //Create special attribute type
    attributeTypeId = H5Tcopy(H5T_C_S1);
    status = H5Tset_size(attributeTypeId, strlen(_pstValue));
    if (status < 0)
    {
        return -1;
    }

    //Create the attribute and write it.
    attr = H5Acreate(_iDatasetId, _pstName, attributeTypeId, attributeSpace, H5P_DEFAULT, H5P_DEFAULT);
    if (attr < 0)
    {
        return -1;
    }

    status = H5Awrite(attr, attributeTypeId, _pstValue);
    if (status < 0)
    {
        return -1;
    }

    //Close and release resources.
    status = H5Aclose(attr);
    if (status < 0)
    {
        return -1;
    }

    status = H5Tclose(attributeTypeId);
    if (status < 0)
    {
        return -1;
    }

    return 0;
}

int updateScilabVersion(int _iFile)
{
    herr_t status;
    //try to read attribute
    char* pstScilabVersion = getScilabVersionAttribute(_iFile);
    if (pstScilabVersion)
    {
        FREE(pstScilabVersion);

        //delete before write
        status = H5Adelete(_iFile, g_SCILAB_CLASS_SCI_VERSION);
        if (status < 0)
        {
            return -1;
        }
    }

    if (strstr(SCI_VERSION_STRING, "branch"))
    {
        //compiled by user
        char pstVersion[64];
        sprintf(pstVersion, "%s %d.%d.%d", SCI_VERSION_STRING, SCI_VERSION_MAJOR, SCI_VERSION_MINOR, SCI_VERSION_MAINTENANCE);
        status = addAttribute(_iFile, g_SCILAB_CLASS_SCI_VERSION, pstVersion);
    }
    else
    {
        //compiled by compilation chain
        status = addAttribute(_iFile, g_SCILAB_CLASS_SCI_VERSION, SCI_VERSION_STRING);
    }

    return status;
}

int updateFileVersion(int _iFile)
{
    herr_t status;
    //try to read attribute
    int iHdf5Version = getSODFormatAttribute(_iFile);
    if (iHdf5Version != -1)
    {
        status = H5Adelete(_iFile, g_SCILAB_CLASS_SOD_VERSION);
        if (status < 0)
        {
            return -1;
        }
    }

    return addIntAttribute(_iFile, g_SCILAB_CLASS_SOD_VERSION, SOD_FILE_VERSION);
}

static int deleteHDF5group(int _iFile, const char* _pstName)
{
    H5G_info_t groupInfo;
    hid_t status = 0;
    //open group
    hid_t groupID = H5Gopen(_iFile, _pstName, H5P_DEFAULT);
    //hid_t groupID = H5Gopen(_iFile, _pstName, H5P_DEFAULT);

    if (groupID < 0)
    {
        return -1;
    }

    //get children count
    status = H5Gget_info(groupID, &groupInfo);
    if (status != -1)
    {
        int index = 0;
        int i = 0;

        //for each child,
        for (i = 0; i < groupInfo.nlinks; i++)
        {
            int ret = 0;
            //get child name
            ssize_t size = H5Lget_name_by_idx(groupID, ".", H5_INDEX_NAME, H5_ITER_INC, index, 0, 0, H5P_DEFAULT) + 1;
            char* pstChildName = (char*)MALLOC(sizeof(char) * size);
            H5Lget_name_by_idx(groupID, ".", H5_INDEX_NAME, H5_ITER_INC, index, pstChildName, size, H5P_DEFAULT);
            ret = deleteHDF5group(groupID, pstChildName);
            if (ret == -1)
            {
                ++index;
            }
            ////unlink child
            //status = H5Ldelete(groupID, pstChildName, H5P_DEFAULT);
            FREE(pstChildName);

            //if (status < 0)
            //{
            //    return -1;
            //}
        }
    }

    //close group
    status = closeList6(groupID);
    if (status < 0)
    {
        return -1;
    }

    //delete group
    status = H5Ldelete(_iFile, _pstName, H5P_DEFAULT);
    if (status < 0)
    {
        return -1;
    }

    return 0;
}

//According to 5.5.2. Deleting a Dataset from a File and Reclaiming Space of http://www.hdfgroup.org/HDF5/doc/UG/10_Datasets.html
//it is actually impossible to really remove data from HDF5 file so unlink dataset to main group
int deleteHDF5Var(int _iFile, const char* _pstName)
{
    int ret = 0;
    void *oldclientdata = NULL;
    H5E_auto2_t oldfunc;

    /* Save old error handler */
    H5Eget_auto2(H5E_DEFAULT, &oldfunc, &oldclientdata);

    /* Turn off error handling */
    H5Eset_auto2(H5E_DEFAULT, NULL, NULL);

    //try to unlink potential subgroups
    ret = deleteHDF5group(_iFile, _pstName);
    if (ret == -1)
    {
        //delete current dataset link
        hid_t status = H5Ldelete(_iFile, _pstName, H5P_DEFAULT);
        if (status < 0)
        {
            H5Eset_auto2(H5E_DEFAULT, oldfunc, oldclientdata);
            return -1;
        }
        ret = 0;
    }

    H5Eset_auto2(H5E_DEFAULT, oldfunc, oldclientdata);
    return ret;
}

/*Scilab 6*/
int writeDoubleMatrix6(int parent, const char* name, int dims, int* pdims, double* data)
{
    hid_t space = 0;
    hid_t dset = 0;
    herr_t status = 0;
    hsize_t *piDims = NULL;
    hid_t iCompress = 0;
    int i = 0;
    int iSize = 0;
    hid_t dprop = 0;

    piDims = convertDims(&dims, pdims, &iSize);

    if (dims == 0 || (dims == 2 && pdims[0] == 0 && pdims[1] == 0))
    {
        // []
        space = H5Screate_simple(0, NULL, NULL);
        if (space < 0)
        {
            free(piDims);
            return -1;
        }

        //Create the dataset and write the array data to it.
        iCompress = enableCompression(9, dims, piDims);
        free(piDims);

        dprop = H5Pcreate(H5P_DATASET_CREATE);
        H5Pset_obj_track_times(dprop, 0);
        dset = H5Dcreate(parent, name, H5T_NATIVE_DOUBLE, space, iCompress, dprop, H5P_DEFAULT);
        if (dset < 0)
        {
            return -1;
        }
    }
    else
    {
        //Create dataspace.  Setting maximum size to NULL sets the maximum size to be the current size.
        space = H5Screate_simple(dims, piDims, NULL);
        if (space < 0)
        {
            free(piDims);
            return -1;
        }

        //Create the dataset and write the array data to it.
        iCompress = enableCompression(9, dims, piDims);
        free(piDims);

        dprop = H5Pcreate(H5P_DATASET_CREATE);
        H5Pset_obj_track_times(dprop, 0);
        dset = H5Dcreate(parent, name, H5T_NATIVE_DOUBLE, space, iCompress, dprop, H5P_DEFAULT);
        if (dset < 0)
        {
            return -1;
        }

        status = H5Dwrite(dset, H5T_NATIVE_DOUBLE, H5S_ALL, H5S_ALL, H5P_DEFAULT, data);
        if (status < 0)
        {
            return -1;
        }
    }

    //Add attribute SCILAB_Class = double to dataset
    status = addAttribute(dset, g_SCILAB_CLASS, g_SCILAB_CLASS_DOUBLE);
    if (status < 0)
    {
        return -1;
    }

    //Close and release resources.
    status = H5Dclose(dset);
    if (status < 0)
    {
        return -1;
    }

    status = H5Pclose(dprop);
    if (status < 0)
    {
        return -1;
    }

    status = H5Sclose(space);
    if (status < 0)
    {
        return -1;
    }

    return dset;
}

hid_t writeDoubleComplexMatrix6(int parent, const char* name, int dims, int* pdims, double* real, double* img)
{
    hid_t space = 0;
    hid_t dset = 0;
    herr_t status = 0;
    hsize_t *piDims = NULL;
    hid_t iCompress = 0;
    hid_t compoundId = 0;
    hid_t dprop = 0;
    int iSize = 1;
    doublecomplex* pData = NULL;

    //create sub group only for non empty matrix
    if (dims == 2 && pdims[0] == 0 && pdims[1] == 0)
    {
        // [] complex
        //a revoir
        return -1;
    }

    compoundId = H5Tcreate(H5T_COMPOUND, sizeof(doublecomplex));
    H5Tinsert(compoundId, "real", HOFFSET(doublecomplex, r), H5T_NATIVE_DOUBLE);
    H5Tinsert(compoundId, "imag", HOFFSET(doublecomplex, i), H5T_NATIVE_DOUBLE);
    piDims = convertDims(&dims, pdims, &iSize);

    //Create dataspace.  Setting maximum size to NULL sets the maximum size to be the current size.
    space = H5Screate_simple(dims, piDims, NULL);
    if (space < 0)
    {
        free(piDims);
        return -1;
    }

    //Create the dataset and write the array data to it.
    iCompress = enableCompression(9, dims, piDims);
    free(piDims);

    dprop = H5Pcreate(H5P_DATASET_CREATE);
    H5Pset_obj_track_times(dprop, 0);
    dset = H5Dcreate(parent, name, compoundId, space, iCompress, dprop, H5P_DEFAULT);
    if (dset < 0)
    {
        return -1;
    }

    //convert double data doublecomplex data
    pData = oGetDoubleComplexFromPointer(real, img, iSize);
    status = H5Dwrite(dset, compoundId, H5S_ALL, H5S_ALL, H5P_DEFAULT, pData);
    FREE(pData);
    if (status < 0)
    {
        return -1;
    }

    //Add attribute SCILAB_Class = double to dataset
    status = addAttribute(dset, g_SCILAB_CLASS, g_SCILAB_CLASS_DOUBLE);
    if (status < 0)
    {
        return -1;
    }

    //Close and release resources.
    status = H5Dclose(dset);
    if (status < 0)
    {
        return -1;
    }

    status = H5Pclose(dprop);
    if (status < 0)
    {
        return -1;
    }

    status = H5Sclose(space);
    if (status < 0)
    {
        return -1;
    }

    return dset;
}

int writeStringMatrix6(int parent, const char* name, int dims, int* pdims, char** data)
{
    int iSize = 0;
    hsize_t* piDims = NULL;
    hid_t typeId = 0, space = 0, dset = 0, dprop = 0;
    herr_t status;
    hid_t iCompress;

    piDims = convertDims(&dims, pdims, &iSize);

    //Create special string type
    typeId = H5Tcopy(H5T_C_S1);
    status = H5Tset_size(typeId, H5T_VARIABLE);
    if (status < 0)
    {
        FREE(piDims);
        return -1;
    }

    if (dims == 0 || (dims == 2 && pdims[0] == 0 && pdims[1] == 0))
    {
        // []
        space = H5Screate_simple(0, NULL, NULL);
        if (space < 0)
        {
            free(piDims);
            return -1;
        }

        //Create the dataset and write the array data to it.
        iCompress = enableCompression(9, dims, piDims);
        free(piDims);

        dprop = H5Pcreate(H5P_DATASET_CREATE);
        H5Pset_obj_track_times(dprop, 0);
        dset = H5Dcreate(parent, name, typeId, space, iCompress, dprop, H5P_DEFAULT);
        if (dset < 0)
        {
            return -1;
        }
    }
    else
    {
        //Create string dataspace.  Setting maximum size to NULL sets the maximum size to be the current size.
        space = H5Screate_simple(dims, piDims, NULL);
        if (space < 0)
        {
            FREE(piDims);
            return -1;
        }

        //Create the data set and write it.
        iCompress = enableCompression(9, dims, piDims);
        FREE(piDims);

        dprop = H5Pcreate(H5P_DATASET_CREATE);
        H5Pset_obj_track_times(dprop, 0);
        dset = H5Dcreate(parent, name, typeId, space, iCompress, dprop, H5P_DEFAULT);
        if (dset < 0)
        {
            return -1;
        }

        status = H5Dwrite(dset, typeId, H5S_ALL, H5S_ALL, H5P_DEFAULT, data);
        if (status < 0)
        {
            return -1;
        }
    }

    //Add attribute SCILAB_Class = string to dataset
    status = addAttribute(dset, g_SCILAB_CLASS, g_SCILAB_CLASS_STRING);
    if (status < 0)
    {
        return -1;
    }

    //Close and release resources.
    status = H5Dclose(dset);
    if (status < 0)
    {
        return -1;
    }

    status = H5Pclose(dprop);
    if (status < 0)
    {
        return -1;
    }

    status = H5Tclose(typeId);
    if (status < 0)
    {
        return -1;
    }

    return dset;
}

int writeBooleanMatrix6(int parent, const char* name, int dims, int* pdims, int* data)
{
    int iSize = 0;
    hsize_t* piDims = NULL;
    herr_t status = 0;
    hid_t iSpace = 0;
    hid_t iCompress = 0;
    hid_t dset = 0;
    hid_t dprop = 0;

    piDims = convertDims(&dims, pdims, &iSize);

    //Create dataspace.  Setting maximum size to NULL sets the maximum size to be the current size.
    iSpace = H5Screate_simple(dims, piDims, NULL);
    if (iSpace < 0)
    {
        FREE(piDims);
        return -1;
    }

    //Create the dataset and write the array data to it.
    iCompress = enableCompression(9, dims, piDims);
    FREE(piDims);

    dprop = H5Pcreate(H5P_DATASET_CREATE);
    H5Pset_obj_track_times(dprop, 0);
    dset = H5Dcreate(parent, name, H5T_NATIVE_INT, iSpace, iCompress, dprop, H5P_DEFAULT);
    if (dset < 0)
    {
        return -1;
    }

    status = H5Dwrite(dset, H5T_NATIVE_INT, H5S_ALL, H5S_ALL, H5P_DEFAULT, data);
    if (status < 0)
    {
        return -1;
    }

    //Add attribute SCILAB_Class = double to dataset
    status = addAttribute(dset, g_SCILAB_CLASS, g_SCILAB_CLASS_BOOLEAN);
    if (status < 0)
    {
        return -1;
    }

    //Close and release resources.
    status = H5Dclose(dset);
    if (status < 0)
    {
        return -1;
    }

    status = H5Pclose(dprop);
    if (status < 0)
    {
        return -1;
    }

    status = H5Sclose(iSpace);
    if (status < 0)
    {
        return -1;
    }

    return dset;
}

int writeIntegerMatrix6(int parent, const char* name, int type, const char* prec, int dims, int* pdims, void* data)
{
    hsize_t* piDims = NULL;
    herr_t status = 0;
    hid_t space = 0;
    hid_t dset = 0;
    hid_t compress = 0;
    int size = 0;
    hid_t dprop = 0;

    piDims = convertDims(&dims, pdims, &size);

    if (dims == 0 || (dims == 2 && pdims[0] == 0 && pdims[1] == 0))
    {
        // []
        space = H5Screate_simple(0, NULL, NULL);
        if (space < 0)
        {
            free(piDims);
            return -1;
        }

        //Create the dataset and write the array data to it.
        compress = enableCompression(9, dims, piDims);
        free(piDims);

        dprop = H5Pcreate(H5P_DATASET_CREATE);
        H5Pset_obj_track_times(dprop, 0);
        dset = H5Dcreate(parent, name, H5T_NATIVE_DOUBLE, space, compress, dprop, H5P_DEFAULT);
        if (dset < 0)
        {
            return -1;
        }
    }
    else
    {
        //Create dataspace.  Setting maximum size to NULL sets the maximum size to be the current size.
        space = H5Screate_simple(dims, piDims, NULL);
        if (space < 0)
        {
            FREE(piDims);
            return -1;
        }
        //Create the dataset and write the array data to it.
        compress = enableCompression(9, dims, piDims);
        FREE(piDims);

        dprop = H5Pcreate(H5P_DATASET_CREATE);
        H5Pset_obj_track_times(dprop, 0);
        dset = H5Dcreate(parent, name, type, space, compress, dprop, H5P_DEFAULT);
        if (dset < 0)
        {
            return -1;
        }

        status = H5Dwrite(dset, type, H5S_ALL, H5S_ALL, H5P_DEFAULT, data);
        if (status < 0)
        {
            return -1;
        }
    }
    //Add attribute SCILAB_Class = double to dataset
    status = addAttribute(dset, g_SCILAB_CLASS, g_SCILAB_CLASS_INT);
    if (status < 0)
    {
        return -1;
    }

    status = addAttribute(dset, g_SCILAB_CLASS_PREC, prec);
    if (status < 0)
    {
        return -1;
    }

    //Close and release resources.
    status = H5Dclose(dset);
    if (status < 0)
    {
        return -1;
    }

    status = H5Pclose(dprop);
    if (status < 0)
    {
        return -1;
    }

    status = H5Sclose(space);
    if (status < 0)
    {
        return -1;
    }

    return 0;
}

int openList6(int parent, const char *name, const char* type)
{
    //First create a group to store all referenced objects.
    int group = H5Gcreate(parent, name, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
    //Add attribute SCILAB_Class = string to dataset
    if (addAttribute(group, g_SCILAB_CLASS, type) < 0)
    {
        return -1;
    }

    return group;
}

int closeList6(int lst)
{
    if (H5Gclose(lst) < 0)
    {
        return -1;
    }

    return 0;
}

int addItemStruct6(int dataset, hobj_ref_t * refs, int pos, const char *name)
{
    herr_t status = H5Rcreate(&refs[pos], dataset, name, H5R_OBJECT, -1);
    if (status < 0)
    {
        return -1;
    }

    return status;
}

int writeStructField6(int parent, const char* name, int dims, int* pdims, hobj_ref_t * refs)
{
    hid_t space = 0;
    hid_t dset = 0;
    herr_t status = 0;
    hsize_t *piDims = NULL;
    hid_t iCompress = 0;
    hid_t dprop = 0;
    int i = 0;
    int iSize = 0;

    piDims = convertDims(&dims, pdims, &iSize);

    //Create dataspace.  Setting maximum size to NULL sets the maximum size to be the current size.
    space = H5Screate_simple(dims, piDims, NULL);
    if (space < 0)
    {
        free(piDims);
        return -1;
    }

    //Create the dataset and write the array data to it.
    iCompress = enableCompression(9, dims, piDims);
    free(piDims);

    dprop = H5Pcreate(H5P_DATASET_CREATE);
    H5Pset_obj_track_times(dprop, 0);
    dset = H5Dcreate(parent, name, H5T_STD_REF_OBJ, space, iCompress, dprop, H5P_DEFAULT);
    if (dset < 0)
    {
        return -1;
    }

    status = H5Dwrite(dset, H5T_STD_REF_OBJ, H5S_ALL, H5S_ALL, H5P_DEFAULT, refs);
    if (status < 0)
    {
        return -1;
    }

    //Close and release resources.
    status = H5Dclose(dset);
    if (status < 0)
    {
        return -1;
    }

    status = H5Pclose(dprop);
    if (status < 0)
    {
        return -1;
    }

    status = H5Sclose(space);
    if (status < 0)
    {
        return -1;
    }

    return dset;
}

int writeUndefined6(int parent, const char* name)
{
    hsize_t piDims[1] = {1};
    herr_t status = 0;
    hid_t iSpace = 0;
    hid_t iDataset = 0;
    hid_t iCompress = 0;
    hid_t dprop = 0;
    char cData = 0;

    //Create dataspace.  Setting maximum size to NULL sets the maximum size to be the current size.
    iSpace = H5Screate_simple(1, piDims, NULL);
    if (iSpace < 0)
    {
        return -1;
    }
    //Create the dataset and write the array data to it.
    iCompress = enableCompression(9, 1, piDims);

    dprop = H5Pcreate(H5P_DATASET_CREATE);
    H5Pset_obj_track_times(dprop, 0);
    iDataset = H5Dcreate(parent, name, H5T_NATIVE_INT8, iSpace, iCompress, dprop, H5P_DEFAULT);
    if (iDataset < 0)
    {
        return -1;
    }

    status = H5Dwrite(iDataset, H5T_NATIVE_INT8, H5S_ALL, H5S_ALL, H5P_DEFAULT, &cData);
    if (status < 0)
    {
        return -1;
    }

    //Add attribute SCILAB_Class = double to dataset
    status = addAttribute(iDataset, g_SCILAB_CLASS, g_SCILAB_CLASS_UNDEFINED);
    if (status < 0)
    {
        return -1;
    }

    //Close and release resources.
    status = H5Dclose(iDataset);
    if (status < 0)
    {
        return -1;
    }

    status = H5Pclose(dprop);
    if (status < 0)
    {
        return -1;
    }

    status = H5Sclose(iSpace);
    if (status < 0)
    {
        return -1;
    }

    return 0;
}
