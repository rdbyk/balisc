function y = Variables()
    sin(a); // a is not in this scope
    x = 123; // x is unused
    y = 0;
    for i=1:10 // i is unused but usefull for the loop
        y = y + 1;
    end
    [l, r] = size(ones(1,2)); // l, r unused
    [l1, r1] = size(ones(3,4));
    sin(r1); // r1 is used so l1 too
endfunction
