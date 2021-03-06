/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2010 - 2012 - INRIA - Allan CORNET
 * Copyright (C) 2011 - INRIA - Michael Baudin
 *
 * Copyright (C) 2012 - 2016 - Scilab Enterprises
 *
 * This file is hereby licensed under the terms of the GNU GPL v2.0,
 * pursuant to article 5.3.4 of the CeCILL v.2.1.
 * This file was originally licensed under the terms of the CeCILL v2.1,
 * and continues to be available under such terms.
 * For more information, see the COPYING file which you should have received
 * along with this program.
 *
 * This code is also published under the GPL v3 license.
 *
 */
#include <string.h>
#include "gw_spreadsheet.h"
#include "api_scilab.h"
#include "Scierror.h"
#include "sci_malloc.h"
#include "Scierror.h"
#include "localization.h"
#include "freeArrayOfPtrs.h"
#include "stringToComplex.h"
#include "csvDefault.h"
#include "csvRead.h"
#include "getRange.h"
#include "gw_csv_helpers.h"
#include "os_string.h"
#include "strcmp.h"

static void freeVar(char*** text, int sizeText, int** lengthText, char** separator, char** decimal, char** conversion, int** iRange);
// =============================================================================
#define CONVTOSTR "string"
#define CONVTODOUBLE "double"
// =============================================================================
int sci_csvTextScan(char *fname, void* pvApiCtx)
{
    SciErr sciErr;
    int iErr = 0;
    int i = 0;

    int *piAddressVarOne = NULL;
    int m1 = 0, n1 = 0;
    int iType1 = 0;

    char **text = NULL;
    int *lengthText = NULL;
    int nbLines = 0;

    char *separator = NULL;
    char *decimal = NULL;
    char *conversion = NULL;

    double * dRealValues = NULL;

    int *iRange = NULL;
    int haveRange = 0;

    csvResult *result = NULL;

    CheckRhs(1, 5);
    CheckLhs(0, 1);

    if (Rhs == 5)
    {
        int m5 = 0, n5 = 0;

        iRange = csv_getArgumentAsMatrixofIntFromDouble(pvApiCtx, 5, fname, &m5, &n5, &iErr);
        if (iErr)
        {
            freeVar(&text, nbLines, &lengthText, &separator, &decimal, &conversion, &iRange);
            return 0;
        }

        if ((m5 * n5 != SIZE_RANGE_SUPPORTED) )
        {
            freeVar(&text, nbLines, &lengthText, &separator, &decimal, &conversion, &iRange);
            Scierror(999, _("%s: Wrong size for input argument #%d: Four entries expected.\n"), fname, 5);
            return 0;
        }

        if ((m5 != 1) && (n5 != 1))
        {
            freeVar(&text, nbLines, &lengthText, &separator, &decimal, &conversion, &iRange);
            Scierror(999, _("%s: Wrong size for input argument #%d: A column or row vector expected.\n"), fname, 5);
            return 0;
        }

        if (isValidRange(iRange, m5 * n5))
        {
            haveRange = 1;
        }
        else
        {
            freeVar(&text, nbLines, &lengthText, &separator, &decimal, &conversion, &iRange);
            Scierror(999, _("%s: Wrong value for input argument #%d: Inconsistent range.\n"), fname, 5);
            return 0;
        }
    }

    if (Rhs >= 4)
    {
        conversion = csv_getArgumentAsStringWithEmptyManagement(pvApiCtx, 4, fname, getCsvDefaultConversion(), &iErr);
        if (iErr)
        {
            freeVar(&text, nbLines, &lengthText, &separator, &decimal, &conversion, &iRange);
            return 0;
        }

        if (!((balisc_strcmp(conversion, CONVTOSTR) == 0) || (balisc_strcmp(conversion, CONVTODOUBLE) == 0)))
        {
            freeVar(&text, nbLines, &lengthText, &separator, &decimal, &conversion, &iRange);
            Scierror(999, _("%s: Wrong value for input argument #%d: '%s' or '%s' string expected.\n"), fname, 4, "double", "string");
            return 0;
        }
    }
    else
    {
        conversion = os_strdup(getCsvDefaultConversion());
    }

    if (Rhs >= 3)
    {
        decimal = csv_getArgumentAsStringWithEmptyManagement(pvApiCtx, 3, fname, getCsvDefaultDecimal(), &iErr);
        if (iErr)
        {
            freeVar(&text, nbLines, &lengthText, &separator, &decimal, &conversion, &iRange);
            return 0;
        }

        if (decimal[0] != '.' && decimal[0] != ',')
        {
            freeVar(&text, nbLines, &lengthText, &separator, &decimal, &conversion, &iRange);
            Scierror(999, _("%s: Wrong value for input argument #%d: '%s' or '%s' string expected.\n"), fname, 3, ",", ".");
            return 0;
        }
    }
    else
    {
        decimal = os_strdup(getCsvDefaultDecimal());
    }

    if (Rhs >= 2)
    {
        separator = csv_getArgumentAsStringWithEmptyManagement(pvApiCtx, 2, fname, getCsvDefaultSeparator(), &iErr);
        if (iErr)
        {
            freeVar(&text, nbLines, &lengthText, &separator, &decimal, &conversion, &iRange);
            return 0;
        }
    }
    else
    {
        separator = os_strdup(getCsvDefaultSeparator());
    }

    if (!csv_isRowVector(pvApiCtx, 1) &&
            !csv_isColumnVector(pvApiCtx, 1) &&
            !csv_isScalar(pvApiCtx, 1))
    {
        freeVar(&text, nbLines, &lengthText, &separator, &decimal, &conversion, &iRange);
        Scierror(999, _("%s: Wrong size for input argument #%d: String vector expected.\n"), fname, 1);
        return 0;
    }

    text = csv_getArgumentAsMatrixOfString(pvApiCtx, 1, fname, &m1, &n1, &iErr);
    if (iErr)
    {
        freeVar(&text, nbLines, &lengthText, &separator, &decimal, &conversion, &iRange);
        return 0;
    }

    nbLines = m1 * n1;
    result = csvTextScan((const char**)text, nbLines, separator, decimal);

    if (result)
    {
        switch (result->err)
        {
            case CSV_READ_SEPARATOR_DECIMAL_EQUAL:
            {
                Scierror(999, _("%s: separator and decimal must have different values.\n"), fname);
            }
            break;

            case CSV_READ_NO_ERROR:
            {
                if (balisc_strcmp(conversion, CONVTOSTR) == 0)
                {
                    if (haveRange)
                    {
                        int newM = 0;
                        int newN = 0;

                        char **pStrRange = getRangeAsString((const char**)result->pstrValues, result->m, result->n, iRange, &newM, &newN);
                        if (pStrRange)
                        {
                            sciErr = createMatrixOfString(pvApiCtx, Rhs + 1, newM, newN, pStrRange);
                            freeArrayOfPtrs((void**)pStrRange, newM * newN);
                        }
                        else
                        {
                            Scierror(999, _("%s: Memory allocation error.\n"), fname);
                        }
                    }
                    else
                    {
                        sciErr = createMatrixOfString(pvApiCtx, Rhs + 1, result->m, result->n, result->pstrValues);
                    }
                }
                else /* to double */
                {
                    stringToComplexError ierr = STRINGTOCOMPLEX_ERROR;
                    complexArray *ptrComplexArray = stringsToComplexArray((const char**)result->pstrValues, result->m * result->n, decimal, TRUE, &ierr);
                    if (ptrComplexArray == NULL)
                    {
                        if (ierr == STRINGTOCOMPLEX_ERROR)
                        {
                            Scierror(999, _("%s: can not convert data.\n"), fname);
                        }
                        else
                        {
                            Scierror(999, _("%s: Memory allocation error.\n"), fname);
                        }
                        freeCsvResult(result);
                        freeVar(&text, nbLines, &lengthText, &separator, &decimal, &conversion, &iRange);
                        return 0;
                    }

                    switch (ierr)
                    {
                        case STRINGTOCOMPLEX_NOT_A_NUMBER:
                        case STRINGTOCOMPLEX_NO_ERROR:
                        {
                            if (haveRange)
                            {
                                int newM = 0;
                                int newN = 0;
                                complexArray *csvComplexRange = getRangeAsComplexArray(ptrComplexArray, result->m, result->n, iRange, &newM, &newN);
                                if (csvComplexRange)
                                {
                                    if (csvComplexRange->isComplex)
                                    {
                                        sciErr = createComplexMatrixOfDouble(pvApiCtx, Rhs + 1, newM, newN, ptrComplexArray->realPart, ptrComplexArray->imagPart);
                                    }
                                    else
                                    {
                                        sciErr = createMatrixOfDouble(pvApiCtx, Rhs + 1, newM, newN, csvComplexRange->realPart);
                                    }
                                    freeComplexArray(csvComplexRange);
                                    csvComplexRange = NULL;
                                }
                                else
                                {
                                    Scierror(999, _("%s: Memory allocation error.\n"), fname);
                                }
                            }
                            else
                            {
                                if (ptrComplexArray->isComplex)
                                {
                                    sciErr = createComplexMatrixOfDouble(pvApiCtx, Rhs + 1, result->m, result->n, ptrComplexArray->realPart, ptrComplexArray->imagPart);
                                }
                                else
                                {
                                    sciErr = createMatrixOfDouble(pvApiCtx, Rhs + 1, result->m, result->n, ptrComplexArray->realPart);
                                }
                            }
                            freeComplexArray(ptrComplexArray);
                            ptrComplexArray = NULL;
                        }
                        break;

                        case STRINGTOCOMPLEX_MEMORY_ALLOCATION:
                        {
                            Scierror(999, _("%s: Memory allocation error.\n"), fname);
                        }
                        break;

                        default:
                        case STRINGTOCOMPLEX_ERROR:
                        {
                            Scierror(999, _("%s: can not convert data.\n"), fname);
                        }
                        break;
                    }
                }

                if (sciErr.iErr)
                {
                    printError(&sciErr, 0);
                    Scierror(17, _("%s: Memory allocation error.\n"), fname);
                    freeCsvResult(result);
                    freeVar(&text, nbLines, &lengthText, &separator, &decimal, &conversion, &iRange);
                    return 0;
                }
                else
                {
                    LhsVar(1) = Rhs + 1;
                    PutLhsVar();
                }
            }
            break;

            case CSV_READ_MEMORY_ALLOCATION:
            {
                Scierror(999, _("%s: Memory allocation error.\n"), fname);
            }
            break;

            case CSV_READ_COLUMNS_ERROR:
            {
                Scierror(999, _("%s: can not read text: Error in the column structure\n"), fname);
            }
            break;

            case CSV_READ_READLINES_ERROR:
            case CSV_READ_ERROR:
            case CSV_READ_MOPEN_ERROR:
            case CSV_READ_FILE_NOT_EXIST:
            case CSV_READ_REGEXP_ERROR:
            {
                Scierror(999, _("%s: can not read text.\n"), fname);
            }
            break;
        }
    }
    else
    {
        Scierror(999, _("%s: Memory allocation error.\n"), fname);
    }

    freeVar(&text, nbLines, &lengthText, &separator, &decimal, &conversion, &iRange);
    freeCsvResult(result);
    return 0;
}
// =============================================================================
static void freeVar(char*** text, int sizeText, int** lengthText, char** separator, char** decimal, char** conversion, int** iRange)
{
    if (text && *text)
    {
        freeArrayOfPtrs((void**)*text, sizeText);
        *text = NULL;
    }

    if (lengthText && *lengthText)
    {
        FREE(*lengthText);
        *lengthText = NULL;
    }

    if (separator && *separator)
    {
        FREE(*separator);
        *separator = NULL;
    }

    if (decimal && *decimal)
    {
        FREE(*decimal);
        *decimal = NULL;
    }

    if (conversion && *conversion)
    {
        FREE(*conversion);
        *conversion = NULL;
    }

    if (iRange && *iRange)
    {
        FREE(*iRange);
        *iRange = NULL;
    }
}
