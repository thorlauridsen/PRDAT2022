﻿
//  Microsoft (R) .NET Framework IL Disassembler.  Version 4.8.3928.0
//  Copyright (c) Microsoft Corporation.  All rights reserved.



// Metadata version: v4.0.30319
.assembly extern mscorlib
{
  .publickeytoken = (B7 7A 5C 56 19 34 E0 89 )                         // .z\V.4..
  .ver 4:0:0:0
}
.assembly Selsort
{
  .custom instance void [mscorlib]System.Runtime.CompilerServices.CompilationRelaxationsAttribute::.ctor(int32) = ( 01 00 08 00 00 00 00 00 ) 
  .custom instance void [mscorlib]System.Runtime.CompilerServices.RuntimeCompatibilityAttribute::.ctor() = ( 01 00 01 00 54 02 16 57 72 61 70 4E 6F 6E 45 78   // ....T..WrapNonEx
                                                                                                             63 65 70 74 69 6F 6E 54 68 72 6F 77 73 01 )       // ceptionThrows.

  // --- The following custom attribute is added automatically, do not uncomment -------
  //  .custom instance void [mscorlib]System.Diagnostics.DebuggableAttribute::.ctor(valuetype [mscorlib]System.Diagnostics.DebuggableAttribute/DebuggingModes) = ( 01 00 02 00 00 00 00 00 ) 

  .hash algorithm 0x00008004
  .ver 0:0:0:0
}
.module Selsort.exe
// MVID: {99FBD861-595C-4AAC-A029-4908B6543FE0}
.imagebase 0x00400000
.file alignment 0x00000200
.stackreserve 0x00100000
.subsystem 0x0003       // WINDOWS_CUI
.corflags 0x00000001    //  ILONLY
// Image base: 0x04E40000


// =============== CLASS MEMBERS DECLARATION ===================

.class private auto ansi beforefieldinit Selsort
       extends [mscorlib]System.Object
{
  .method public hidebysig static void  SelectionSort(int32[] arr) cil managed
  {
    // Code size       57 (0x39)
    .maxstack  4             // 4 = the number of items that shall be tracked by an analysis tool
    .locals init (int32 V_0, // i      - The verification algorithm shall attempt to associate a valid stack state with every CIL instruction. The stack state specifies the number of slots on the CIL stack at that point in the code and for each slot a required type that shall be present in that slot. The initial stack state is empty (there are no items on the stack).
             int32 V_1,      // least  - Verification assumes that the CLI zeroes all memory other than the evaluation stack before it is made visible to programs. A conforming implementation of the CLI shall provide this observable behavior. Furthermore, verifiable methods shall have the localsinit bit set, see Partition II (Flags for Method Headers). If this bit is not set, then a CLI might throw a Verification exception at any point where a local variable is accessed, and where the assembly containing that method has not been granted SecurityPermission.SkipVerification.
             int32 V_2,      // tmp
             int32 V_3)      // j

    IL_0000:  ldc.i4.0            // 0x16: push 0 onto the stack <- 0;
    IL_0001:  stloc.0             // 0x0A: pop a value from the stack into local variable 0 <- int i = 0 This also means that local variable 0 is i
    IL_0002:  br.s       IL_0032  // 0x2B: unconditional jump  <- go to label IL_0032 which we can assume is the for condition

    IL_0004:  ldloc.0             // 0x06: load i onto stack
    IL_0005:  stloc.1             // 0x0B: pop i from stack and save as local variable 1 (variable least on line 22)
    IL_0006:  ldloc.0             // 0x06: load i onto stack
    IL_0007:  ldc.i4.1            // 0x17: push 1 onto stack
    IL_0008:  add                 // 0x58: arithmetic add (pop 2 numbers from the stack and add them together and push the result unto the stack) (i+1)
    IL_0009:  stloc.3             // 0x0D: store j with value i+1 as local variable 3
    IL_000a:  br.s       IL_001a  // 0x2B: unconditional jump  (go to IL_001a which we can assume is condition for inner loop)

    IL_000c:  ldarg.0             // 0x02: Load the first argument of SelectionSort into stack (int[] arr) 
    IL_000d:  ldloc.3             // 0x09: load local variable 3 (j) onto the stack
    IL_000e:  ldelem.i4           // 0x94  Load element from array at index j (arr[j])
    IL_000f:  ldarg.0             // 0x02  Load the first argument of SelectionSort into stack (int[] arr) 
    IL_0010:  ldloc.1             // 0x07  Load local variable 1 (least) onto the stack
    IL_0011:  ldelem.i4           // 0x94  Load element from array at index least (arr[least])
    IL_0012:  bge.s      IL_0016  // 0x2F  If arr[j] is greater than or equal to arr[least] then go to IL_0016 which is assumed to be (least = j;)

    IL_0014:  ldloc.3             // 0x09  Load local variable 3 (j) onto the stack
    IL_0015:  stloc.1             // 0x0B  pop j from stack and save value on local variable 1 (least=j;)
    IL_0016:  ldloc.3             // 0x09  load local variable 3 (j) onto the stack
    IL_0017:  ldc.i4.1            // Push 1 onto stack as int32
    IL_0018:  add                 // arithmetic add (pop j and 1 from the stack and add together)
    IL_0019:  stloc.3             // store j with value j+1 as local variable 3 (j++;)
    IL_001a:  ldloc.3             // Load local variable 3 (j) onto the stack
    IL_001b:  ldarg.0             // Load the first argument of SelectionSort into stack (int[] arr) 
    IL_001c:  ldlen               // Get the length of the array and only keep the length (arr.length)
    IL_001d:  conv.i4             // Convert to int32
    IL_001e:  blt.s      IL_000c  // goto IL_000c if j is less than length (j < arr.length) IL_000c is assumed to be the inner for loop block

    IL_0020:  ldarg.0             // Load the first argument of SelectionSort into stack (int[] arr) 
    IL_0021:  ldloc.0             // Load local variable 0 (i) onto the stack
    IL_0022:  ldelem.i4           // load element from array at index i onto the stack (arr[i])
    IL_0023:  stloc.2             // Store arr[i] as local variable 2 (tmp)
    IL_0024:  ldarg.0             // Load the first argument of SelectionSort into stack (int[] arr) (arr[i])
    IL_0025:  ldloc.0             // Load local variable 0 (i) onto the stack (arr[i])
    IL_0026:  ldarg.0             // Load the first argument of SelectionSort into stack (int[] arr) (arr[least])
    IL_0027:  ldloc.1             // Load local variable 1 (least) onto the stack (arr[least])
    IL_0028:  ldelem.i4           // Load element from array arr at index least
    IL_0029:  stelem.i4           // Store element in array at index i as arr[least] (arr[i] = arr[least])
    IL_002a:  ldarg.0             // Load the first argument of SelectionSort into stack (int[] arr)
    IL_002b:  ldloc.1             // Load local variable 1 (least)
    IL_002c:  ldloc.2             // Load local variable 2 (tmp)
    IL_002d:  stelem.i4           // Store element in array at index least as tmp
    IL_002e:  ldloc.0             // Load local variable 0 i
    IL_002f:  ldc.i4.1            // Push 1 onto as int32
    IL_0030:  add                 // arithmetic add (pop i and 1 and add together) (i++;)
    IL_0031:  stloc.0             // Store as local variable 0    
    IL_0032:  ldloc.0             // Load i (local variable 0) onto stack
    IL_0033:  ldarg.0             // Load the first argument of SelectionSort into stack (int[] arr)
    IL_0034:  ldlen               // Get the length of the array and only keep the length (arr.length)
    IL_0035:  conv.i4             // Convert to int32
    IL_0036:  blt.s      IL_0004  // goto IL_0004 if i is less than length (i < arr.length;) IL_0004 is assumed is the for block

    IL_0038:  ret
  } // end of method Selsort::SelectionSort
} // end of class Selsort


// =============================================================

// *********** DISASSEMBLY COMPLETE ***********************
