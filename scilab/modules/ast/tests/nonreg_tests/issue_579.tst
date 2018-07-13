// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->
//
// <-- Non-regression test for issue 579 -->
//
// <-- Github URL -->
// https://github.com/rdbyk/balisc/issues/579
//
// <-- Short Description -->
// Ops on Polynomials with Different Variable Names

errmsg = ["Undefined operation for the given operands.";"check or define function %p_a_p for overloading."]
assert_checkerror("%s+%z", errmsg)

errmsg = ["Undefined operation for the given operands.";"check or define function %p_s_p for overloading."]
assert_checkerror("%s-%z", errmsg)

errmsg = ["Undefined operation for the given operands.";"check or define function %p_m_p for overloading."]
assert_checkerror("%s*%z", errmsg)

assert_checkequal(%s/%z, rlist(%s,%z))
assert_checkequal(%s\%z, rlist(%z,%s))

errmsg = ["Undefined operation for the given operands.";"check or define function %p_p_p for overloading."]
assert_checkerror("%s^%z", errmsg)

errmsg = ["Undefined operation for the given operands.";"check or define function %p_x_p for overloading."]
assert_checkerror("%s.*%z", errmsg)

assert_checkequal(%s./%z, rlist(%s,%z))
assert_checkequal(%s.\%z, rlist(%z,%s))

errmsg = ["Undefined operation for the given operands.";"check or define function %p_j_p for overloading."]
assert_checkerror("%s.^%z", errmsg)

assert_checkequal(%s==%z, %f)
assert_checkequal(%s<>%z, %t)

errmsg = ["Undefined operation for the given operands.";"check or define function %p_c_p for overloading."]
assert_checkerror("[%s,%z]", errmsg)

errmsg = ["Undefined operation for the given operands.";"check or define function %p_f_p for overloading."]
assert_checkerror("[%s;%z]", errmsg)
