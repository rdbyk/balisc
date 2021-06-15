// ============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2008 - INRIA - Sylvestre LEDRU <sylvestre.ledru@inria.fr>
// Copyright (C) 2021 - Dirk Reusch, Kybernetik Dr. Reusch
//
//  This file is distributed under the same license as the Scilab package.
// ============================================================================

// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->

if setlanguage("zh_TW")
    msg="%s: Type %s is not implemented.\n";
    if gettext(msg) <> "%s: 型態 %s 未實作.\n" then pause, end
    msg="%s: function not available in NWNI mode.\n";
    if gettext(msg) <> "%s: 此函數在 NWNI 模式中不存在.\n" then pause, end
end

if setlanguage("ru_RU")
    msg="%s: Type %s is not implemented.\n";
    if gettext(msg) <> "%s: Тип %s не реализован.\n" then pause, end
    msg="%s: function not available in NWNI mode.\n";
    if gettext(msg) <> "%s: функция недоступна в режиме NWNI.\n" then pause, end
end
