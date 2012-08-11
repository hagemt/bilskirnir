class(   1, "CSCI", "Computer Science I")
class(   4, "CSCI", "Data Structures")
class(   7, "CSCI", "Introduction to Algorithms")
class(   8, "CSCI", "Computer Organization")
class(  10, "CSCI", "Models of Computation")
class(  11, "CSCI", "Programming Languages")
class(  12, "CSCI", "Operating Systems")
class(  13, "CSCI", "Software Design and Documentation")

class(   2, "MATH", "Calculus I")
class(   5, "MATH", "Calculus II")
class(   6, "MATH", "Introduction to Discrete Structures")

class(   3, "PHYS", "Physics I")

class(   9, "BIOL", "Introduction to Biology")

%MATH -- MATH 2xxx+ (no P/NC, no ISR)
%SCOP -- 4-Credit ASTR, BIOL, CHEM, EENV, or PHYS (no P/NC, no ERTH 1030)
%CSOP x3 3/4-Credit CSCI {4xxx,6xxx} ECSE {46xx,47xx,4490} (no 4630, 4640, 4720) (no P/NC, no ISR)
%HASS x6 ????
%FREE x8 XXXX xxxx
%cross_listed/2
%is_HASS/1
%is_writing_intensive/1
%class(UUID, Dept, Name).
%student(RIN, Name).
%has_met(RIN, UUID).

fills_core_CS_requirements(_, []).
fills_core_CS_requirements(RIN, [ReqHead|ReqTail]) :-
  has_met(RIN, ReqHead),
  fills_requirements(RIN, ReqTail).

fills_CS_requirements(RIN, Reqs) :-
  fills_core_CS_requirements(RIN, Reqs),
  has_CS_options(RIN, 3),
  has_HASS_credits(RIN, 24),
  has_HASS_depth(RIN),
  has_HASS_breadth(RIN),
  has_writing_intensive(RIN).

