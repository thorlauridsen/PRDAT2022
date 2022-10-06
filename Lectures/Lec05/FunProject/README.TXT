Compiling and loading the micro-ML evaluator and parser (Fun/README.TXT)
------------------------------------------------------------------------

The items A to C are similar to the code found under folder Fun handed
out last week. In this week we extend with higher order functions,
items D-E and type interence, item F.

A. Loading the micro-ML evaluator, with abstract syntax only

   dotnet fsi Absyn.fs Fun.fs

   open Absyn;;
   open Fun;;
   let res = run (Prim("+", CstI 5, CstI 7));;
   #q;;


B. Generating and compiling the lexer and parser, and loading them:

   fsyacc --module FunPar FunPar.fsy
   fslex --unicode FunLex.fsl
   dotnet fsi -r ~/fsharp/FsLexYacc.Runtime.dll Absyn.fs FunPar.fs FunLex.fs Parse.fs   

   open Parse;;
   let e1 = fromString "5+7";;
   let e2 = fromString "let y = 7 in y + 2 end";;
   let e3 = fromString "let f x = x + 7 in f 2 end";;


C. Using the lexer, parser and first-order evaluator together:

   fsyacc --module FunPar FunPar.fsy
   fslex --unicode FunLex.fsl
   dotnet fsi -r ~/fsharp/FsLexYacc.Runtime.dll Absyn.fs FunPar.fs FunLex.fs Parse.fs Fun.fs ParseAndRun.fs

   open ParseAndRun;;
   run (fromString "5+7");;
   run (fromString "let y = 7 in y + 2 end");;
   run (fromString "let f x = x + 7 in f 2 end");;


D. Loading the evaluator for a higher-order functional language (same
   abstract syntax as the first-order language):

   dotnet fsi Absyn.fs HigherFun.fs

   open HigherFun;;
   eval ex1 [];;
   open Absyn;;
   run (Letfun ("twice", "f",
                Letfun ("g", "x", Call (Var "f", Call (Var "f", Var "x")), Var "g"),
                        Letfun ("mul3", "z", Prim ("*", Var "z", CstI 3),
                                Call (Call (Var "twice",Var "mul3"),CstI 2))));;

   (The above abstract syntax term corresponds to the concrete syntax
   term shown in point E below).


E. Using the lexer, parser and higher-order evaluator together:

   fsyacc --module FunPar FunPar.fsy
   fslex --unicode FunLex.fsl
   dotnet fsi -r ~/fsharp/FsLexYacc.Runtime.dll Absyn.fs FunPar.fs FunLex.fs Parse.fs HigherFun.fs ParseAndRunHigher.fs

   open ParseAndRunHigher;;
   run (fromString @"let twice f = let g x = f(f(x)) in g end 
                     in let mul3 z = z*3 in twice mul3 2 end end");;
					 
	run (fromString @"fun x -> 2*x");;
	run (fromString @"let y = 22 in fun z -> z+y end");;
	run (fromString @"let add x = fun y -> x+y in add 2 5 end");;
	run (fromString @"let add = fun x -> fun y -> x+y in add 2 5 end");;

F. Using the lexer, parser and polymorphic type inference together:

	fsyacc --module FunPar FunPar.fsy
	fslex --unicode FunLex.fsl
	dotnet fsi -r ./fsharp/FsLexYacc.Runtime.dll Absyn.fs FunPar.fs FunLex.fs Parse.fs TypeInference.fs ParseAndType.fs

	open ParseAndType;;
	inferType (fromString "let f x = 1 in f 7 + f false end");;
	inferType (fromString "let f x = 1 in f f end");;
	inferType (fromString "let f g = g g in f end");;
	inferType (fromString "let f x = let g y = y in g false end in f 42 end");;
	inferType (fromString "let f x = let g y = if true then y else x in g false end");;
	inferType (fromString "let f x = let g y = if true then y else x in g false end in f true end");;

	bool -> bool
	inferType (fromString "let f x = let g y = y in g false = x end in f end");;

	int -> int
	inferType (fromString "let f x = let g y = y in g 4 + x end in f end");;

    int -> int -> int
	inferType (fromString "let f x = let g y = y + x in g end in f end");;

    'a -> 'b -> 'a
    inferType (fromString "let x = let g y = x in g end end");;

    'a -> 'b -> 'b
    inferType (fromString "let f x = let g y = y in g end in f end");;

    ('a -> 'b) -> ('b -> 'c) -> ('a -> 'c)
	inferType (fromString "let f x = let g y = let h z = y (x z) in h end in g end in f end");;

    'a -> 'b
    inferType (fromString "let f x = f x in f end");;

    'a
    inferType (fromString "let f x = f x in f 2 end");;
