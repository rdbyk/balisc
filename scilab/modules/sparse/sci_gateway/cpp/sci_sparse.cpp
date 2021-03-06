/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2010-2010 - DIGITEO - Bernard HUGUENEY
 * Copyright (C) 2012 - 2016 - Scilab Enterprises
 * Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
 *
 * This file is hereby licensed under the terms of the GNU GPL v2.0,
 * pursuant to article 5.3.4 of the CeCILL v.2.1.
 * This file was originally licensed under the terms of the CeCILL v2.1,
 * and continues to be available under such terms.
 * For more information, see the COPYING file which you should have received
 * along with this program.
 *
 */

#include <algorithm>

#include "sparse_gw.hxx"
#include "function.hxx"
#include "sparse.hxx"

extern "C"
{
#include "charEncoding.h"
#include "Scierror.h"
#include "localization.h"
}

static const char fname[] = "sparse";

types::Function::ReturnValue sci_sparse(types::typed_list &in, int _piRetCount, types::typed_list &out)
{
    bool isValid = true;
    types::GenericType* pRetVal = NULL;

    // per the scilab manual sparse will take upto 3 arguments but no less than one
    if (in.size() < 1 || in.size() > 3)
    {
        Scierror(999, _("%s: Wrong number of input arguments: %d to %d expected.\n"), fname, 1, 3);
        return types::Function::Error;
    }

    for (int i = 0 ; isValid && i < in.size() ; i++)
    {
        // Valid input arguments are of Bool and Double types (dense or sparse)
        switch (in[i]->getType())
        {
            case types::InternalType::ScilabBool :
            case types::InternalType::ScilabSparseBool :
            {
                isValid = (i == (in.size() > 1) ? 1 : 0);
            }
            case types::InternalType::ScilabDouble :
            case types::InternalType::ScilabSparse :
            {
                break;
            }
            default :
            {
                isValid = false;
            }
        }

        if (!isValid)
        {
            Scierror(999, _("%s: Wrong type for input argument #%d: Matrix expected.\n"), fname, i + 1);
            return types::Function::Error;
        }

        // Valid input arguments are matrices and not hypermatrices
        if ( in[i]->getAs<types::GenericType>()->getDims() > 2 )
        {
            Scierror(999, _("%s: Wrong size for input argument #%d: A m-by-n matrix expected.\n"), fname, i + 1);
            return types::Function::Error;
        }

    }
    // if one argument is given, it will be a matrix of constant or sparse type, which will be converted into a sparse matrix
    if (in.size() == 1)
    {
        switch (in[0]->getType())
        {
            case types::InternalType::ScilabSparse :
            {
                pRetVal = new types::Sparse(*in[0]->getAs<types::Sparse>());
                break;
            }
            case types::InternalType::ScilabDouble :
            {
                if (in[0]->getAs<types::Double>()->isEmpty())
                {
                    pRetVal = new types::Sparse(0,0,false);
                    break;
                }

                if (in[0]->getAs<types::Double>()->isIdentity())
                {
                    out.push_back(in[0]);
                    return types::Function::OK;
                }

                pRetVal = new types::Sparse(*in[0]->getAs<types::Double>());
                break;
            }
            case types::InternalType::ScilabBool :
            {
                pRetVal = new types::SparseBool(*in[0]->getAs<types::Bool>());
                break;
            }
            case types::InternalType::ScilabSparseBool :
            {
                pRetVal = new types::SparseBool(*in[0]->getAs<types::SparseBool>());
                break;
            }
            default :
            {
                pRetVal = NULL;
            }
        }
    }
    else if (in.size() == 2 || in.size() == 3)
    {
        // if two arguments are given the first is a 'n x 2' matrix of the non zero indices and the second is a 'n x 1' vector of the values
        for (int i = 0 ; i < in.size() ; i++)
        {
            if (in[i]->isDouble() == false && !(in[i]->isBool() && i == 1))
            {
                Scierror(999, _("%s: Wrong type for input argument #%d: Real or Complex matrix expected.\n"), fname, i + 1);
                return types::Function::Error;
            }
        }

        types::Double* ij = in[0]->getAs<types::Double>();

        if (ij->getSize() > 0 && ij->getCols() != 2)
        {
            Scierror(999, _("%s: Wrong size for input argument #%d: A m-by-2 matrix expected.\n"), fname, 1);
            return types::Function::Error;
        }

        int size = ij->getRows();
        double* i = ij->get();
        double* j = i + ij->getRows();
        double row_idx_max = *std::max_element(i, i + size);
        double col_idx_max = *std::max_element(j, j + size);

        if (size && (row_idx_max < 1 || col_idx_max < 1))
        {
            Scierror(999, _("%s: Wrong value(s) for input argument #%d: elements greater or equal to 1.0 expected.\n"), fname, 1);
            return types::Function::Error;
        }

        types::GenericType* pGT2 = in[1]->getAs<types::GenericType>();

        if (pGT2->getSize() != ij->getRows())
        {
            Scierror(999, _("%s: Wrong size for input argument #%d: A vector of size %d expected.\n"), fname, 2, ij->getRows());
            return types::Function::Error;
        }

        types::Double* pDims = NULL;
        bool alloc = false;

        if (in.size() == 3)
        {
            pDims = in[2]->getAs<types::Double>();

            if (pDims->getRows() != 1 || pDims->getCols() != 2)
            {
                Scierror(999, _("%s: Wrong size for input argument #%d: A matrix of size %d x %d expected.\n"), fname, 3, 1, 2);
                return types::Function::Error;
            }

            double out_rows = pDims->getFirst();
            double out_cols = pDims->get(1);

            if (size && (row_idx_max > out_rows || col_idx_max > out_cols))
            {
                Scierror(999, _("%s: Wrong value(s) for input argument #%d: greater or equal to [%d,%d] expected.\n"), fname, 3, static_cast<int>(row_idx_max), static_cast<int>(col_idx_max));
                return types::Function::Error;
            }

            if (out_rows <= 0 || out_cols <= 0)
            {
                out.push_back(types::Double::Empty());
                return types::Function::OK;
            }

            if (out_rows >= INT_MAX || out_cols >= INT_MAX)
            {
                Scierror(999, _("%s: Wrong value(s) for input argument #%d: elements less than %d expected.\n"), fname, 3, INT_MAX);
                return types::Function::Error;
            }
        }
        else
        {
            if (size)
            {
                pDims = new types::Double(1, 2, false);
                pDims->set(0, row_idx_max);
                pDims->set(1, col_idx_max);
                alloc = true;
            }
            else
            {
                out.push_back(types::Double::Empty());
                return types::Function::OK;
            }
        }

        if (in[1]->isDouble())
        {
            types::Double* dbl = pGT2->getAs<types::Double>();
            pRetVal = new types::Sparse(*dbl, *ij, *pDims);
        }
        else
        {
            types::Bool* b = pGT2->getAs<types::Bool>();
            pRetVal = new types::SparseBool(*b, *ij, *pDims);
        }

        if (alloc)
        {
            delete pDims;
        }
    }

    if (pRetVal == NULL)
    {
        return types::Function::Error;
    }

    out.push_back(pRetVal);
    return types::Function::OK;
}
