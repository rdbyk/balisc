/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) INRIA - Allan CORNET
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

/*--------------------------------------------------------------------------*/
#ifndef __STRSUBST_H__
#define __STRSUBST_H__

#include <wchar.h>

/**
* substitute a character string by another in a character string
* @param[in] string
* @param[in] string to search in input_string
* @param[in] replacement_string
* @param[out] error returned by pcre_private
* @return substituted string
*/
char *strsub(const char* input_string, const char* string_to_search, const char* replacement_string);

wchar_t **wcssubst(const wchar_t** _pwstInput, int _iInputSize, const wchar_t* _pwstSearch, const wchar_t* _pwstReplace);
wchar_t **wcssubst_reg(const wchar_t** _pwstInput, int _iInputSize, const wchar_t* _pwstSearch, const wchar_t* _pwstReplace, int* _piErr);

wchar_t *wcssub(const wchar_t* _pwstInput, const wchar_t* _pwstSearch, const wchar_t* _pwstReplace);
wchar_t *wcssub_reg(const wchar_t* _pwstInput, const wchar_t* _pwstSearch, const wchar_t* _pwstReplace, int* _piErr);

#endif /* __STRSUBST_H__ */
