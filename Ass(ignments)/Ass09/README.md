# Assignment 9

## Exercise 10.1
To understand how the abstract machine and the garbage collector work and how they collaborate, answer these questions:

### (i)
Write 3-10 line descriptions of how the abstract machine executes each of the following instructions:

| Instruction | Description |
|-------------|-------------|
| ADD         | Retrieve the integer in the stack which is at `sp-1` and untag it such that it is the original integer. The same is done for the integer at `sp`. The two integers are then added and tagged again. The stack pointer is decremented. |
| CSTI i      | Takes the next instruction and tags it. Increments the stack pointer since you pushed the value onto the stack. |
| NIL         | Pushes 0 as an address onto the stack. This integer value is not tagged so it is an address. |
| IFZERO      | First take the value at `sp-1` then it will check if this is 0 or nill. This is done by either untagging the integer or just checking if its nil. If it is zero, it will set the program counter and goto the address given. Otherwise the program counter is incremented |
| CONS        | First allocate memory for the cons cell. Then it takes the two top words on the stack and put them into a cons cell. |
| CAR         | Takes the first element from the cons cell at `sp` |
| SETCAR      | Set first element of the cons cell |

### (ii)
Describe the result of applying each C macro Length, Color and Paint from Sect. 10.7.4 to a block header

ttttttttnnnnnnnnnnnnnnnnnnnnnngg,

that is, a 32-bit word, as described in the source code comments.

tttttttt is the block tagging
nnnnnnnnnnnnnnnnnnnnnn is the block length
gg is the garbage collection color

### (iii)
When does the abstract machine, or more precisely, its instruction interpretation loop, call the `allocate(...)` function? Is there any other interaction between the abstract machine (also called the mutator) and the garbage collector?

`allocate(...)` is only used in `CSTI i` which pushes the integer constant i
The other garbage collection methods aren't used in the instruction interpretation loop.

### (iv)
In what situation will the garbage collector’s `collect(...)` function be called?
When allocating memory, the `collect()` method will be called if there is no available memory.

## Exercise 10.2
Add a simple mark-sweep garbage collector to listmachine.c, like
this:
```
void collect(int s[], int sp) {
  markPhase(s, sp);
  sweepPhase();
}
```
Your `markPhase` function should scan the abstract machine stack `s[0..sp]` and
call an auxiliary function `mark(word* block)` on each non-nil heap reference
in the stack, to mark live blocks in the heap. Function `mark(word* block)`
should recursively mark everything reachable from the block.
The `sweepPhase` function should scan the entire heap, put white blocks on the
freelist, and paint black blocks white. It should ignore blue blocks; they are either
already on the freelist or they are orphan blocks which are neither used for data nor
on the freelist, because they consist only of a block header, so there is no way to
link them into the freelist.
This may sound complicated, but the complete solution takes less than 30 lines
of C code.
Running `listmachine ex30.out 1000` should now work, also for arguments that are much larger than 1000.
Remember that the listmachine has a tracing mode `listmachine -trace
ex30.out 4` so you can see the stack state just before your garbage collector
crashes.
Also, calling the `heapStatistics()` function in `listmachine.c` performs some checking of the heap’s consistency and reports some statistics on the
number of used and free blocks and so on. It may be informative to call it before
and after garbage collection, and between the mark and sweep phases.
When your garbage collector works, use it to run the list-C programs `ex35.lc`
and `ex36.lc` and check that they produce the expected output (described in their
source files). These programs build shared and cyclic data structures in the heap,
and this may reveal flaws in your garbage collector

## Exercise 10.3
Improve the sweep phase so that it joins adjacent dead blocks into a single dead block. More precisely, when sweep finds a white (dead) block of length n at address p, it checks whether there is also a white block at address p + 1 + n, and if so joins them into one block. Don’t forget to run the list-C programs ex35.lc and ex36.lc as in Exercise 10.2.

