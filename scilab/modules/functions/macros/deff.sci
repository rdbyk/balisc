function deff(head, body)

    if nargin <> 2  then
        error(71, 2);
    end

    execstr(["function " + head; body(:); "endfunction"]);

    funcs = funclist();

    if size(funcs, "*") == 1 then
        execstr(funcs + "=return(" + funcs + ")");
    end

endfunction
