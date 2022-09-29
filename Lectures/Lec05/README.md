# Assignment 5

## Exercise 5.1
## Exercise 5.7
## Exercise 6.1
```
let add x = let f y = x+y in f end
  in let addtwo = add 2
    in let x = 77 in addtwo 5 end
  end
end
```
Yes it is expeected
x is already defined in `addtwo = add 2`
So `let x = 77` has no effect

```
let add x = let f y = x+y in f end
in add 2 end
```
Since we only give the function one actual argument but expects 2, it returns a function.

## Exercise 6.2
## Exercise 6.3
## Exercise 6.4
## Exercise 6.5
