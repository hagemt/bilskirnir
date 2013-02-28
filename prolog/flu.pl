:- dynamic(infected/1).

% Ashley has been infected.
infected(ashley).

% When infected, students give the Flu to every student they converse with.

infected(Y) :- converses(X,Y), infected(X), asserta(infected(Y)).

% Ashley converses with John and Nate.
converses(ashley,john).
converses(ashley,nate).

% Nate converses with Sam and Matt and Adam.
converses(nate,sam).
converses(nate,matt).
converses(nate,adam).

% Adam converses with Nate and Wayne.
converses(adam,nate).
converses(adam,wayne).

% Wayne converses with Charles and George.
converses(wayne,charles).
converses(wayne,george).

% Charles converses with Sam.
converses(charles,sam).

% George converses with Adam and Sam and Matt.
converses(george,adam).
converses(george,sam).
converses(george,matt).

% Eric converses with Charles.
converses(eric,charles).
