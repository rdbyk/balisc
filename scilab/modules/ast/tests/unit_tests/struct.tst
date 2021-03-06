// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2011 - DIGITEO - Antoine ELIAS
// Copyright (C) 2012 - 2016 - Scilab Enterprises
// Copyright (C) 2019 - Dirk Reusch, Kybernetik Dr. Reusch
//
// This file is hereby licensed under the terms of the GNU GPL v2.0,
// pursuant to article 5.3.4 of the CeCILL v.2.1.
// This file was originally licensed under the terms of the CeCILL v2.1,
// and continues to be available under such terms.
// For more information, see the COPYING file which you should have received
// along with this program.

// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->

//function struct

firstname       = "firstname";
firstname_new   = "firstname_new";
lastname        = "lastname";
lastname_new    = "lastname_new";
email           = "email";
email_new       = "email_new";
phone_new       = "phone_new";

// create a one dimensional struct
st = struct("firstname", firstname, "lastname", lastname, "email", email);

assert_checkequal(st.firstname, firstname);
assert_checkequal(st.lastname, lastname);
assert_checkequal(st.email, email);

//change some values
st.firstname    = firstname_new;
st.lastname     = lastname_new;
st.email        = email_new;

// add a phone field
st.phone        = phone_new;

assert_checkequal(st.firstname, firstname_new);
assert_checkequal(st.lastname, lastname_new);
assert_checkequal(st.email, email_new);
assert_checkequal(st.phone, phone_new);
clear st;

//creating one dimensional structure by insertion
firstname   = "firstname";
lastname    = "lastname";
email       = "email";

st.firstname    = firstname;
st.lastname     = lastname;
st.email        = email;

assert_checkequal(st.firstname, firstname);
assert_checkequal(st.lastname, lastname);
assert_checkequal(st.email, email);
clear st;

//create multi dimentional struct by insertion
n1 = 4;
n2 = 3;
n3 = 2;

firstnames(n1,n2,n3)    = "";
lastnames(n1,n2,n3)     = "";
emails(n1,n2,n3)        = "";


for i = 1:(n1*n2*n3)
    sz              = string(i);
    firstnames(i)   = "firstname_" + sz;
    lastnames(i)    = "lastname_" + sz;
    emails(i)       = "email_" + sz;
end

//set dimension to 4x3x2
st(4,3,2).firstname = firstnames($);
st(4,3,2).lastname = lastnames($);

//fill struct as vector
for i = 1:(n1*n2*n3)
    st(i).firstname = firstnames(i);
    st(i).lastname  = lastnames(i);
    st(i).email     = emails(i);
end

//check data on each dimension
for i = 1:n1
    for j = i:n2
        for k = 1:n3
            assert_checkequal(st(i,j,k).firstname, firstnames(i,j,k));
            assert_checkequal(st(i,j,k).lastname, lastnames(i,j,k));
            assert_checkequal(st(i,j,k).email, emails(i,j,k));
        end
    end
end
clear firstnames
clear lastnames
clear emails
clear st;

//fields of an empty struct
fields = getfield(1,struct());
assert_checkequal(fields(1), "st");
assert_checkequal(fields(2), "dims");

// struct concatenation
clear st;
st.a = [];
st.a = [st.a;struct("field1", 1, "field2", 2)];
st.a = [st.a;struct("field1", 1, "field2", 2)];
st.a(1).field1 = 12;
st.a(1).field2 = 42;
assert_checkequal(st.a(1).field1, 12);
assert_checkequal(st.a(1).field2, 42);
