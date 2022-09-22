(* File Fun/ParseAndRun.fs *)

module ParseAndRun

let fromString = Parse.fromString;;

let eval = Fun.eval;;

let run e = eval e [];;

let e1 = run (fromString "5+7");;
let e2 = run (fromString "let y = 7 in y + 2 end");;
let e3 = run (fromString "let f x = x + 7 in f 2 end");;

let ex1 = run (fromString "5+7");;
let ex2 = run (fromString "let y = 7 in y + 2 end");;
let ex3 = run (fromString "let f x = x + 7 in f 2 end");;


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
