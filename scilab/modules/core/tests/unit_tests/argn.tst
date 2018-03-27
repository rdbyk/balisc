//<-- CLI SHELL MODE -->
// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2008 - INRIA
// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================

// <-- ENGLISH IMPOSED -->

// nargin, nargout

funcprot(0);

function [x,y]=foo(a,b)
    x=[nargout,nargin];
    y=-1;
endfunction

if or(foo(1)<>[1 1]) then pause,end
if or(foo(1,2)<>[1 2]) then pause,end
if or(foo()<>[1 0]) then pause,end
[x,y]=foo(1);if or(x<>[2 1]) then pause,end
[x,y]=foo(1,1);if or(x<>[2 2]) then pause,end
[x,y]=foo();if or(x<>[2 0]) then pause,end

function [x,y]=foo(a,b)
    x=nargout;
    y=-1;
endfunction

if foo(1)<>1 then pause,end
if foo(1,2)<>1 then pause,end
[x,y]=foo(1);if x<>2 then pause,end
//

function [x,y]=foo(a,b)
    x=[nargout,nargin];
    y=-1;
endfunction

if or(foo(1)<>[1 1]) then pause,end
if or(foo(1,2)<>[1 2]) then pause,end
if or(foo()<>[1 0]) then pause,end
[x,y]=foo(1);if or(x<>[2 1]) then pause,end
[x,y]=foo(1,1);if or(x<>[2 2]) then pause,end
[x,y]=foo();if or(x<>[2 0]) then pause,end

function [x,y]=foo(a,b)
    x=nargout;
    y=-1;
endfunction

if foo(1)<>1 then pause,end
if foo(1,2)<>1 then pause,end
[x,y]=foo(1);if x<>2 then pause,end
