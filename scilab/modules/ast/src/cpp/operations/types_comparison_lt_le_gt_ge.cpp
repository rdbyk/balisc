/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2008-2008 - DIGITEO - Antoine ELIAS
 * Copyright (C) 2010-2010 - DIGITEO - Bruno JOFRET
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

#include "types_comparison_lt_le_gt_ge.hxx"
#include "double.hxx"
#include "sparse.hxx"
#include "int.hxx"

extern "C"
{
#include "localization.h"
#include "charEncoding.h"
}

using namespace types;

InternalType *GenericLess(InternalType *_pLeftOperand, InternalType *_pRightOperand)
{
    InternalType *pResult = NULL;

    /*
    ** [] < A TYPE
    */
    if (_pLeftOperand->isDouble() && _pLeftOperand->getAs<Double>()->isEmpty())
    {
        return _pLeftOperand->getRef() > 0 ? Double::Empty() : _pLeftOperand;
    }

    /*
    ** A TYPE < []
    */
    if (_pRightOperand->isDouble() && _pRightOperand->getAs<Double>()->isEmpty())
    {
        return _pRightOperand->getRef() > 0 ? Double::Empty() : _pRightOperand;
    }

    /*
    ** DOUBLE < DOUBLE
    */
    if (_pLeftOperand->isDouble() && _pRightOperand->isDouble())
    {
        Double *pL = _pLeftOperand->getAs<Double>();
        Double *pR = _pRightOperand->getAs<Double>();

        int iResult = DoubleLessDouble(pL, pR, (Bool**)&pResult);
        if (iResult)
        {
            throw ast::InternalError(_W("Inconsistent row/column dimensions.\n"));
        }

        return pResult;
    }

    /*
    ** SPARSE < SPARSE
    */
    if (_pLeftOperand->isSparse() && _pRightOperand->isSparse())
    {
        Sparse *pL = _pLeftOperand->getAs<Sparse>();
        Sparse *pR = _pRightOperand->getAs<Sparse>();

        int iResult = SparseLessSparse(pL, pR, (SparseBool**)&pResult);
        if (iResult)
        {
            throw ast::InternalError(_W("Inconsistent row/column dimensions.\n"));
        }

        return pResult;
    }

    /*
    ** DOUBLE < SPARSE
    */
    if (_pLeftOperand->isDouble() && _pRightOperand->isSparse())
    {
        Double *pL = _pLeftOperand->getAs<Double>();
        Sparse *pR = _pRightOperand->getAs<Sparse>();

        int iResult = DoubleLessSparse(pL, pR, (SparseBool**)&pResult);
        if (iResult)
        {
            throw ast::InternalError(_W("Inconsistent row/column dimensions.\n"));
        }

        return pResult;
    }

    /*
    ** SPARSE < DOUBLE
    */
    if (_pLeftOperand->isSparse() && _pRightOperand->isDouble())
    {
        Sparse *pL = _pLeftOperand->getAs<Sparse>();
        Double *pR = _pRightOperand->getAs<Double>();

        int iResult = SparseLessDouble(pL, pR, (SparseBool**)&pResult);
        if (iResult)
        {
            throw ast::InternalError(_W("Inconsistent row/column dimensions.\n"));
        }

        return pResult;
    }


    /*
    ** INT < INT
    */
    if (_pLeftOperand->isInt() && _pRightOperand->isInt())
    {
        if (_pLeftOperand->getType() != _pRightOperand->getType())
        {
            //call overload function to convert left or right or both to have comparable type
            return NULL;
        }

        int iResult = IntLessInt(_pLeftOperand, _pRightOperand, (GenericType**)&pResult);
        if (iResult)
        {
            throw ast::InternalError(_W("Inconsistent row/column dimensions.\n"));
        }

        return pResult;
    }
    return NULL;
}

int DoubleLessDouble(Double* _pDouble1, Double* _pDouble2, Bool** _pOut)
{
    if (_pDouble1->isComplex() || _pDouble2->isComplex())
    {
        //call overload for complex cases
        return 0;
    }

    int iCase = 2*(_pDouble2->getSize() == 1) + (_pDouble1->getSize() == 1);

    switch (iCase)
    {
        case 1:  // only 1st arg is scalar or eye()
            {
                Bool* pB = new Bool(_pDouble2->getDims(), _pDouble2->getDimsArray());

                if (_pDouble1->getRows() == -1) // FIXME: better check for eye()
                {
                    for (int i = 0; i < pB->getRows(); ++i)
                    {
                        for (int j = 0; j < pB->getCols(); ++j)
                        {
                            if (i != j)
                            {
                                pB->set(i,j, 0.0 < _pDouble2->get(i,j));
                            }
                            else
                            {
                                pB->set(i,j, 1.0 < _pDouble2->get(i,j));
                            }
                        }
                    }
                }
                else
                {
                    int* pb = pB->get();
                    double dblRef = _pDouble1->getFirst();

                    for (int i = 0; i < pB->getSize(); ++i)
                    {
                        pb[i] = dblRef < _pDouble2->get(i);
                    }
                }

                *_pOut = pB;
            }
            break;

        case 2:  // only 2nd arg is scalar or eye()
            {
                Bool* pB = new Bool(_pDouble1->getDims(), _pDouble1->getDimsArray());

                if (_pDouble2->getRows() == -1) // FIXME: better check for eye()
                {
                    for (int i = 0; i < pB->getRows(); ++i)
                    {
                        for (int j = 0; j < pB->getCols(); ++j)
                        {
                            if (i != j)
                            {
                                pB->set(i,j, _pDouble1->get(i,j) < 0.0);
                            }
                            else
                            {
                                pB->set(i,j, _pDouble1->get(i,j) < 1.0);
                            }
                        }
                    }
                }
                else
                {
                    int* pb = pB->get();
                    double dblRef = _pDouble2->getFirst();

                    for (int i = 0 ; i < pB->getSize() ; i++)
                    {
                        pb[i] = _pDouble1->get(i) < dblRef;
                    }
                }

                *_pOut = pB;
            }
            break;

        case 3:  // both args are scalar or eye()
            *_pOut = new Bool(_pDouble1->getFirst() < _pDouble2->getFirst());
            break;

        default: // no arg is scalar or eye()
            {
                if (_pDouble1->getDims() != _pDouble2->getDims())
                {
                    return 1;
                }

                int* piDims1 = _pDouble1->getDimsArray();
                int* piDims2 = _pDouble2->getDimsArray();

                for (int i = 0 ; i < _pDouble1->getDims() ; i++)
                {
                    if (piDims1[i] != piDims2[i])
                    {
                        return 1;
                    }
                }

                Bool* pB = new Bool(_pDouble1->getDims(), _pDouble1->getDimsArray());
                int* pb = pB->get();

                for (int i = 0 ; i < pB->getSize() ; i++)
                {
                    pb[i] = _pDouble1->get(i) < _pDouble2->get(i);
                }

                *_pOut = pB;
            }
            break;
    }

    return 0;
}

int SparseLessSparse(Sparse* _pSparse1, Sparse* _pSparse2, SparseBool** _pOut)
{
    if (_pSparse1->isComplex() || _pSparse2->isComplex())
    {
        //call overload for complex cases
        return 0;
    }

    if (_pSparse1->isScalar() || _pSparse2->isScalar() || //scalar cases
            (_pSparse1->getRows() == _pSparse2->getRows() && _pSparse1->getCols() == _pSparse2->getCols())) //matrix case
    {
        *_pOut = _pSparse1->newLessThan(*_pSparse2);
        return 0;
    }

    *_pOut = NULL;
    return 1;
}

int DoubleLessSparse(Double* _pDouble, Sparse* _pSparse, SparseBool** _pOut)
{
    Sparse* pSparse = new Sparse(*_pDouble);
    int iRet = SparseLessSparse(pSparse, _pSparse, _pOut);
    delete pSparse;
    return iRet;
}

int SparseLessDouble(Sparse* _pSparse, Double* _pDouble, SparseBool** _pOut)
{
    Sparse* pSparse = new Sparse(*_pDouble);
    int iRet = SparseLessSparse(_pSparse, pSparse, _pOut);
    delete pSparse;
    return iRet;
}


InternalType *GenericLessEqual(InternalType *_pLeftOperand, InternalType *_pRightOperand)
{
    InternalType *pResult = NULL;

    /*
    ** [] <= A TYPE
    */
    if (_pLeftOperand->isDouble() && _pLeftOperand->getAs<Double>()->isEmpty())
    {
        return _pLeftOperand->getRef() > 0 ? Double::Empty() : _pLeftOperand;
    }

    /*
    ** A TYPE <= []
    */
    if (_pRightOperand->isDouble() && _pRightOperand->getAs<Double>()->isEmpty())
    {
        return _pRightOperand->getRef() > 0 ? Double::Empty() : _pRightOperand;
    }

    /*
    ** DOUBLE <= DOUBLE
    */
    if (_pLeftOperand->isDouble() && _pRightOperand->isDouble())
    {
        Double *pL = _pLeftOperand->getAs<Double>();
        Double *pR = _pRightOperand->getAs<Double>();

        int iResult = DoubleLessEqualDouble(pL, pR, (Bool**)&pResult);
        if (iResult)
        {
            throw ast::InternalError(_W("Inconsistent row/column dimensions.\n"));
        }

        return pResult;
    }

    /*
    ** SPARSE <= SPARSE
    */
    if (_pLeftOperand->isSparse() && _pRightOperand->isSparse())
    {
        Sparse *pL = _pLeftOperand->getAs<Sparse>();
        Sparse *pR = _pRightOperand->getAs<Sparse>();

        int iResult = SparseLessEqualSparse(pL, pR, (SparseBool**)&pResult);
        if (iResult)
        {
            throw ast::InternalError(_W("Inconsistent row/column dimensions.\n"));
        }

        return pResult;
    }

    /*
    ** DOUBLE <= SPARSE
    */
    if (_pLeftOperand->isDouble() && _pRightOperand->isSparse())
    {
        Double *pL = _pLeftOperand->getAs<Double>();
        Sparse *pR = _pRightOperand->getAs<Sparse>();

        int iResult = DoubleLessEqualSparse(pL, pR, (SparseBool**)&pResult);
        if (iResult)
        {
            throw ast::InternalError(_W("Inconsistent row/column dimensions.\n"));
        }

        return pResult;
    }

    /*
    ** SPARSE <= DOUBLE
    */
    if (_pLeftOperand->isSparse() && _pRightOperand->isDouble())
    {
        Sparse *pL = _pLeftOperand->getAs<Sparse>();
        Double *pR = _pRightOperand->getAs<Double>();

        int iResult = SparseLessEqualDouble(pL, pR, (SparseBool**)&pResult);
        if (iResult)
        {
            throw ast::InternalError(_W("Inconsistent row/column dimensions.\n"));
        }

        return pResult;
    }

    /*
    ** INT <= INT
    */
    if (_pLeftOperand->isInt() && _pRightOperand->isInt())
    {
        if (_pLeftOperand->getType() != _pRightOperand->getType())
        {
            //call overload function to convert left or right or both to have comparable type
            return NULL;
        }

        int iResult = IntLessEqualInt(_pLeftOperand, _pRightOperand, (GenericType**)&pResult);
        if (iResult)
        {
            throw ast::InternalError(_W("Inconsistent row/column dimensions.\n"));
        }

        return pResult;
    }
    return NULL;
}

int DoubleLessEqualDouble(Double* _pDouble1, Double* _pDouble2, Bool** _pOut)
{
    if (_pDouble1->isComplex() || _pDouble2->isComplex())
    {
        //call overload for complex cases
        return 0;
    }

    int iCase = 2*(_pDouble2->getSize() == 1) + (_pDouble1->getSize() == 1);

    switch (iCase)
    {
        case 1:  // only 1st arg is scalar or eye()
            {
                Bool* pB = new Bool(_pDouble2->getDims(), _pDouble2->getDimsArray());

                if (_pDouble1->getRows() == -1) // FIXME: better check for eye()
                {
                    for (int i = 0; i < pB->getRows(); ++i)
                    {
                        for (int j = 0; j < pB->getCols(); ++j)
                        {
                            if (i != j)
                            {
                                pB->set(i,j, 0.0 <= _pDouble2->get(i,j));
                            }
                            else
                            {
                                pB->set(i,j, 1.0 <= _pDouble2->get(i,j));
                            }
                        }
                    }
                }
                else
                {
                    int* pb = pB->get();
                    double dblRef = _pDouble1->getFirst();

                    for (int i = 0; i < pB->getSize(); ++i)
                    {
                        pb[i] = dblRef <= _pDouble2->get(i);
                    }
                }

                *_pOut = pB;
            }
            break;

        case 2:  // only 2nd arg is scalar or eye()
            {
                Bool* pB = new Bool(_pDouble1->getDims(), _pDouble1->getDimsArray());

                if (_pDouble2->getRows() == -1) // FIXME: better check for eye()
                {
                    for (int i = 0; i < pB->getRows(); ++i)
                    {
                        for (int j = 0; j < pB->getCols(); ++j)
                        {
                            if (i != j)
                            {
                                pB->set(i,j, _pDouble1->get(i,j) <= 0.0);
                            }
                            else
                            {
                                pB->set(i,j, _pDouble1->get(i,j) <= 1.0);
                            }
                        }
                    }
                }
                else
                {
                    int* pb = pB->get();
                    double dblRef = _pDouble2->getFirst();

                    for (int i = 0 ; i < pB->getSize() ; i++)
                    {
                        pb[i] = _pDouble1->get(i) <= dblRef;
                    }
                }

                *_pOut = pB;
            }
            break;

        case 3:  // both args are scalar or eye()
            *_pOut = new Bool(_pDouble1->getFirst() <= _pDouble2->getFirst());
            break;

        default: // no arg is scalar or eye()
            {
                if (_pDouble1->getDims() != _pDouble2->getDims())
                {
                    return 1;
                }

                int* piDims1 = _pDouble1->getDimsArray();
                int* piDims2 = _pDouble2->getDimsArray();

                for (int i = 0 ; i < _pDouble1->getDims() ; i++)
                {
                    if (piDims1[i] != piDims2[i])
                    {
                        return 1;
                    }
                }

                Bool* pB = new Bool(_pDouble1->getDims(), _pDouble1->getDimsArray());
                int* pb = pB->get();

                for (int i = 0 ; i < pB->getSize() ; i++)
                {
                    pb[i] = _pDouble1->get(i) <= _pDouble2->get(i);
                }

                *_pOut = pB;
            }
            break;
    }

    return 0;
}

int SparseLessEqualSparse(Sparse* _pSparse1, Sparse* _pSparse2, SparseBool** _pOut)
{
    if (_pSparse1->isComplex() || _pSparse2->isComplex())
    {
        //call overload for complex cases
        return 0;
    }

    if (_pSparse1->isScalar() || _pSparse2->isScalar() || //scalar cases
            (_pSparse1->getRows() == _pSparse2->getRows() && _pSparse1->getCols() == _pSparse2->getCols())) //matrix case
    {
        *_pOut = _pSparse1->newLessOrEqual(*_pSparse2);
        return 0;
    }

    *_pOut = NULL;
    return 1;
}

int DoubleLessEqualSparse(Double* _pDouble, Sparse* _pSparse, SparseBool** _pOut)
{
    Sparse* pSparse = new Sparse(*_pDouble);
    int iRet = SparseLessEqualSparse(pSparse, _pSparse, _pOut);
    delete pSparse;
    return iRet;
}

int SparseLessEqualDouble(Sparse* _pSparse, Double* _pDouble, SparseBool** _pOut)
{
    Sparse* pSparse = new Sparse(*_pDouble);
    int iRet = SparseLessEqualSparse(_pSparse, pSparse, _pOut);
    delete pSparse;
    return iRet;
}

InternalType *GenericGreater(InternalType *_pLeftOperand, InternalType *_pRightOperand)
{
    return GenericLess(_pRightOperand, _pLeftOperand);
}

InternalType *GenericGreaterEqual(InternalType *_pLeftOperand, InternalType *_pRightOperand)
{
    return GenericLessEqual(_pRightOperand, _pLeftOperand);
}

template <class T>
static int IntLessInt(T* _pL, T* _pR, types::GenericType** _pOut)
{
    if (_pL->isScalar())
    {
        Bool *pB = new Bool(_pR->getDims(), _pR->getDimsArray());

        int* pb = pB->get();
        const typename T::type x = _pL->getFirst();

        for (int i = 0 ; i < pB->getSize() ; i++)
        {
            pb[i] = x < _pR->get(i);
        }

        *_pOut = pB;
        return 0;
    }

    if (_pR->isScalar())
    {
        Bool *pB = new Bool(_pL->getDims(), _pL->getDimsArray());

        int* pb = pB->get();
        const typename T::type x = _pR->getFirst();

        for (int i = 0 ; i < pB->getSize() ; i++)
        {
            pb[i] = _pL->get(i) < x;
        }

        *_pOut = pB;
        return 0;
    }

    if (_pL->getDims() != _pR->getDims())
    {
        return 1;
    }

    int* piDimsL = _pL->getDimsArray();
    int* piDimsR = _pR->getDimsArray();

    for (int i = 0 ; i < _pL->getDims() ; i++)
    {
        if (piDimsL[i] != piDimsR[i])
        {
            return 1;
        }
    }

    Bool* pB = new Bool(_pR->getDims(), _pR->getDimsArray());
    int* pb = pB->get();

    for (int i = 0 ; i < _pL->getSize() ; i++)
    {
        pb[i] = _pL->get(i) < _pR->get(i);
    }

    *_pOut = pB;
    return 0;
}

int IntLessInt(types::InternalType* _pL, types::InternalType*  _pR, types::GenericType** _pOut)
{
    switch (_pL->getType())
    {
        case InternalType::ScilabInt8 :
        {
            return IntLessInt(_pL->getAs<Int8>(), _pR->getAs<Int8>(), _pOut);
        }
        case InternalType::ScilabUInt8 :
        {
            return IntLessInt(_pL->getAs<UInt8>(), _pR->getAs<UInt8>(), _pOut);
        }
        case InternalType::ScilabInt16 :
        {
            return IntLessInt(_pL->getAs<Int16>(), _pR->getAs<Int16>(), _pOut);
        }
        case InternalType::ScilabUInt16 :
        {
            return IntLessInt(_pL->getAs<UInt16>(), _pR->getAs<UInt16>(), _pOut);
        }
        case InternalType::ScilabInt32 :
        {
            return IntLessInt(_pL->getAs<Int32>(), _pR->getAs<Int32>(), _pOut);
        }
        case InternalType::ScilabUInt32 :
        {
            return IntLessInt(_pL->getAs<UInt32>(), _pR->getAs<UInt32>(), _pOut);
        }
        case InternalType::ScilabInt64 :
        {
            return IntLessInt(_pL->getAs<Int64>(), _pR->getAs<Int64>(), _pOut);
        }
        case InternalType::ScilabUInt64 :
        {
            return IntLessInt(_pL->getAs<UInt64>(), _pR->getAs<UInt64>(), _pOut);
        }
        default:
        {
            return 0;
        }
    }
}

template <class T>
static int IntLessEqualInt(T* _pL, T* _pR, types::GenericType** _pOut)
{
    if (_pL->isScalar())
    {
        Bool *pB = new Bool(_pR->getDims(), _pR->getDimsArray());

        int* pb = pB->get();
        const typename T::type x = _pL->getFirst();

        for (int i = 0 ; i < pB->getSize() ; i++)
        {
            pb[i] = x <= _pR->get(i);
        }

        *_pOut = pB;
        return 0;
    }

    if (_pR->isScalar())
    {
        Bool *pB = new Bool(_pL->getDims(), _pL->getDimsArray());

        int* pb = pB->get();
        const typename T::type x = _pR->getFirst();

        for (int i = 0 ; i < pB->getSize() ; i++)
        {
            pb[i] = _pL->get(i) <= x;
        }

        *_pOut = pB;
        return 0;
    }

    if (_pL->getDims() != _pR->getDims())
    {
        return 1;
    }

    int* piDimsL = _pL->getDimsArray();
    int* piDimsR = _pR->getDimsArray();

    for (int i = 0 ; i < _pL->getDims() ; i++)
    {
        if (piDimsL[i] != piDimsR[i])
        {
            return 1;
        }
    }

    Bool* pB = new Bool(_pR->getDims(), _pR->getDimsArray());
    int* pb = pB->get();

    for (int i = 0 ; i < _pL->getSize() ; i++)
    {
        pb[i] = _pL->get(i) <= _pR->get(i);
    }

    *_pOut = pB;
    return 0;
}

int IntLessEqualInt(types::InternalType* _pL, types::InternalType* _pR, types::GenericType** _pOut)
{
    switch (_pL->getType())
    {
        case InternalType::ScilabInt8 :
        {
            return IntLessEqualInt(_pL->getAs<Int8>(), _pR->getAs<Int8>(), _pOut);
        }
        case InternalType::ScilabUInt8 :
        {
            return IntLessEqualInt(_pL->getAs<UInt8>(), _pR->getAs<UInt8>(), _pOut);
        }
        case InternalType::ScilabInt16 :
        {
            return IntLessEqualInt(_pL->getAs<Int16>(), _pR->getAs<Int16>(), _pOut);
        }
        case InternalType::ScilabUInt16 :
        {
            return IntLessEqualInt(_pL->getAs<UInt16>(), _pR->getAs<UInt16>(), _pOut);
        }
        case InternalType::ScilabInt32 :
        {
            return IntLessEqualInt(_pL->getAs<Int32>(), _pR->getAs<Int32>(), _pOut);
        }
        case InternalType::ScilabUInt32 :
        {
            return IntLessEqualInt(_pL->getAs<UInt32>(), _pR->getAs<UInt32>(), _pOut);
        }
        case InternalType::ScilabInt64 :
        {
            return IntLessEqualInt(_pL->getAs<Int64>(), _pR->getAs<Int64>(), _pOut);
        }
        case InternalType::ScilabUInt64 :
        {
            return IntLessEqualInt(_pL->getAs<UInt64>(), _pR->getAs<UInt64>(), _pOut);
        }
        default:
        {
            return 0;
        }
    }
}
