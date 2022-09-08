# Answers

## 2.4 & 2.5

These can be viewed in https://github.com/REXKrash/PRDAT2022/blob/main/Lectures/Lec02/ex2_4Handout.fs

## 3.2

Our regular expression solution for a regular expression which recognizesallsequencesconsistingof _a_ and _b_ where two _a_’s are always separated by at least one _b_, is "`^(b|ab|a$)+$`".


### NFA 
<img src="https://github.com/REXKrash/PRDAT2022/blob/main/Lectures/Lec02/images/SFA.jpg" width="50%">


### DFA

| DFA | Ved A | Ved B | NFA-tilstande |
| --- | ----- | ----- | ------------- |
| S0  | S2    | S1    | {1,2,4}       |
| S1  | S2    | S1    | {3}           |
| S2  | X     | S1    | {5}           |

<img src="https://github.com/REXKrash/PRDAT2022/blob/main/Lectures/Lec02/images/DFA.jpg" width="50%">
