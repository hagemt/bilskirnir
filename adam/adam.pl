% For the case of (* op *)
make(A, B, S, add) :- S is A + B.
make(A, B, S, sub) :- S is A - B.
make(A, B, S, bus) :- S is B - A.
make(A, B, S, mul) :- S is A * B.
make(A, B, S, div) :- \+ B is 0.0, S is A / B.
make(A, B, S, vid) :- \+ A is 0.0, S is B / A.

% For the case of ((* op *) op *)
make(A, B, C, S, OP1, OP2) :- make(A, B, I, OP1), make(C, I, S, OP2).
make(A, B, C, S, OP1, OP2) :- make(A, C, I, OP1), make(B, I, S, OP2).
make(A, B, C, S, OP1, OP2) :- make(B, C, I, OP1), make(A, I, S, OP2).

% For the case of (((* op *) op *) op *)
make(A, B, C, D, S, OP1, OP2, OP3) :- make(B, C, D, I, OP1, OP2), make(A, I, S, OP3).
make(A, B, C, D, S, OP1, OP2, OP3) :- make(A, C, D, I, OP1, OP2), make(B, I, S, OP3).
make(A, B, C, D, S, OP1, OP2, OP3) :- make(A, B, D, I, OP1, OP2), make(C, I, S, OP3).
make(A, B, C, D, S, OP1, OP2, OP3) :- make(A, B, C, I, OP1, OP2), make(D, I, S, OP3).

% For the case of ((* op *) op (* op *))
make(A, B, C, D, S, OP1, OP2, OP3) :- make(A, B, I, OP1), make(C, D, J, OP2), make(I, J, S, OP3).
make(A, B, C, D, S, OP1, OP2, OP3) :- make(A, C, I, OP1), make(B, D, J, OP2), make(I, J, S, OP3).
make(A, B, C, D, S, OP1, OP2, OP3) :- make(A, D, I, OP1), make(B, C, J, OP2), make(I, J, S, OP3).

%directive :- initialization(make(1.0,3.0,4.0,6.0,24.0,A,B,C)).
