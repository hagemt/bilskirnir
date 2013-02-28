% Make a dynamic procedure called 'fib'
:- dynamic(fib/2).

% Base cases: f(0) = f(1) = 1 (cut for efficiency)
fib(0,1) :- !.
fib(1,1) :- !.

% Recursively: f(n) = f(n-1) + f(n-2) (memoize for efficiency)
fib(N,F) :-
	N1 is N - 1, fib(N1,F1), asserta(fib(N1,F1)),
	N2 is N - 2, fib(N2,F2), asserta(fib(N2,F2)),
	F is F1 + F2.
