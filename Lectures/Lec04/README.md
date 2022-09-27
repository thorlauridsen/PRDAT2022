# Assignment 4

## Exercise 4.1

![](https://github.com/REXKrash/PRDAT2022/blob/main/Lectures/Lec04/Images/Exercise4.1a.png?raw=true)
![](https://github.com/REXKrash/PRDAT2022/blob/main/Lectures/Lec04/Images/Exercise4.1b.png?raw=true)
![](https://github.com/REXKrash/PRDAT2022/blob/main/Lectures/Lec04/Images/Exercise4.1c.png?raw=true)

## Exercise 4.2

Code can be seen in ParseAndRun.fs
```fsharp
run (fromString "let sum n = if n < 0 then n + sum(n-1) else 0 in sum 1000 end");;
run (fromString "let sum n = if n = 0 then 0 else n + sum(n-1) in sum 1000 end");;
run (fromString "let pow n = 
                        if n = 0 then 
                            1 
                        else 3 * pow(n-1) 
                    in pow 8 end");;

run (fromString "let pow n = 
                    if n = 0 then 
                        1 
                    else 
                        3 * pow(n-1) 
                    in let compu m = 
                        if m = 0 then 
                            1 
                        else 
                            compu(m-1) + pow m 
                        in compu 11 end end");;

run (fromString "let pow8 n = 
                    n * n * n * n * n * n * n * n 
                in let compu m =
                    if m = 0 then
                        0
                    else
                        compu(m-1) + pow8 m
                     in compu 10 end end");;
```

## Exercise 4.3

Code can be seen in fun.fs
```fsharp
type value = 
  | Int of int
  | Closure of string * (string list) * expr * value env       (* (f, x, fBody, fDeclEnv) *)

let rec eval (e : expr) (env : value env) : int =
    match e with 
    | CstI i -> i
    | CstB b -> if b then 1 else 0
    | Var x  ->
      match lookup env x with
      | Int i -> i 
      | _     -> failwith "eval Var"
    | Prim(ope, e1, e2) -> 
      let i1 = eval e1 env
      let i2 = eval e2 env
      match ope with
      | "*" -> i1 * i2
      | "+" -> i1 + i2
      | "-" -> i1 - i2
      | "=" -> if i1 = i2 then 1 else 0
      | "<" -> if i1 < i2 then 1 else 0
      | _   -> failwith ("unknown primitive " + ope)
    | Let(x, eRhs, letBody) -> 
      let xVal = Int(eval eRhs env)
      let bodyEnv = (x, xVal) :: env
      eval letBody bodyEnv
    | If(e1, e2, e3) -> 
      let b = eval e1 env
      if b<>0 then eval e2 env
      else eval e3 env
    | Letfun(f, pArgs, fBody, letBody) -> 
      let bodyEnv = (f, Closure(f, pArgs, fBody, env)) :: env 
      eval letBody bodyEnv
    | Call(Var f, eArgs) -> //"f [7]"
      let fClosure = lookup env f
      match fClosure with
      | Closure (f, pArgs, fBody, fDeclEnv) -> //f x body env
        let pVals = List.fold (fun acc arg -> acc @ [Int(eval arg env)]) [] eArgs  //"[7,8]" -> FAIL
        let fBodyEnv = (List.zip pArgs pVals) @ (f, fClosure) :: fDeclEnv //x = [x,y] zip [x,y] FAIL
        eval fBody fBodyEnv
      | _ -> failwith "eval Call: not a function"
    | Call _ -> failwith "eval Call: not first-order function"

```

## Exercise 4.4

![](https://github.com/REXKrash/PRDAT2022/blob/main/Lectures/Lec04/Images/Exercise4.4.png?raw=true)
![](https://github.com/REXKrash/PRDAT2022/blob/main/Lectures/Lec04/Images/Exercise4.4b.png?raw=true)

## Exercise 4.5

![](https://github.com/REXKrash/PRDAT2022/blob/main/Lectures/Lec04/Images/Exercise4.5.png?raw=true)
![](https://github.com/REXKrash/PRDAT2022/blob/main/Lectures/Lec04/Images/Exercise4.5b.png?raw=true)
