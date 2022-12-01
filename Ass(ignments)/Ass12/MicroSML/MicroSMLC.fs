(* Building the command-line compiler for Micro-SML with parameters
     * -verbose : print verbose information on stdout
     * -eval : evaluate the program
     * -opt : compile with optimizations enabled (includes tail calls)
     * -debug: enambles the debug function in Comp.fs and Contcomp.fs for debugging.
*)
     
let args = System.Environment.GetCommandLineArgs()

let _ = printf "Micro-SML compiler v 1.0.0.0 of 2015-12-07\n";;

let readParams (args:string array) =
  let args = args.[1..]  (* Remove micromlc.exe as first array element *)
  let verbose_p = Array.exists ((=) "-verbose") args
  let eval_p = Array.exists ((=) "-eval") args
  let opt_p = Array.exists ((=) "-opt") args
  let debug_p = Array.exists ((=) "-debug") args
  match Array.tryFind (fun s -> s <> "-verbose" && s <> "-eval" && s <> "-opt" && s <> "-debug") args with
    None -> raise (Failure "Usage: micromlc <-opt> <-debug> <-verbose> <-eval> <source file>\n")
  | Some source -> (opt_p,debug_p,verbose_p,eval_p,source)

let _ =
  try    
    let (opt_p,debug_p,verbose_p,eval_p,source) = readParams args  
    let stem =
      if source.EndsWith(".sml") then source.Substring(0,source.Length-4) 
      else source
    let target = stem + ".out"
    printf "Compiling %s to %s\n" source target;
    ignore (ParseTypeAndRun.compFile(opt_p,debug_p,verbose_p,eval_p,source,target))
  with Failure msg -> printf "ERROR: %s\n" msg
