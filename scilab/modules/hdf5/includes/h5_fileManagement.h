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

#ifndef __H5_FILEMANAGEMENT_H__
#define __H5_FILEMANAGEMENT_H__

void HDF5cleanup(void);
int createHDF5File(const char *name);
int openHDF5File(const char *name, int _iAppendMode);
void closeHDF5File(int file);
int isHDF5File(const char* _pstFilename);

#endif /* !__H5_FILEMANAGEMENT_H__ */
