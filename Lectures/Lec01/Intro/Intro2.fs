(* Programming language concepts for software developers, 2010-08-28 *)

(* Evaluating simple expressions with variables *)

module Intro2

(* Association lists map object language variables to their values *)

let env = [("a", 3); ("c", 78); ("baf", 666); ("b", 111)];;

let emptyenv = []; (* the empty environment *)

let rec lookup env x =
    match env with 
    | []        -> failwith (x + " not found")
    | (y, v)::r -> if x=y then v else lookup r x;;

let cvalue = lookup env "c";;


(* Object language expressions with variables *)

type expr = 
  | CstI of int
  | Var of string
  | Prim of string * expr * expr
  | If of expr * expr * expr;;

let e1 = CstI 17;;

let e2 = Prim("+", CstI 3, Var "a");;

let e3 = Prim("+", Prim("*", Var "b", CstI 9), Var "a");;


(* Evaluation within an environment *)
(* 1.1.1 *)
let rec eval e (env : (string * int) list) : int =
    match e with
    | CstI i            -> i
    | Var x             -> lookup env x 
    | Prim("+", e1, e2) -> eval e1 env + eval e2 env
    | Prim("*", e1, e2) -> eval e1 env * eval e2 env
    | Prim("-", e1, e2) -> eval e1 env - eval e2 env
    | Prim("max", e1, e2) ->
        let left = eval e1 env
        let right = eval e2 env
        if left > right then left else right

    | Prim("min", e1, e2) ->
        let left = eval e1 env
        let right = eval e2 env
        if left < right then left else right

    | Prim("==", e1, e2) ->
        let left = eval e1 env
        let right = eval e2 env
        if left = right then 1 else 0

    | Prim _            -> failwith "unknown primitive";;

let e1v  = eval e1 env;;
let e2v1 = eval e2 env;;
let e2v2 = eval e2 [("a", 314)];;
let e3v  = eval e3 env;;

(* 1.1.2 *)
let example0 = eval (Prim("max", (CstI 7), (Prim("*", (CstI 2), (CstI 7))))) env;;
printfn "eval (Prim(\"max\", (CstI 7), (Prim(\"*\", (CstI 2), (CstI 7))))) = %A" (example0)
let example1 = eval (Prim("max", CstI 5, CstI 10)) env // Returns 10
printfn "eval (Prim(\"max\", CstI 5, CstI 10))  = %A" (example1)
let example2 = eval (Prim("min", CstI 5, CstI 10)) env //Returns 5
printfn "eval (Prim(\"min\", CstI 5, CstI 10)) = %A" (example2)
let example3 = eval (Prim("==", CstI 5, CstI 10)) env //Returns 0
printfn "eval (Prim(\"==\", CstI 5, CstI 10)) = %A" (example3)
let example4 = eval (Prim("==", CstI 10, CstI 10)) env //Returns 1
printfn "eval (Prim(\"==\", CstI 10, CstI 10)) = %A" (example4)

(* 1.1.3, 1.1.4, 1.1.5 *)
let rec eval2 e (env : (string * int) list) : int =
    match e with
    | CstI i            -> i
    | Var x             -> lookup env x 
    | Prim(ops, e1,e2) ->
        let i1 = eval2 e1 env
        let i2 = eval2 e2 env
        match ops with
        | "+" -> i1 + i2
        | "*" -> i1 * i2
        | "-" -> i1 - i2
        | "max" ->  if i1 > i2 then i1 else i2
        | "min" ->  if i1 < i2 then i1 else i2
        | "==" ->  if i1 = i2 then 1 else 0
        | _ -> failwith "unknown primitive"
    | If (e1, e2, e3) -> if eval2 e1 env <> 0 then eval2 e2 env else eval2 e3 env

(* 1.2.1 *)
type aexpr =
  | CstI of int
  | Var of string
  | Add of aexpr * aexpr
  | Mul of aexpr * aexpr
  | Sub of aexpr * aexpr

(* 1.2.2 *)
(* v−(w+z) *)
let aex1 = Sub(Var "v", Add (Var "w", Var "z"))

(* 2*(v−(w+z)) *)
let aex2 = Mul(CstI 2, Sub(Var "v", Add (Var "w", Var "z")))

(* x + y + z + v *)
let aex3 = Add(Var "x", Add (Var "y", Add (Var "z", Var "v")))

(* 1.2.3 *)
let rec fmt =
    function
    | CstI i -> string i
    | Var s -> s
    | Add (a1, a2) ->
        "(" + fmt a1 + " + " + fmt a2 + ")"
    | Mul (a1, a2) ->
        "(" + fmt a1 + " * " + fmt a2 + ")"
    | Sub (a1, a2) ->
        "(" + fmt a1 + " - " + fmt a2 + ")"

printfn "(x - 34) = %A" (fmt (Sub(Var "x", CstI 34)))
printfn "%A = %A" aex1 (fmt aex1)
printfn "%A = %A" aex2 (fmt aex2)
printfn "%A = %A" aex3 (fmt aex3)

(* 1.2.4 *)
let rec simplify (ae: aexpr) : aexpr =
    match ae with
    | CstI i    -> ae
    | Var x     -> ae
    | Add(ae1, ae2) -> 
        match ae1, ae2 with
        | CstI 0, _ -> simplify ae2
        | _, CstI 0 -> simplify ae1
        | CstI _, CstI _ | CstI _, Var _ | Var _, CstI _ | Var _, Var _
                    -> Add(ae1, ae2)
        | _, _      -> simplify (Add(simplify ae1, simplify ae2))

    | Sub(ae1, ae2) -> 
        match ae1, ae2 with 
        | _, CstI i when i = 0  -> simplify ae1
        | _, _ when ae1 = ae2   -> CstI 0
        | CstI _, CstI _ | CstI _, Var _ | Var _, CstI _ | Var _, Var _
                                -> Sub(ae1, ae2)
        | _, _                  -> simplify (Sub(simplify ae1, simplify ae2))

    | Mul(ae1, ae2) -> 
        match ae1, ae2 with
        | CstI i, _ when i = 1  -> simplify ae2
        | CstI i, _ when i = 0  -> CstI 0
        | _, CstI i when i = 1  -> simplify ae1
        | _, CstI i when i = 0  -> CstI 0
        | CstI _, CstI _ | CstI _, Var _ | Var _, CstI _ | Var _, Var _
                                -> Mul(ae1, ae2)
        | _, _                  -> simplify (Mul(simplify ae1, simplify ae2))


printfn "\nExercise 1.2.4"
let se1 = Add(Var "e", Add(Var "e", CstI 0))
printfn "%A = %A" se1 (fmt (simplify se1))

let se2 = Add(Var "e", Mul(Var "e", CstI 0))
printfn "%A = %A" se2 (fmt (simplify se2))

let se3 = Add(Var "e", Mul(Mul(Var "e", CstI 1), Sub(Var "a", Var "a")))
printfn "%A = %A" se3 (fmt (simplify se3))

(* 1.2.5 *)
let rec aeval (ae : aexpr) (env : (string * int) list) : int = 
    match ae with
    | CstI i -> i
    | Var x -> lookup env x 
    | Add(ae1, ae2) -> (aeval ae1 env) + (aeval ae2 env)
    | Sub(ae1, ae2) -> (aeval ae1 env) - (aeval ae2 env)
    | Mul(ae1, ae2) -> (aeval ae1 env) * (aeval ae2 env)


printfn "\nExercise 1.2.5"
let ae2 = Add(Var "a", Add(Var "a", CstI 5))
printfn "%A = %A" ae2 (aeval ae2 env)