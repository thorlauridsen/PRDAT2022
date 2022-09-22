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