Compiling and loading the micro-C evaluator and parser (MicroC/README.TXT)
--------------------------------------------------------------------------

Archive microc.zip contains the files used in points A, B and C below.


A. Generating and compiling the lexer and parser for micro-C, and
   loading the interpreter for micro-C.

   fslex --unicode CLex.fsl
   fsyacc --module CPar CPar.fsy
   dotnet fsi -r ~/fsharp/FsLexYacc.Runtime.dll Absyn.fs CPar.fs CLex.fs Parse.fs Interp.fs ParseAndRun.fs

   open ParseAndRun;;
   fromFile "ex1.c";;
   run (fromFile "ex1.c") [17];;
   run (fromFile "ex5.c") [];;
   run (fromFile "ex11.c") [8];;

   mac gang:
   mono ./fsharp/fslex.exe --unicode CLex.fsl
   mono ./fsharp/fsyacc.exe --module CPar CPar.fsy
   fsharpi -r ./fsharp/FsLexYacc.Runtime.dll Absyn.fs CPar.fs CLex.fs Parse.fs Interp.fs ParseAndRun.fs
   
   open ParseAndRun;;
   fromFile "ex1.c";;
   run (fromFile "ex1.c") [17];;
   run (fromFile "ex5.c") [];;
   run (fromFile "ex11.c") [8];;
   run (fromFile "7-2-3.c");;

B. To compile and use the micro-C compiler

   fslex --unicode CLex.fsl
   fsyacc --module CPar CPar.fsy
   dotnet fsi -r ~/fsharp/FsLexYacc.Runtime.dll Absyn.fs CPar.fs CLex.fs Parse.fs Machine.fs Comp.fs ParseAndComp.fs   

   open ParseAndComp;;
   compileToFile (fromFile "ex11.c") "ex11.out";;
   compile "ex11";;
   #q;;

   mac gang:
   mono ./fsharp/fslex.exe --unicode CLex.fsl
   mono ./fsharp/fsyacc.exe --module CPar CPar.fsy
   dotnet fsi -r ./fsharp/FsLexYacc.Runtime.dll Absyn.fs CPar.fs CLex.fs Parse.fs Machine.fs Comp.fs ParseAndComp.fs   

   open ParseAndComp;;
   compileToFile (fromFile "7-2-1.c") "7-2-1.out";;
   compileToFile (fromFile "7-2-2.c") "7-2-2.out";;
   compileToFile (fromFile "7-2-3.c") "7-2-3.out";;
   #q;;
   
   compileToFile (fromFile "7-2-1.c") "7-2-1.out";;
   compileToFile (fromFile "7-2-2.c") "7-2-2.out";;
   compileToFile (fromFile "7-2-3.c") "7-2-3.out";;
   compileToFile (fromFile "7-3.c") "7-3.out";;
   compileToFile (fromFile "7-5.c") "7-5.out";;



The Java stack machine:

   javac Machine.java
   java Machine 7-2-1.out
   java Machine 7-2-2.out
   java Machine 7-2-3.out

The C stack machine
   gcc machine.c
   ./a.out ex11.out 8

C. To compile and use the backwards (continuation-based) micro-C compiler:

   fslex --unicode CLex.fsl
   fsyacc --module CPar CPar.fsy
   dotnet fsi -r ./fsharp/FsLexYacc.Runtime.dll Absyn.fs CPar.fs CLex.fs Parse.fs Machine.fs Contcomp.fs ParseAndContcomp.fs   

   open ParseAndContcomp;;
   contCompileToFile (fromFile "7-2-3.c") "7-2-3.out";;
   compile "7-2-3";;
   #q;;

   javac Machine.java
   java Machine 7-2-3.out 8


D. Build the backwards micro-C compiler as a command-line program microcc

   fslex --unicode CLex.fsl
   fsyacc --module CPar CPar.fsy
   dotnet fsi --standalone -r ~/fsharp/FsLexYacc.Runtime.dll Absyn.fs CPar.fs CLex.fs Parse.fs Machine.fs Contcomp.fs MicroCC.fs -o microcc.exe

   mono microcc.exe ex11.c

   javac Machine.java
   java Machine ex11.out 8
