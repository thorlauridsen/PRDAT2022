# Answers

## PLC 2.4 & 2.5

Our answers to these exercises can be viewed here: https://github.com/REXKrash/PRDAT2022/blob/main/Lectures/Lec02/ex2_4Handout.fs

## PLC 3.2

Our regular expression solution for a regular expression which recognizesallsequencesconsistingof _a_ and _b_ where two _a_’s are always separated by at least one _b_, is "`^(b|ab|a$)+$`".


### NFA 
<img src="https://github.com/REXKrash/PRDAT2022/blob/main/Lectures/Lec02/images/PLC3_2/SFA.jpg" width="50%">


### DFA

| DFA | Ved A | Ved B | NFA-tilstande |
| --- | ----- | ----- | ------------- |
| S0  | S2    | S1    | {1,2,4}       |
| S1  | S2    | S1    | {3}           |
| S2  | X     | S1    | {5}           |

<img src="https://github.com/REXKrash/PRDAT2022/blob/main/Lectures/Lec02/images/PLC3_2/DFA.jpg" width="50%">


## BCD 2.1

Note: We were confused about the phrasing of the question, and asked a TA. For example, we ewre cofused whether "All number-strings that have the value 42." meant any number that had "42" in it, such as 1230420123, or if it is any number that equals 42, such as 0000042. We were told the former was the correct understandig, and have done the excercises in such a mannner.

### a)
`([0-9]*42[0-9]*)+`

### b)
`(?!(([0-9]*42[0-9]*)+))[0-9]+(?<!((42)))`

### c)
`0*([1-9][0-9]{2,}|4[3-9]|[5-9][0-9])`

## BCD 2.2

### a)
To make a NFA, we have divided the regular expression into 3 parts (a*, a|b and aa): 
<img src="https://github.com/REXKrash/PRDAT2022/blob/main/Lectures/Lec02/images/BCD2_2/NFAv0.png" width="50%">

We then make seperate NFAs for each part:
#### NFA for _a*_
<img src="https://github.com/REXKrash/PRDAT2022/blob/main/Lectures/Lec02/images/BCD2_2/NFAv01.png" width="50%">

#### NFA for _a|b_
<img src="https://github.com/REXKrash/PRDAT2022/blob/main/Lectures/Lec02/images/BCD2_2/NFAv02.png" width="50%">

#### NFA for _aa_
<img src="https://github.com/REXKrash/PRDAT2022/blob/main/Lectures/Lec02/images/BCD2_2/NFAv03.png" width="50%">

Lastly, we will unify each seperate NFA into 1 final NFA:
<img src="https://github.com/REXKrash/PRDAT2022/blob/main/Lectures/Lec02/images/BCD2_2/NFAv1.png" width="75%">

### b)
Through building this DFA, we have made the followig matrix:

This translates into the followig DFA:

<img src="https://github.com/REXKrash/PRDAT2022/blob/main/Lectures/Lec02/images/BCD2_2/DFA.png" width="50%">
