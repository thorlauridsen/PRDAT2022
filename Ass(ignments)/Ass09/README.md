# Assignment 9

## Exercise 10.1

### (i)

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
