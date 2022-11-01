# Assignment 7

## Exercise 8.1

### Description

Download microc.zip from the book homepage, unpack it to a folder MicroC, and build the micro-C compiler as explained in README.TXT step (B).

(i) As a warm-up, compile one of the micro-C examples provided, such as that in source file ex11.c, then run it using the abstract machine implemented in Java, as described also in step (B) of the README file. When run with command line argument 8, the program prints the 92 solutions to the eight queens problem: how to place eight queens on a chessboard so that none of them can attack any of the others.
(ii) Now compile the example micro-C programs ex3.c and ex5.c using functions compileToFile and fromFile from ParseAndComp.fs as above.

Study the generated symbolic bytecode. Write up the bytecode in a more structured way with labels only at the beginning of the line (as in this chapter). Write the corresponding micro-C code to the right of the stack machine code. Note that ex5.c has a nested scope (a block { ... } inside a function body); how is that visible in the generated code?

Execute the compiled programs using java Machine ex3.out 10 and similar. Note that these micro-C programs require a command line argument (an integer) when they are executed.

Trace the execution using java Machinetrace ex3.out 4, and explain the stack contents and what goes on in each step of execution, and especially how the low-level bytecode instructions map to the higher-level features of micro-C. You can capture the standard output from a command prompt (in a file ex3trace.txt) using the Unix-style notation:
`java Machinetrace ex3.out 4 > ex3trace.txt`

### Solution
#UNFINISHED
```
compileToFile (fromFile "ex3.c") "ex3.out";;
val it: Machine.instr list =
  [LDARGS; CALL (1, "L1"); STOP; Label "L1"; INCSP 1; GETBP; CSTI 1; ADD;
   CSTI 0; STI; INCSP -1; GOTO "L3"; Label "L2"; GETBP; CSTI 1; ADD; LDI;
   PRINTI; INCSP -1; GETBP; CSTI 1; ADD; GETBP; CSTI 1; ADD; LDI; CSTI 1; ADD;
   STI; INCSP -1; INCSP 0; Label "L3"; GETBP; CSTI 1; ADD; LDI; GETBP; CSTI 0;
   ADD; LDI; LT; IFNZRO "L2"; INCSP -1; RET 0]
```
```
Compile ex3:
    LDARGS
    CALL(1,"L1")
    STOP
L1:
    INCSP 1
    GETBP
    CSTI1
    ADD
    CASI0
    STI
    INCSP -1;
    GOTO "L3"
L2: 
    GETBP
    CSTI1
    ADD
    LDI
    PRINTI
    INCSP -1
    GETBP
    CSTI 1
    ADD
    GETBP
    CSTI 1
    ADD
    LDI 
    CSTI 1
    ADD
    STI
    INCSP -1
    INCSP 0
L3:
    GETBP
    CSTI 1
    ADD 
    LDI
    GETBP
    CSTI 0
    ADD
    LDI
    LT
    IFNZRO L2
    INCSP -1
    RET 0
```
```
> compileToFile (fromFile "ex5.c") "ex5.out";;
val it: Machine.instr list =
  [LDARGS; CALL (1, "L1"); STOP; Label "L1"; INCSP 1; GETBP; CSTI 1; ADD;
   GETBP; CSTI 0; ADD; LDI; STI; INCSP -1; INCSP 1; GETBP; CSTI 0; ADD; LDI;
   GETBP; CSTI 2; ADD; CALL (2, "L2"); INCSP -1; GETBP; CSTI 2; ADD; LDI;
   PRINTI; INCSP -1; INCSP -1; GETBP; CSTI 1; ADD; LDI; PRINTI; INCSP -1;
   INCSP -1; RET 0; Label "L2"; GETBP; CSTI 1; ADD; LDI; GETBP; CSTI 0; ADD;
   LDI; GETBP; CSTI 0; ADD; LDI; MUL; STI; INCSP -1; INCSP 0; RET 1]
```
```
Compile ex5:
    LDARGS
    CALL(1,"L1")
    STOP
L1: // main
    INCSP 1
    GETBP
    CSTI 1
    ADD
    GETBP
    CSTI 0
    ADD
    LDI
    STI
    INCSP -1
    INCSP 1
    GETBP
    CSTI 0
    ADD
    LDI
    GETBP
    CSTI 2
    ADD
    CALL (2, "L2")
    INCSP -1
    GETBP
    CSTI 2
    ADD
    LDI
    PRINTI
    INCSP -1
    INCSp -1
    RET 0
L2: // sqaure  
    GETBP
    CSTI1
    ADD
    LDI
    GETBP
    CSTI 0
    ADD
    LDI
    GETBP
    CSTI 0
    ADD
    LDI
    MUL
    STI
    INCSP -1
    INCSP 0
    RET 1]
```

Output of trace:
```
[ ]                  {0: LDARGS} // ARG given 4 and set in stack
[ 4 ]                {1: CALL 1 5}
[ 4 -999 4 ]         {5: INCSP 1}
[ 4 -999 4 0 ]       {7: GETBP}
[ 4 -999 4 0 2 ]     {8: CSTI 1}
[ 4 -999 4 0 2 1 ]   {10: ADD}
[ 4 -999 4 0 3 ]     {11: CSTI 0}
[ 4 -999 4 0 3 0 ]   {13: STI}
[ 4 -999 4 0 0 ]     {14: INCSP -1}
[ 4 -999 4 0 ]       {16: GOTO 43}
[ 4 -999 4 0 ]       {43: GETBP}
[ 4 -999 4 0 2 ]     {44: CSTI 1}
[ 4 -999 4 0 2 1 ]   {46: ADD}
[ 4 -999 4 0 3 ]     {47: LDI}
[ 4 -999 4 0 0 ]     {48: GETBP}
[ 4 -999 4 0 0 2 ]   {49: CSTI 0}
[ 4 -999 4 0 0 2 0 ] {51: ADD}
[ 4 -999 4 0 0 2 ]   {52: LDI}
[ 4 -999 4 0 0 4 ]   {53: LT}
[ 4 -999 4 0 1 ]     {54: IFNZRO 18}
[ 4 -999 4 0 ]       {18: GETBP}
[ 4 -999 4 0 2 ]     {19: CSTI 1}
[ 4 -999 4 0 2 1 ]   {21: ADD}
[ 4 -999 4 0 3 ]     {22: LDI}
[ 4 -999 4 0 0 ]     {23: PRINTI}
0 [ 4 -999 4 0 0 ]   {24: INCSP -1}
[ 4 -999 4 0 ]       {26: GETBP}
[ 4 -999 4 0 2 ]     {27: CSTI 1}
[ 4 -999 4 0 2 1 ]   {29: ADD}
[ 4 -999 4 0 3 ]     {30: GETBP}
[ 4 -999 4 0 3 2 ]   {31: CSTI 1}
[ 4 -999 4 0 3 2 1 ] {33: ADD}
[ 4 -999 4 0 3 3 ]   {34: LDI}
[ 4 -999 4 0 3 0 ]   {35: CSTI 1}
[ 4 -999 4 0 3 0 1 ] {37: ADD}
[ 4 -999 4 0 3 1 ]   {38: STI}
[ 4 -999 4 1 1 ]     {39: INCSP -1}
[ 4 -999 4 1 ]       {41: INCSP 0}
[ 4 -999 4 1 ]       {43: GETBP}
[ 4 -999 4 1 2 ]     {44: CSTI 1}
[ 4 -999 4 1 2 1 ]   {46: ADD}
[ 4 -999 4 1 3 ]     {47: LDI}
[ 4 -999 4 1 1 ]     {48: GETBP}
[ 4 -999 4 1 1 2 ]   {49: CSTI 0}
[ 4 -999 4 1 1 2 0 ] {51: ADD}
[ 4 -999 4 1 1 2 ]   {52: LDI}
[ 4 -999 4 1 1 4 ]   {53: LT}
[ 4 -999 4 1 1 ]     {54: IFNZRO 18}
[ 4 -999 4 1 ]       {18: GETBP}
[ 4 -999 4 1 2 ]     {19: CSTI 1}
[ 4 -999 4 1 2 1 ]   {21: ADD}
[ 4 -999 4 1 3 ]     {22: LDI}
[ 4 -999 4 1 1 ]     {23: PRINTI}
1 [ 4 -999 4 1 1 ]   {24: INCSP -1}
[ 4 -999 4 1 ]       {26: GETBP}
[ 4 -999 4 1 2 ]     {27: CSTI 1}
[ 4 -999 4 1 2 1 ]   {29: ADD}
[ 4 -999 4 1 3 ]     {30: GETBP}
[ 4 -999 4 1 3 2 ]   {31: CSTI 1}
[ 4 -999 4 1 3 2 1 ] {33: ADD}
[ 4 -999 4 1 3 3 ]   {34: LDI}
[ 4 -999 4 1 3 1 ]   {35: CSTI 1}
[ 4 -999 4 1 3 1 1 ] {37: ADD}
[ 4 -999 4 1 3 2 ]   {38: STI}
[ 4 -999 4 2 2 ]     {39: INCSP -1}
[ 4 -999 4 2 ]       {41: INCSP 0}
[ 4 -999 4 2 ]       {43: GETBP}
[ 4 -999 4 2 2 ]     {44: CSTI 1}
[ 4 -999 4 2 2 1 ]   {46: ADD}
[ 4 -999 4 2 3 ]     {47: LDI}
[ 4 -999 4 2 2 ]     {48: GETBP}
[ 4 -999 4 2 2 2 ]   {49: CSTI 0}
[ 4 -999 4 2 2 2 0 ] {51: ADD}
[ 4 -999 4 2 2 2 ]   {52: LDI}
[ 4 -999 4 2 2 4 ]   {53: LT}
[ 4 -999 4 2 1 ]     {54: IFNZRO 18}
[ 4 -999 4 2 ]       {18: GETBP}
[ 4 -999 4 2 2 ]     {19: CSTI 1}
[ 4 -999 4 2 2 1 ]   {21: ADD}
[ 4 -999 4 2 3 ]     {22: LDI}
[ 4 -999 4 2 2 ]     {23: PRINTI}
2 [ 4 -999 4 2 2 ]   {24: INCSP -1}
[ 4 -999 4 2 ]       {26: GETBP}
[ 4 -999 4 2 2 ]     {27: CSTI 1}
[ 4 -999 4 2 2 1 ]   {29: ADD}
[ 4 -999 4 2 3 ]     {30: GETBP}
[ 4 -999 4 2 3 2 ]   {31: CSTI 1}
[ 4 -999 4 2 3 2 1 ] {33: ADD}
[ 4 -999 4 2 3 3 ]   {34: LDI}
[ 4 -999 4 2 3 2 ]   {35: CSTI 1}
[ 4 -999 4 2 3 2 1 ] {37: ADD}
[ 4 -999 4 2 3 3 ]   {38: STI}
[ 4 -999 4 3 3 ]     {39: INCSP -1}
[ 4 -999 4 3 ]       {41: INCSP 0}
[ 4 -999 4 3 ]       {43: GETBP}
[ 4 -999 4 3 2 ]     {44: CSTI 1}
[ 4 -999 4 3 2 1 ]   {46: ADD}
[ 4 -999 4 3 3 ]     {47: LDI}
[ 4 -999 4 3 3 ]     {48: GETBP}
[ 4 -999 4 3 3 2 ]   {49: CSTI 0}
[ 4 -999 4 3 3 2 0 ] {51: ADD}
[ 4 -999 4 3 3 2 ]   {52: LDI}
[ 4 -999 4 3 3 4 ]   {53: LT}
[ 4 -999 4 3 1 ]     {54: IFNZRO 18}
[ 4 -999 4 3 ]       {18: GETBP}
[ 4 -999 4 3 2 ]     {19: CSTI 1}
[ 4 -999 4 3 2 1 ]   {21: ADD}
[ 4 -999 4 3 3 ]     {22: LDI}
[ 4 -999 4 3 3 ]     {23: PRINTI}
3 [ 4 -999 4 3 3 ]   {24: INCSP -1}
[ 4 -999 4 3 ]       {26: GETBP}
[ 4 -999 4 3 2 ]     {27: CSTI 1}
[ 4 -999 4 3 2 1 ]   {29: ADD}
[ 4 -999 4 3 3 ]     {30: GETBP}
[ 4 -999 4 3 3 2 ]   {31: CSTI 1}
[ 4 -999 4 3 3 2 1 ] {33: ADD}
[ 4 -999 4 3 3 3 ]   {34: LDI}
[ 4 -999 4 3 3 3 ]   {35: CSTI 1}
[ 4 -999 4 3 3 3 1 ] {37: ADD}
[ 4 -999 4 3 3 4 ]   {38: STI}
[ 4 -999 4 4 4 ]     {39: INCSP -1}
[ 4 -999 4 4 ]       {41: INCSP 0}
[ 4 -999 4 4 ]       {43: GETBP}
[ 4 -999 4 4 2 ]     {44: CSTI 1}
[ 4 -999 4 4 2 1 ]   {46: ADD}
[ 4 -999 4 4 3 ]     {47: LDI}
[ 4 -999 4 4 4 ]     {48: GETBP}
[ 4 -999 4 4 4 2 ]   {49: CSTI 0}
[ 4 -999 4 4 4 2 0 ] {51: ADD}
[ 4 -999 4 4 4 2 ]   {52: LDI}
[ 4 -999 4 4 4 4 ]   {53: LT}
[ 4 -999 4 4 0 ]     {54: IFNZRO 18}
[ 4 -999 4 4 ]       {56: INCSP -1}
[ 4 -999 4 ]         {58: RET 0}
[ 4 ]                {4: STOP}
```

## Exercise 8.3

### Description

Modify the compiler (function cExpr) to generate code for PreInc(acc) and PreDec(acc). To parse micro-C source programs containing these expressions, you also need to modify the lexer and parser.

### Solution

Added cases for PreInc and PreDec In Comp.fs
```
cExpr ...
| ...
| PreInc acc -> cAccess acc varEnv funEnv @ [DUP; LDI; CSTI 1; ADD; STI]
| PreDec acc -> cAccess acc varEnv funEnv @ [DUP; LDI; CSTI 1; SUB; STI]
```
To test it we created the following program
```
void main() {
    int num;
	num = 6;
	
	++num;
    print num;
	
	--num;
    print num;
}
```
which prints 7 6 which is the correct answer
![](https://github.com/REXKrash/PRDAT2022/blob/main/Lectures/Lec07/images/8.3.png?raw=true)

## Exercise 8.4

### Description

Description

### Solution

Unfinished

## Exercise 8.5

### Description

Description

### Solution

Unfinished

## Exercise 8.6

### Description

Description

### Solution

Unfinished