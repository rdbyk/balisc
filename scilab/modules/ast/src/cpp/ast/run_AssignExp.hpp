/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2008-2008 - DIGITEO - Antoine ELIAS
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

//file included in runvisitor.cpp
namespace ast {

template<class T>
void RunVisitorT<T>::visitprivate(const AssignExp  &e)
{
    CoverageInstance::invokeAndStartChrono((void*)&e);
    symbol::Context* ctx = symbol::Context::getInstance();
    /*Create local exec visitor*/
    try
    {
        SimpleVar * pVar = NULL;
        if (e.getLeftExp().isSimpleVar())
        {
            pVar = static_cast<SimpleVar*>(&e.getLeftExp());
        }

        /*get king of left hand*/
        if (pVar)
        {
            // x = ?
            /*getting what to assign*/
            types::InternalType *pIT = e.getRightVal();
            if (pIT == NULL)
            {
                setExpectedSize(1);
                e.getRightExp().accept(*this);

                pIT = getResult();
                //reset result
                setResult(NULL);
            }

            if (pIT->isImplicitList())
            {
                if (pIT->getAs<types::ImplicitList>()->isComputable())
                {
                    types::InternalType *pTemp = pIT->getAs<types::ImplicitList>()->extractFullMatrix();
                    pIT->killMe();
                    pIT = pTemp;
                }
            }

            if (pIT->isAssignable() == false)
            {
                pIT->killMe();
                setResult(NULL);
                CoverageInstance::stopChrono((void*)&e);
                return;
            }

            if (ctx->isprotected(pVar->getStack()) == false)
            {
                if (e.getRightExp().isReturnExp())
                {
                    // ReturnExp so, which puts the value in the
                    if (ctx->getScopeLevel() > SCOPE_CONSOLE)
                    {
                        // previous scope
                        if (ctx->putInPreviousScope(pVar->getStack(), pIT) == false)
                        {
                            goto PROTECTED;
                        }
                    }
                    else
                    {
                        // or console scope
                        ctx->put(pVar->getStack(), pIT);
                    }

                    ((AssignExp*)&e)->setReturn();
                }

                ctx->put(pVar->getStack(), pIT);
            }
            else
            {
PROTECTED:
                // ignore assignment to protected dash "–" variable
                if (pVar->getSymbol().getName() == L"–")
                {
                    CoverageInstance::stopChrono((void*)&e);
                    return;
                }
                throw ast::InternalError(4, e.getLeftExp().getLocation());
            }

            if (e.isVerbose() && ConfigVariable::isPrintOutput())
            {
                std::wstring wstrName = pVar->getSymbol().getName();
                
                std::wstring ostr;
                ostr.reserve(wstrName.size() + 7);
                ostr = L" ";
                ostr += wstrName;
                ostr += L"  = \n";
                if (ConfigVariable::isPrintCompact() == false)
                {
                    ostr += L"\n";
                }
                scilabWriteW(ostr.c_str());
                
                VariableToString(pIT, wstrName.c_str());
            }
            CoverageInstance::stopChrono((void*)&e);
            return;
        }

        if (e.getLeftExp().isCellCallExp())
        {
            // a{?} = ?
            CellCallExp *pCell = static_cast<CellCallExp*>(&e.getLeftExp());
            types::InternalType *pOut = NULL;

            if (pCell->getName().isSimpleVar())
            {
                ast::SimpleVar* var = pCell->getName().getAs<ast::SimpleVar>();
                types::InternalType* pIT = ctx->getCurrentLevel(var->getStack());

                if (pIT)
                {
                    if (pIT->isCell() == false)
                    {
                        CoverageInstance::stopChrono((void*)&e);
                        throw ast::InternalError(8, e.getLeftExp().getLocation());
                    }
                }
                else
                {
                    pIT = ctx->get(var->getSymbol());

                    if (pIT && pIT->isCallable())
                    {
                        CoverageInstance::stopChrono((void*)&e);
                        throw ast::InternalError(8, e.getLeftExp().getLocation());
                    }
                }
            }

            /*getting what to assign*/
            types::InternalType* pITR = e.getRightVal();
            if (pITR == NULL)
            {
                e.getRightExp().accept(*this);
                pITR = getResult();
                //reset result
                setResult(NULL);
            }

            if (pITR == NULL)
            {
                // if the right hand is NULL.
                throw ast::InternalError(13, e.getLeftExp().getLocation());
            }

            std::list<ExpHistory*> fields;
            if (getFieldsFromExp(pCell, fields) == false)
            {
                for (std::list<ExpHistory*>::const_iterator i = fields.begin(), end = fields.end(); i != end; ++i)
                {
                    delete *i;
                }

                throw ast::InternalError(12, e.getRightExp().getLocation());
            }

            try
            {
                pOut = evaluateFields(pCell, fields, pITR);
            }
            catch (const InternalError&)
            {
                // catch error when call overload
                for (std::list<ExpHistory*>::const_iterator i = fields.begin(), end = fields.end(); i != end; ++i)
                {
                    (*i)->setDeleteCurrent(true);
                    delete *i;
                }

                pITR->killMe();
                throw;
            }

            for (std::list<ExpHistory*>::const_iterator i = fields.begin(), end = fields.end(); i != end; ++i)
            {
                delete *i;
            }

            pITR->killMe();

            if (pOut == NULL)
            {
                throw ast::InternalError(10, e.getRightExp().getLocation());
            }

            if (pOut != NULL)
            {
                if (e.isVerbose() && ConfigVariable::isPrintOutput())
                {
                    std::wstring ostr;
                    ostr.reserve((*getStructNameFromExp(pCell)).size() + 7);
                    ostr = L" ";
                    ostr += *getStructNameFromExp(pCell);
                    ostr += L"  = \n";
                    if (ConfigVariable::isPrintCompact() == false)
                    {
                        ostr += L"\n";
                    }
                    scilabWriteW(ostr.c_str());

                    VariableToString(pOut, ostr.c_str());
                }
            }
            else
            {
                throw ast::InternalError(2, e.getRightExp().getLocation());
            }

            CoverageInstance::stopChrono((void*)&e);
            return;
        }

        if (e.getLeftExp().isCallExp())
        {
            CallExp *pCall = static_cast<CallExp*>(&e.getLeftExp());
            //x(?) = ?
            types::InternalType *pOut = NULL;

            if (e.getRightExp().isReturnExp())
            {
                // We can't put in the previous scope a variable create like that : a(2)=return(1)
                throw ast::InternalError(28, e.getLeftExp().getLocation());
            }

            /*getting what to assign*/
            types::InternalType* pITR = e.getRightVal();
            if (pITR == NULL)
            {
                e.getRightExp().accept(*this);
                pITR = getResult();
                //reset result
                setResult(NULL);
            }

            if (pITR == NULL)
            {
                // if the right hand is NULL.
                throw ast::InternalError(13, e.getLeftExp().getLocation());
            }

            bool alreadyProcessed = false;
            //a(...) without fields or whatever on arrayof derived types
            if (pCall->getName().isSimpleVar())
            {
                ast::SimpleVar* var = pCall->getName().getAs<ast::SimpleVar>();
                types::InternalType* pIT = ctx->getCurrentLevel(var->getStack());
                if (pIT && pIT->isArrayOf())
                {
                    if (ctx->isprotected(var->getStack()))
                    {
                        throw ast::InternalError(4, pCall->getLocation());
                    }

                    // prevent delete after extractFullMatrix
                    // called in insertionCall when pITR is an ImplicitList
                    pITR->IncreaseRef();

                    types::typed_list* currentArgs = GetArgumentList(pCall->getArgs());

                    try
                    {
                        pOut = insertionCall(e, currentArgs, pIT, pITR);
                    }
                    catch (const InternalError&)
                    {
                        pITR->DecreaseRef();
                        // call killMe on all arguments
                        cleanOut(*currentArgs);
                        delete currentArgs;
                        // insertion have done, call killMe on pITR
                        pITR->killMe();
                        throw;
                    }

                    pITR->DecreaseRef();

                    // call killMe on all arguments
                    cleanOut(*currentArgs);
                    delete currentArgs;

                    // insertion have done, call killMe on pITR
                    pITR->killMe();

                    if (pOut == NULL)
                    {
                        throw ast::InternalError(6, e.getLocation());
                    }


                    //update variable with new value
                    if (pOut != pIT)
                    {
                        ctx->put(var->getStack(), pOut);
                    }

                    alreadyProcessed = true;
                }
            }

            if (alreadyProcessed == false)
            {
                std::list<ExpHistory*> fields;
                if (getFieldsFromExp(pCall, fields) == false)
                {
                    for (std::list<ExpHistory*>::const_iterator i = fields.begin(), end = fields.end(); i != end; ++i)
                    {
                        delete *i;
                    }

                    throw ast::InternalError(31, e.getRightExp().getLocation());
                }

                // prevent delete after extractFullMatrix
                // called in evaluateFields when pITR is an ImplicitList
                pITR->IncreaseRef();

                try
                {
                    pOut = evaluateFields(pCall, fields, pITR);
                }
                catch (const InternalError&)
                {
                    // catch error when call overload
                    for (std::list<ExpHistory*>::const_iterator i = fields.begin(), end = fields.end(); i != end; ++i)
                    {
                        delete *i;
                    }

                    pITR->DecreaseRef();
                    pITR->killMe();

                    throw;
                }

                for (std::list<ExpHistory*>::const_iterator i = fields.begin(), end = fields.end(); i != end; ++i)
                {
                    delete *i;
                }

                pITR->DecreaseRef();
                pITR->killMe();

                if (pOut == NULL)
                {
                    throw ast::InternalError(10, e.getRightExp().getLocation());
                }
            }

            if (e.isVerbose() && ConfigVariable::isPrintOutput())
            {
                std::wstring ostrName(*getStructNameFromExp(&pCall->getName()));
                
                std::wstring ostr;
                ostr.reserve(ostrName.size() + 7);
                ostr = L" ";
                ostr += ostrName;
                ostr += L"  = \n";
                if (ConfigVariable::isPrintCompact() == false)
                {
                    ostr += L"\n";                
                }
                scilabWriteW(ostr.c_str());

                VariableToString(pOut, ostrName.c_str());
            }

            clearResult();
            CoverageInstance::stopChrono((void*)&e);

            return;
        }

        if (e.getLeftExp().isAssignListExp())
        {
            AssignListExp *pList = e.getLeftExp().getAs<AssignListExp>();
            //[x,y] = ?
            int iLhsCount = (int)pList->getExps().size();

            /*getting what to assign*/
            T exec;
            exec.setExpectedSize(iLhsCount);
            e.getRightExp().accept(exec);

            if (exec.getResultSize() < iLhsCount)
            {
                throw ast::InternalError(49, e.getRightExp().getLocation());
            }

            exps_t::const_iterator it;
            exps_t exps = pList->getExps();
            types::InternalType** pIT = new types::InternalType*[iLhsCount];
            int i = 0;
            for (i = iLhsCount - 1; i >= 0; i--)
            {
                //create a new AssignExp and run it
                pIT[i] = exec.getResult(i);
                //protet rhs against removal [a,b] = (b,a);
                pIT[i]->IncreaseRef();
            }

            for (i = 0, it = exps.begin(); it != exps.end(); ++it, ++i)
            {
                Exp* pExp = e.getRightExp().clone();
                AssignExp pAssign((*it)->getLocation(), *(*it), *pExp, pIT[i]);
                pAssign.setLrOwner(false);
                pAssign.setVerbose(e.isVerbose());
                pAssign.accept(*this);
                 //clear result to take care of [n,n]
                exec.setResult(i, NULL);
                delete pExp;
            }

            for (i = iLhsCount - 1; i >= 0; i--)
            {
                //unprotect rhs
                pIT[i]->DecreaseRef();
                pIT[i]->killMe();
            }

            delete[] pIT;
            exec.clearResult();
            CoverageInstance::stopChrono((void*)&e);
            return;
        }

        if (e.getLeftExp().isFieldExp())
        {
            FieldExp *pField = static_cast<FieldExp*>(&e.getLeftExp());
            types::InternalType *pIT = e.getRightVal();
            if (pIT == NULL)
            {
                //a.b = x
                //a.b can be a struct or a tlist/mlist or a handle
                /*getting what to assign*/
                setExpectedSize(1);
                e.getRightExp().accept(*this);
                pIT = getResult();
                setResult(NULL);
            }

            if (pIT->isImplicitList())
            {
                if (pIT->getAs<types::ImplicitList>()->isComputable())
                {
                    types::InternalType *pTemp = pIT->getAs<types::ImplicitList>()->extractFullMatrix();
                    delete pIT;
                    setResult(NULL);
                    pIT = pTemp;
                }
            }

            std::list<ExpHistory*> fields;
            if (getFieldsFromExp(pField, fields) == false)
            {
                for (std::list<ExpHistory*>::const_iterator i = fields.begin(), end = fields.end(); i != end; ++i)
                {
                    delete *i;
                }

                throw ast::InternalError(12, e.getRightExp().getLocation());
            }

            try
            {
                if (evaluateFields(pField, fields, pIT) == NULL)
                {
                    for (std::list<ExpHistory*>::const_iterator i = fields.begin(), end = fields.end(); i != end; ++i)
                    {
                        delete *i;
                    }

                    throw ast::InternalError(10, e.getRightExp().getLocation());
                }
            }
            catch (const InternalError&)
            {
                for (auto i : fields)
                {
                    delete i;
                }

                throw;
            }

            for (auto i : fields)
            {
                delete i;
            }

            if (e.isVerbose() && ConfigVariable::isPrintOutput())
            {
                const std::wstring *pstName = getStructNameFromExp(pField);

                types::InternalType* pPrint = ctx->get(symbol::Symbol(*pstName));
                
                std::wstring ostr;
                ostr.reserve((*pstName).size() + 7);
                ostr = L" ";
                ostr += *pstName;
                ostr += L"  = \n";
                if (ConfigVariable::isPrintCompact() == false)
                {
                    ostr += L"\n";                
                }
                scilabWriteW(ostr.c_str());

                VariableToString(pPrint, (*pstName).c_str());
            }

            clearResult();
            CoverageInstance::stopChrono((void*)&e);
            return;
        }

        throw ast::InternalError(30, e.getRightExp().getLocation());
    }
    catch (const InternalError&)
    {
        CoverageInstance::stopChrono((void*)&e);
        throw;
    }
}

} /* namespace ast */
