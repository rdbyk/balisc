function deff(head, body)

    if nargin <> 2  then
        error(999, msprintf(_("%s: Wrong number of input arguments: %d expected.\n"), "deff", 2));
    end

    execstr(["function " + head; body(:); "endfunction"]);

    funcs = funclist();

    if size(funcs, "*") == 1 then
        execstr(funcs + "=return(" + funcs + ")");
    end

endfunction
