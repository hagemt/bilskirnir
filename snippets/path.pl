edge(a,b,10).
edge(b,c,15).
edge(b,d,5).
edge(c,d,10).

can_move(X, Y, D) :-
        edge(X, Y, D) ; edge(Y, X, D).

path(X, X, [X], 0, _).

path(X, Y, [X|P], D, V) :-
	can_move(X, M, D0),
        nonmember(M, V),
	path(M, Y, P, D1, [X|V]),
	D is D0 + D1.

path(X, Y, P, L) :- path(X, Y, P, L, []).

nonmember(_, []).
nonmember(X, [H|T]) :- X \= H, nonmember(X, T).
