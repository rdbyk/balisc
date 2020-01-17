/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2008-2008 - DIGITEO - Antoine ELIAS
 * Copyright (C) 2012 - 2016 - Scilab Enterprises
 * Copyright (C) 2018 - 2019 Dirk Reusch, Kybernetik Dr. Reusch
 *
 * This file is hereby licensed under the terms of the GNU GPL v2.0,
 * pursuant to article 5.3.4 of the CeCILL v.2.1.
 * This file was originally licensed under the terms of the CeCILL v2.1,
 * and continues to be available under such terms.
 * For more information, see the COPYING file which you should have received
 * along with this program.
 *
 */

//file included in runvisitor.cpp
namespace ast {

template<class T>
void RunVisitorT<T>::visitprivate(const OpExp &e)
{
    CoverageInstance::invokeAndStartChrono((void*)&e);
    types::InternalType * pITL = NULL, *pITR = NULL, *pResult = NULL;
    try
    {
        /*getting what to assign*/
        e.getLeft().accept(*this);
        if (isSingleResult() == false)
        {
            clearResult();
            throw ast::InternalError(5, e.getRight().getLocation());
        }

        pITL = getResult();
        if (pITL == nullptr)
        {
            clearResult();
            char* strOp = wide_string_to_UTF8(e.getString().c_str());
            InternalError ie(42,  e.getLeft().getLocation(), strOp, 1);
            FREE(strOp);
            throw ie;
        }

        /*getting what to assign*/
        e.getRight().accept(*this);
        if (isSingleResult() == false)
        {
            clearResult();
            throw ast::InternalError(5, e.getRight().getLocation());
        }

        pITR = getResult();
        if (pITR == nullptr)
        {
            clearResult();
            char* strOp = wide_string_to_UTF8(e.getString().c_str());
            InternalError ie(42,  e.getLeft().getLocation(), strOp, 2);
            FREE(strOp);
            throw ie;
        }

        if (pITL->getType() == types::InternalType::ScilabImplicitList)
        {
            types::ImplicitList* pIL = pITL->getAs<types::ImplicitList>();
            if (pIL->isComputable())
            {
                pITL = pIL->extractFullMatrix();
                pIL->killMe();
            }
        }

        if (pITR->getType() == types::InternalType::ScilabImplicitList)
        {
            types::ImplicitList* pIR = pITR->getAs<types::ImplicitList>();
            if (pIR->isComputable())
            {
                pITR = pIR->extractFullMatrix();
                pIR->killMe();
            }
        }

        switch (e.getOper())
        {
            case OpExp::unaryPlus:
            {
                pResult = GenericUnaryPlus(pITR);
                break;
            }
            case OpExp::plus:
            {
                pResult = GenericPlus(pITL, pITR);
                break;
            }
            case OpExp::unaryMinus:
            {
                pResult = GenericUnaryMinus(pITR);
                break;
            }
            case OpExp::minus:
            {
                pResult = GenericMinus(pITL, pITR);
                break;
            }
            case OpExp::times:
            {
                pResult = GenericTimes(pITL, pITR);
                break;
            }
            case OpExp::ldivide:
            {
                pResult = GenericLDivide(pITL, pITR);
                break;
            }
            case OpExp::dotldivide:
            {
                pResult = GenericDotLDivide(pITL, pITR);
                break;
            }
            case OpExp::rdivide:
            {
                pResult = GenericRDivide(pITL, pITR);
                break;
            }
            case OpExp::dotrdivide:
            {
                pResult = GenericDotRDivide(pITL, pITR);
                break;
            }
            case OpExp::dottimes:
            {
                pResult = GenericDotTimes(pITL, pITR);
                break;
            }
            case OpExp::dotpower:
            {
                pResult = GenericDotPower(pITL, pITR);
                break;
            }
            case OpExp::eq:
            {
                pResult = GenericComparisonEqual(pITL, pITR);
                break;
            }
            case OpExp::ne:
            {
                pResult = GenericComparisonNonEqual(pITL, pITR);
                break;
            }
            case OpExp::lt:
            {
                pResult = GenericLess(pITL, pITR);
                break;
            }
            case OpExp::le:
            {
                pResult = GenericLessEqual(pITL, pITR);
                break;
            }
            case OpExp::gt:
            {
                pResult = GenericGreater(pITL, pITR);
                break;
            }
            case OpExp::ge:
            {
                pResult = GenericGreaterEqual(pITL, pITR);
                break;
            }
            case OpExp::power:
            {
                pResult = GenericPower(pITL, pITR);
                break;
            }
            case OpExp::krontimes:
            {
                pResult = GenericKrontimes(pITL, pITR);
                break;
            }
            case OpExp::kronrdivide:
            {
                pResult = GenericKronrdivide(pITL, pITR);
                break;
            }
            case OpExp::kronldivide:
            {
                pResult = GenericKronldivide(pITL, pITR);
                break;
            }
            default:
                break;
        }

        //overloading
        if (pResult == NULL)
        {
            // We did not have any algorithm matching, so we try to call OverLoad
            pResult = callOverloadOpExp(e.getOper(), pITL, pITR);
        }

        setResult(pResult);

        //clear left and/or right operands
        if (pResult != pITL)
        {
            pITL->killMe();
        }

        if (pResult != pITR)
        {
            pITR->killMe();
        }
    }
    catch (ast::InternalError& error)
    {
        setResult(NULL);
        if (pResult)
        {
            pResult->killMe();
        }
        if (pITL && (pITL != pResult))
        {
            pITL->killMe();
        }
        if (pITR && (pITR != pResult))
        {
            pITR->killMe();
        }

        error.SetErrorLocation(e.getLocation());
        CoverageInstance::stopChrono((void*)&e);
        throw error;
    }

    CoverageInstance::stopChrono((void*)&e);
    /*if (e.getDecorator().res.isConstant())
    {

    }*/
}

template<class T>
void RunVisitorT<T>::visitprivate(const LogicalOpExp &e)
{
    CoverageInstance::invokeAndStartChrono((void*)&e);
    types::InternalType *pITR = NULL; //assign only in non shortcut operations.
    types::InternalType *pITL = NULL;
    types::InternalType *pResult = NULL;

    try
    {
        /*getting what to assign*/
        e.getLeft().accept(*this);
        pITL = getResult();
        if (pITL == nullptr)
        {
            clearResult();
            char* strOp = wide_string_to_UTF8(e.getString().c_str());
            InternalError ie(42,  e.getLeft().getLocation(), strOp, 1);
            FREE(strOp);
            throw ie;
        }
        if (isSingleResult() == false)
        {
            throw ast::InternalError(5, e.getRight().getLocation());
        }

        setResult(NULL);

        if (pITL->getType() == types::InternalType::ScilabImplicitList)
        {
            types::ImplicitList* pIL = pITL->getAs<types::ImplicitList>();
            if (pIL->isComputable())
            {
                pITL = pIL->extractFullMatrix();
                pIL->killMe();
            }
        }

        // process left arg only (for shortcut ops)
        bool bIsShortCut = true;

        switch (e.getOper())
        {
            case LogicalOpExp::logicalShortCutAnd:
                pResult = GenericShortcutAnd(pITL);
                break;

            case LogicalOpExp::logicalShortCutOr:
                pResult = GenericShortcutOr(pITL);
                break;

            default:
                bIsShortCut = false;
                break;
        }

        // process both arguments
        if (pResult == NULL)
        {
            e.getRight().accept(*this);
            if (pITR)
            {
                pITR->killMe();
            }
            pITR = getResult();

            if (pITR == nullptr)
            {
                clearResult();
                char* strOp = wide_string_to_UTF8(e.getString().c_str());
                InternalError ie(42,  e.getLeft().getLocation(), strOp, 2);
                FREE(strOp);
                throw ie;
            }

            if (isSingleResult() == false)
            {
                throw ast::InternalError(5, e.getRight().getLocation());
            }

            if (pITR->getType() == types::InternalType::ScilabImplicitList)
            {
                types::ImplicitList* pIR = pITR->getAs<types::ImplicitList>();
                if (pIR->isComputable())
                {
                    pITR = pIR->extractFullMatrix();
                }
            }

            switch (e.getOper())
            {
                case LogicalOpExp::logicalShortCutAnd:
                case LogicalOpExp::logicalAnd:
                    pResult = GenericLogicalAnd(pITL, pITR);
                    break;

                case LogicalOpExp::logicalShortCutOr:
                case LogicalOpExp::logicalOr:
                    pResult = GenericLogicalOr(pITL, pITR);
                    break;

                default:
                    break;
            }

            if (pResult && bIsShortCut)
            {
                bool bIsShortCutAnd = e.getOper() == LogicalOpExp::logicalShortCutAnd;
                types::InternalType* pResult2 = bIsShortCutAnd ? GenericShortcutAnd(pResult) : GenericShortcutOr(pResult);

                if(pResult != pITL && pResult != pITR)
                {
                    pResult->killMe();
                }

                if (pResult2)
                {
                    pResult = pResult2;
                }
                else
                {
                    pResult = new types::Bool(bIsShortCutAnd);
                }
            }
        }

        //overloading
        if (pResult == NULL)
        {
            pResult = callOverloadOpExp(e.getOper(), pITL, pITR);
        }

        setResult(pResult);

        // protect pResult in case where pITL or pITR equal pResult
        pResult->IncreaseRef();

        //clear left and/or right operands
        pITL->killMe();
        if (pITR)
        {
            pITR->killMe();
        }

        // unprotect pResult
        pResult->DecreaseRef();
    }
    catch (ast::InternalError& error)
    {
        setResult(NULL);
        if (pResult)
        {
            pResult->killMe();
        }
        if (pITL && (pITL != pResult))
        {
            pITL->killMe();
        }
        if (pITR && (pITR != pResult))
        {
            pITR->killMe();
        }
        error.SetErrorLocation(e.getLocation());
        CoverageInstance::stopChrono((void*)&e);
        throw error;
    }

    CoverageInstance::stopChrono((void*)&e);
}

template<class T>
types::InternalType* RunVisitorT<T>::callOverloadOpExp(OpExp::Oper _oper, types::InternalType* _paramL, types::InternalType* _paramR)
{
    types::typed_list in;
    types::typed_list out;

    /*
    ** Special case for unary minus => will call %{type_s}
    */
    if (_oper == OpExp::unaryMinus || _oper == OpExp::unaryPlus)
    {
        _paramR->IncreaseRef();
        in.push_back(_paramR);
        try
        {
            types::Callable::ReturnValue ret = Overload::generateNameAndCall(Overload::getNameFromOper(_oper), in, 1, out, true);
            if(ret == types::Function::Error)
            {
                throw ast::InternalError(ConfigVariable::getLastErrorMessage());
            }
            if (!out.size())
            {
                throw ast::InternalError(23);
            }
        }
        catch (const ast::InternalError&)
        {
            _paramR->DecreaseRef();
            throw;
        }

        _paramR->DecreaseRef();
        return out[0];
    } 

    _paramL->IncreaseRef();
    _paramR->IncreaseRef();
    in.push_back(_paramL);
    in.push_back(_paramR);

    try
    {
        types::Callable::ReturnValue ret = Overload::generateNameAndCall(Overload::getNameFromOper(_oper), in, 1, out, true);
        if(ret == types::Function::Error)
        {
            throw ast::InternalError(ConfigVariable::getLastErrorMessage());
        }
        if (!out.size())
        {
            throw ast::InternalError(23);
        }
    }
    catch (const ast::InternalError&)
    {
        _paramL->DecreaseRef();
        _paramR->DecreaseRef();
        throw;
    }

    _paramL->DecreaseRef();
    _paramR->DecreaseRef();

    return out[0];
}

} /* namespace ast */
