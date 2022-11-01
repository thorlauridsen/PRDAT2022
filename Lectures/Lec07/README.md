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

Unfinished
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
L1: 
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
L2  
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

## Exercise 8.3

### Description

Description

### Solution

Unfinished

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