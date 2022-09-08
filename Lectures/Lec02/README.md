# Answers

## PLC 2.4 & 2.5

Our answers to these exercises can be viewed here: https://github.com/REXKrash/PRDAT2022/blob/main/Lectures/Lec02/ex2_4Handout.fs

## PLC 3.2

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


## BCD 2.1

Note: We were confused about the phrasing of the question, and asked a TA. For example, we ewre cofused whether "All number-strings that have the value 42." meant any number that had "42" in it, such as 1230420123, or if it is any number that equals 42, such as 0000042. We were told the former was the correct understandig, and have done the excercises in such a mannner.

### a)
`([0-9]*42[0-9]*)+`

### b)
`(?!(([0-9]*42[0-9]*)+))[0-9]+(?<!((42)))`

