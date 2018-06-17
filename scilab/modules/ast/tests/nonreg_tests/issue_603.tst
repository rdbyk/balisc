// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->
//
// <-- Non-regression test for issue 603 -->
//
// <-- Github URL -->
// https://github.com/rdbyk/balisc/issues/603
//
// <-- Short Description -->
// Execution "(1:$):2" yields a Crash

errmsg = ["Undefined operation for the given operands.";"check or define function %ip_b_s for overloading."]
assert_checkerror("(1:$):1:1", errmsg)

errmsg = ["Undefined operation for the given operands.";"check or define function %s_b_ip for overloading."]
assert_checkerror("1:(1:$):1", errmsg)

errmsg = ["Undefined operation for the given operands.";"check or define function %ip_b_ip for overloading."]
assert_checkerror("(1:$):(1:$):1", errmsg)
