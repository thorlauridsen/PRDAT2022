
module Exercises
;;
//11.1
let rec len xs =
    match xs with
    | []    -> 0
    | x::xr -> 1 + len xr
;;

//With continuation
let rec lenc xs cont =
    match xs with
    | []    -> cont 0
    | x::xr -> lenc xr (fun valu -> cont (valu + 1))
;;

len [2; 5; 7]
;;
lenc [2; 5; 7] id
;;
lenc [2; 5; 7] (printf "The answer is %d \n")
;;

//11.1.ii

let rec lenc2 xs cont =
    match xs with
    | []    -> cont 1
    | x::xr -> lenc2 xr (fun valu -> cont (valu * 2))
;;
//What happens if you call it as lenc xs (fun v -> 2*v) instead?
lenc [2; 5; 7] (fun v -> 2*v)
;;
lenc2 [2; 5; 7] id
;;

//11.1.iii (With accumulator)
let rec leni xs acc =
    match xs with
    | []    -> acc
    | x::xr -> leni xr (acc + 1)
;;

leni [2; 5; 7] 0
;;
//What is the relation between lenc and leni?



// 11.2
// 11.2.i
let rec rev xs = 
    match xs with 
	| []	->	[]
	| x::xr	->	rev xr @ [x]
;;

rev [1;2;3]
;;

//With continuation
let rec revc xs cont =
    match xs with
    | []    -> cont []
    | x::xr -> revc xr (fun valu -> cont (valu @ [x]))
;;

revc [1;2;3] id
;;

//11.2.ii
let rec revc2 xs cont =
    match xs with
    | []    -> cont []
    | x::xr -> revc2 xr (fun v -> cont(v @ v))

revc2 [1;2;3] id
;;
//It fails??... []@[] fails


//11.2.iii (with accumulator)
let rec revi xs acc =
    match xs with
    | []    -> acc
    | x::xr -> revi xr (x :: acc)
;;

revi [1;2;3] []



//11.3 (With continuation)
let rec prod xs =
	match xs with
	| [] 	-> 1
	| x::xr -> x * prod xr
;;

prod [1;2;3;4]
;;

let rec prodc xs cont =
    match xs with
    | []    -> cont 1
    | x::xr -> prodc xr (fun valu -> cont (x * valu))
;;

prodc [1;2;3;4] id
;;

//11.4
let rec prodi xs acc =
    match xs with
    | [] -> acc
    | x::xr -> 
        if x <> 0 then
            prodi xr (acc * x)
        else    
            0


//11.4 (optimize)
let rec prodi xs cont =
    match xs with
    | []                -> cont 1
    | x::xr when x = 0  -> 0
    | x::xr             -> prodi xr (fun valu -> cont (x * valu))
;;

prodi [1;2;3;4] id
;;
prodi [1;2;0;4] id
;;


//11.8