/* File MicroSML/msmlmachine.c A unified-stack abstract machine and
   garbage collector for Micro-SML, a variant of micro-ML extended
   with global mutual recursive functions, tail calls, exceptions and
   cons cells.

   nh@itu.dk * 2015-11-13
   sestoft@itu.dk * 2009-11-17, 2012-02-08

   Compile like this, on ssh.itu.dk say:
      gcc -Wall msmlmachine.c -o msmlmachine

   If necessary, force compiler to use 32 bit integers:
      gcc -m32 -Wall msmlmachine.c -o msmlmachine

   To execute a program file using this abstract machine, do:
      ./msmlmachine <programfile> <arg1> <arg2> ...
   To get also a trace of the program execution:
      ./msmlmachine -trace <programfile> <arg1> <arg2> ...

   This code assumes -- and checks -- that values of type
   int, unsigned int and unsigned int* have size 32 bits.
*/

/*
   Data representation in the stack s[...] and the heap:
    * All integers are tagged with a 1 bit in the least significant
      position, regardless of whether they represent program integers,
      return addresses, array base addresses or old base pointers
      (into the stack).  
    * All heap references are word-aligned, that is, the two least
      significant bits of a heap reference are 00.  
    * Integer constants and code addresses in the program array
      p[...] are not tagged.
   The distinction between integers and references is necessary for 
   the garbage collector to be precise (not conservative).

   The heap consists of 32-bit words, and the heap is divided into 
   blocks.  A block has a one-word header block[0] followed by the 
   block's contents: zero or more words block[i], i=1..n.

   A header has the form ttttttttnnnnnnnnnnnnnnnnnnnnnngg
   where tttttttt is the block tag, all 0 for cons cells
	 nn....nn is the block length (excluding header)
	 gg       is the block's color

   The block color has this meaning:
   gg=00=White: block is dead (after mark, before sweep)
   gg=01=Grey:  block is live, children not marked (during mark)
   gg=11=Black: block is live (after mark, before sweep)
   gg=11=Blue:  block is on the freelist or orphaned

   A block of length zero is an orphan; it cannot be used 
   for data and cannot be on the freelist.  An orphan is 
   created when allocating all but the last word of a free block.
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/time.h>
#include <sys/resource.h>

typedef unsigned int word;

#define IsInt(v) (((v)&1)==1)
#define Tag(v) (((v)<<1)|1)
#define Untag(v) ((v)>>1)

#define White 0
#define Grey  1
#define Black 2
#define Blue  3

#define BlockTag(hdr) ((hdr)>>24)
#define Length(hdr)   (((hdr)>>2)&0x003FFFFF)
#define Color(hdr)    ((hdr)&3)
#define Paint(hdr, color)  (((hdr)&(~3))|(color))

#define CONSTAG 0
#define NILVALUE 0
#define CLOSTAG 1

// Heap size in words

#define HEAPSIZE 100000

word* heap;
word* afterHeap;
word *freelist;

int silent=0; /* Glocal boolean value to run the interpreter in silent mode. Default false. */

// These numeric instruction codes must agree with MicroSML/Machine.fs:
// (Use #define because const int does not define a constant in C)

#define CSTI 0
#define ADD 1
#define SUB 2
#define MUL 3
#define DIV 4
#define MOD 5
#define EQ 6
#define LT 7
#define NOT 8
#define DUP 9
#define SWAP 10
#define LDI 11
#define STI 12
#define GETBP 13
#define GETSP 14
#define INCSP 15
#define GOTO 16
#define IFZERO 17
#define IFNZRO 18
#define CALL 19
#define TCALL 20
#define RET 21
#define PRINTI 22
#define PRINTC 23
#define LDARGS 24
#define STOP 25
#define NIL 26
#define CONS 27
#define CAR 28
#define CDR 29
#define SETCAR 30
#define SETCDR 31
#define PUSHLAB 32
#define HEAPSTI 33
#define ACLOS 34
#define CLOSCALL 35
#define HEAPLDI 36
#define PRINTB 37
#define TCLOSCALL 38
#define PRINTL 39
#define THROW 40
#define PUSHHDLR 41
#define POPHDLR 42

// We check for stack overflow in execcode inbetween execution of two byte code instructions.
// Such instructions can increate the stack arbitraily, e.g., INCSP. The STACKSAFETYSIZE
// is to have a buffer for this not to happen. 

#define STACKSAFETYSIZE 100
#define STACKSIZE 2000000
  
// Print the stack machine instruction at p[pc]

void printInstruction(int p[], int pc) {
  switch (p[pc]) {
  case CSTI:   printf("CSTI %d", p[pc+1]); break;
  case ADD:    printf("ADD"); break;
  case SUB:    printf("SUB"); break;
  case MUL:    printf("MUL"); break;
  case DIV:    printf("DIV"); break;
  case MOD:    printf("MOD"); break;
  case EQ:     printf("EQ"); break;
  case LT:     printf("LT"); break;
  case NOT:    printf("NOT"); break;
  case DUP:    printf("DUP"); break;
  case SWAP:   printf("SWAP"); break;
  case LDI:    printf("LDI"); break;
  case STI:    printf("STI"); break;
  case GETBP:  printf("GETBP"); break;
  case GETSP:  printf("GETSP"); break;
  case INCSP:  printf("INCSP %d", p[pc+1]); break;
  case GOTO:   printf("GOTO %d", p[pc+1]); break;
  case IFZERO: printf("IFZERO %d", p[pc+1]); break;
  case IFNZRO: printf("IFNZRO %d", p[pc+1]); break;
  case CALL:   printf("CALL %d %d", p[pc+1], p[pc+2]); break;
  case TCALL:  printf("TCALL %d %d", p[pc+1], p[pc+2]); break;
  case RET:    printf("RET %d", p[pc+1]); break;
  case PRINTI: printf("PRINTI"); break;
  case PRINTB: printf("PRINTB"); break;
  case PRINTC: printf("PRINTC"); break;
  case PRINTL: printf("PRINTL"); break;    
  case LDARGS: printf("LDARGS"); break;
  case STOP:   printf("STOP"); break;
  case NIL:    printf("NIL"); break;
  case CONS:   printf("CONS"); break;
  case CAR:    printf("CAR"); break;
  case CDR:    printf("CDR"); break;
  case SETCAR: printf("SETCAR"); break;
  case SETCDR: printf("SETCDR"); break;
  case PUSHLAB: printf("PUSHLAB %d", p[pc+1]); break;
  case HEAPSTI: printf("HEAPSTI %d", p[pc+1]); break;
  case HEAPLDI: printf("HEAPLDI %d", p[pc+1]); break;    
  case ACLOS:   printf("ACLOS %d", p[pc+1]); break;
  case CLOSCALL: printf("CLOSCALL %d", p[pc+1]); break;
  case TCLOSCALL: printf("TCLOSCALL %d", p[pc+1]); break;
  case THROW:     printf("THROW"); break;
  case PUSHHDLR:  printf("PUSHHDLR %d", p[pc+1]); break;
  case POPHDLR:   printf("POPHDLR"); break;
  default:     printf("<unknown> <%d>", p[pc]); break; 
  }
}

// Print current stack (marking heap references by #) and current instruction

void printStackAndPc(int s[], int bp, int sp, int p[], int pc) {
  printf("[ ");
  int i;
  for (i=0; i<=sp; i++)
    if (IsInt(s[i]))
      printf("%d ", Untag(s[i]));
    else
      printf("#%d ", s[i]);      
  printf("]");
  printf("{%d:", pc); printInstruction(p, pc); printf("}\n"); 
}

// Read instructions from a file, return array of instructions

int* readfile(char* filename) {
  int capacity = 1, size = 0;
  int *program = (int*)malloc(sizeof(int)*capacity); 
  FILE *inp = fopen(filename, "r");
  if (inp==NULL) {
    printf("File %s does not exists.", filename);
    exit(-1);
  }
  int instr;
  while (fscanf(inp, "%d", &instr) == 1) {
    if (size >= capacity) { 
      int* buffer = (int*)malloc(sizeof(int) * 2 * capacity);
      int i;
      for (i=0; i<capacity; i++)
        buffer[i] = program[i];
      free(program);
      program = buffer;
      capacity *= 2;
    }
    program[size++] = instr;
  }
  fclose(inp);
  return program;
}


// Tags and values

word mkheader(unsigned int tag, unsigned int length, unsigned int color) { 
  return (tag << 24) | (length << 2) | color;
}

void printI (int i) {
  printf("%d ", IsInt(i) ? Untag(i) : i);
}

void printB(int i) {
  if IsInt(i) {
    printf("%s ", Untag(i)?"true":"false");
  } else {
    printf("PRINTB applied on non scalar value.\n");
    exit(-1);
  }
  return;
}       

void printC(int i) {
  if IsInt(i) {
    printf("%c", Untag(i));
  } else {
    printf("PRINTC applied on non scalar value.\n");
    exit(-1);
  }
  return;
}

void printL(int i) {
  //  printf("in printL %d\n",i);
  if (i == NILVALUE) {
    printf("[]");
  } else {
    int *consPtr = (int *)i;
    if (BlockTag(*consPtr) != CONSTAG) {
      printf("PRINTL: Expected CONSTAG.\n");
      exit(-1);
    }
    printf("[");
    int done=0;
    do {
      int hd = consPtr[1];
      int tl = consPtr[2];
      if (IsInt(hd)) printf("%d", Untag(hd));
      else {
        //int *vPtr = (int *)hd;
	if (hd == NILVALUE || (BlockTag(*((int *)hd)) == CONSTAG)) printL(hd);
        else printf("Unexpected hd=%d\n", hd);
      }
      if (tl != NILVALUE) {
        consPtr = (int *)tl;
	printf(",");
      }
      else
	done = 1;
    } while (!done);
    printf("]");
  } 
  return;
}

// Garbage collection and heap allocation 

int inHeap(word* p) {
  return heap <= p && p < afterHeap;
}

// Call this after a GC to get heap statistics:

void heapStatistics() {
  int blocks = 0, free = 0, orphans = 0, 
    blocksSize = 0, freeSize = 0, largestFree = 0;
  word* heapPtr = heap;
  while (heapPtr < afterHeap) {
    if (Length(heapPtr[0]) > 0) {
      blocks++;
      blocksSize += Length(heapPtr[0]);
    } else 
      orphans++;
    word* nextBlock = heapPtr + Length(heapPtr[0]) + 1;
    if (nextBlock > afterHeap) {
      printf("heapStatistics HEAP ERROR: block at heap[%d] (%d), length %d extends beyond heap\n", 
	     heapPtr-heap,(word)&heapPtr[0], Length(heapPtr[0]));
      exit(-1);
    }
    heapPtr = nextBlock;
  }
  word* freePtr = freelist;
  while (freePtr != 0) {
    free++; 
    int length = Length(freePtr[0]);
    if (freePtr < heap || afterHeap < freePtr+length+1) {
      printf("HEAP ERROR: freelist item %d (at heap[%d], length %d) is outside heap\n", 
	     free, freePtr-heap, length);
      exit(-1);
    }
    freeSize += length;
    largestFree = length > largestFree ? length : largestFree;
    if (Color(freePtr[0])!=Blue)
      printf("Non-blue block at heap[%d] on freelist\n", (int)freePtr);
    freePtr = (word*)freePtr[1];
  }
  if (!silent)
    printf("Heap: %d blocks (%d words); of which %d free (%d words, largest %d words); %d orphans\n", 
	   blocks, blocksSize, free, freeSize, largestFree, orphans);
}

void initheap() {
  heap = (word*)malloc(sizeof(word)*HEAPSIZE);
  afterHeap = &heap[HEAPSIZE];
  // Initially, entire heap is one block on the freelist:
  heap[0] = mkheader(0, HEAPSIZE-1, Blue);
  heap[1] = (word)0;
  freelist = &heap[0];
}

void markPhase(int s[], int sp) {
  if (!silent) printf("GC[");
  if (!silent) printf("M");
}

void sweepPhase() {
  if (!silent) printf(",");
  if (!silent) printf("BS]");
}

void collect(int s[], int sp) {
  markPhase(s, sp);
  sweepPhase();
  heapStatistics();
}

word* allocate(unsigned int tag, unsigned int length, int s[], int sp) {
  int attempt = 1;
  do {
    word* free = freelist;
    word** prev = &freelist;
    while (free != 0) {
      int rest = Length(free[0]) - length;
      if (rest >= 0)  {
        if (rest == 0) // Exact fit with free block
	  *prev = (word*)free[1];
        else if (rest == 1) { // Create orphan (unusable) block
          *prev = (word*)free[1];
          free[length+1] = mkheader(0, rest-1, Blue);
	} else { // Make previous free block point to rest of this block
          *prev = &free[length+1];
          free[length+1] = mkheader(0, rest-1, Blue);
          free[length+2] = free[1];
        }
        free[0] = mkheader(tag, length, White);
        return free;
      }
      prev = (word**)&free[1];
      free = (word*)free[1];
    }
    // No free space, do a garbage collection and try again
    if (attempt==1)
      collect(s, sp);
  } while (attempt++ == 1);
  printf("Out of memory\n");
  exit(1);
}
  
// The machine: execute the code starting at p[pc] 

int execcode(int p[], int s[], int iargs[], int iargc, int /* boolean */ trace) {
  int bp = -999;        // Base pointer, for local variable access 
  int sp = -1;          // Stack top pointer
  int pc = 0;           // Program counter: next instruction
  int hr = -1;          // Handler Register
  for (;;) {
    if (STACKSIZE-sp <= 0) {
      printf("Stack overflow");
      return 0;
    }
    if (trace) 
      printStackAndPc(s, bp, sp, p, pc);
    switch (p[pc++]) {
    case CSTI:
      s[sp+1] = Tag(p[pc++]); sp++; break;
    case ADD: 
      s[sp-1] = Tag(Untag(s[sp-1]) + Untag(s[sp])); sp--; break;
    case SUB: 
      s[sp-1] = Tag(Untag(s[sp-1]) - Untag(s[sp])); sp--; break;
    case MUL: 
      s[sp-1] = Tag(Untag(s[sp-1]) * Untag(s[sp])); sp--; break;
    case DIV: 
      s[sp-1] = Tag(Untag(s[sp-1]) / Untag(s[sp])); sp--; break;
    case MOD: 
      s[sp-1] = Tag(Untag(s[sp-1]) % Untag(s[sp])); sp--; break;
    case EQ: 
      s[sp-1] = Tag(s[sp-1] == s[sp] ? 1 : 0); sp--; break;
    case LT: 
      s[sp-1] = Tag(s[sp-1] < s[sp] ? 1 : 0); sp--; break;
    case NOT: {
      int v = s[sp];
      s[sp] = Tag((IsInt(v) ? Untag(v) == 0 : v == 0) ? 1 : 0);
    } break;
    case DUP: 
      s[sp+1] = s[sp]; sp++; break;
    case SWAP: 
      { int tmp = s[sp];  s[sp] = s[sp-1];  s[sp-1] = tmp; } break; 
    case LDI:                 // load indirect
      s[sp] = s[Untag(s[sp])]; break;
    case STI:                 // store indirect, keep value on top
      s[Untag(s[sp-1])] = s[sp]; s[sp-1] = s[sp]; sp--; break;
    case GETBP:
      s[sp+1] = Tag(bp); sp++; break;
    case GETSP:
      s[sp+1] = Tag(sp); sp++; break;
    case INCSP:
      sp = sp+p[pc++]; break;
    case GOTO:
      pc = p[pc]; break;
    case IFZERO: { 
      int v = s[sp--];
      pc = (IsInt(v) ? Untag(v) == 0 : v == 0) ? p[pc] : pc+1; 
    } break;
    case IFNZRO: { 
      int v = s[sp--];
      pc = (IsInt(v) ? Untag(v) != 0 : v != 0) ? p[pc] : pc+1; 
    } break;
    case CALL: { 
      int argc = p[pc++];
      int i;
      for (i=0; i<argc; i++)               // Make room for return address
        s[sp-i+2] = s[sp-i];               // and old base pointer
      s[sp-argc+1] = Tag(pc+1); sp++; 
      s[sp-argc+1] = Tag(bp);   sp++; 
      bp = sp+1-argc;
      pc = p[pc]; 
    } break; 
    case TCALL: { 
      int argc = p[pc++];                  // Number of new arguments
      int pop  = sp-bp; /* BUG */                   // Number of variables to discard
      int i;
      for (i=argc-1; i>=0; i--)    // Discard variables
        s[sp-i-pop] = s[sp-i];
      sp = sp - pop; pc = p[pc]; 
    } break; 
    case RET: { 
      int res = s[sp];
      sp = sp-p[pc]; bp = Untag(s[--sp]); pc = Untag(s[--sp]); 
      s[sp] = res; 
    } break; 
    case PRINTI:
      printI(s[sp]); break;
    case PRINTB:
      printB(s[sp]); break;
    case PRINTC:
      printC(s[sp]); break;
    case PRINTL:
      printL(s[sp]); break;
    case LDARGS: {
      int i;
      for (i=0; i<iargc; i++) // Push commandline arguments
        s[++sp] = Tag(iargs[i]);
    } break;
    case STOP:
      printf("\nResult value: %d", Untag(s[sp]));
      return 0;
    case NIL:    
      s[sp+1] = NILVALUE; sp++; break;
    case CONS: {
      word* p = allocate(CONSTAG, 2, s, sp); 
      p[1] = (word)s[sp-1];
      p[2] = (word)s[sp];
      s[sp-1] = (int)p;
      sp--;
    } break;
    case CAR: {
      word* p = (word*)s[sp]; 
      if (p == 0) 
        { printf("Cannot take car of null\n"); return -1; }
      s[sp] = (int)(p[1]);
    } break;
    case CDR: {
      word* p = (word*)s[sp]; 
      if (p == 0) 
        { printf("Cannot take cdr of null\n"); return -1; }
      s[sp] = (int)(p[2]);
    } break;
    case SETCAR: {
      word v = (word)s[sp--];
      word* p = (word*)s[sp]; 
      p[1] = v;
    } break;
    case SETCDR: {
      word v = (word)s[sp--];
      word* p = (word*)s[sp]; 
      p[2] = v;
    } break;
    case PUSHLAB: {
      s[++sp] = (word)(Tag(p[pc++]));
    } break;
    case HEAPSTI: {
      int n = p[pc++];
      word* ptr = (word*)s[sp];
      for (int i=0;i<n;i++)
	ptr[i+1] = (word)s[sp-n+i];  // p[0] is the heap allocated tag.
      s[sp-n] = s[sp];             // Move pointer to heap object.
      sp = sp-n;                   // Pointer to heap object now top of stack.
      //      printf("HEAPSTI: n=%d, ptr[0]=%d, ptr[1]=%d, ptr[2]=%d, length=%d",n,ptr[0],ptr[1],ptr[2],Length(ptr[0]));
    } break;
    case HEAPLDI: {
      int offset = p[pc++];
      word* ptr = (word*)s[sp];
      s[sp] = (int)ptr[offset+1];      // +1 to accomodate for the closure tag.
    } break;
    case ACLOS: {
      int n = p[pc++];             // size of closure, n>0 as first index is mandatory code pointer
      word* ptr = allocate(CLOSTAG, n, s, sp);
      for (int i=0;i<n;i++)
	// Init storage scalar values in case gc is invoked before data is filled in with HEAPSTI.
	// Could happen with mutually recursive functions.
	ptr[i+1] = Tag(0); 
      s[++sp] = (int)ptr;
    } break;
    case CLOSCALL: {
      int argc = p[pc++];
      argc++;                              // Closure is additional first argument.
      for (int i=0; i<argc; i++)           // Make room for return address
        s[sp-i+2] = s[sp-i];               // and old base pointer
      s[sp-argc+1] = Tag(pc); sp++; 
      s[sp-argc+1] = Tag(bp); sp++; 
      bp = sp+1-argc;
      word* cp = (word*)s[bp];             // cp is pointer to closure.
      pc = Untag(cp[1]);                   // Label is a tagged scalar at index 1, see PUSHLAB.
      //	printf("\n pc=%d, hr=%d, sp=%d, bp=%d\n", pc, hr, sp, bp);		      
    } break;
    case TCLOSCALL: {
      int argc = p[pc++];
      argc++;                              // Closure is additional first argument.
      int pop  = sp-bp-argc+1;               // Number of variables to discard
      if (pop < 0) printf("PANIC\n");
      //      printf("sp=%d, bp=%d,argc=%d,pop=%d\n",sp,bp,argc,pop);
      for (int i=argc-1; i>=0; i--)        // Tail call, do not touch existing return address
        s[sp-i-pop] = s[sp-i];             // and old base pointer
      // bp = sp+1-argc; tail call so the same
      sp = sp - pop;
      word* cp = (word*)s[bp];             // cp is pointer to closure.
      pc = Untag(cp[1]);                   // Label is a tagged scalar at index 1, see PUSHLAB.
      //	printf("\n pc=%d, hr=%d, sp=%d, bp=%d\n", pc, hr, sp, bp);		      
    } break;
    case THROW: { // stack,exnVal1,exnlab,prevHr,...,exnVal2 -> stack if exnVal1 = exnVal2
      int exn = Untag(s[sp]);
      while (hr != -1 && Untag(s[hr]) != exn) {
	hr = Untag(s[hr+2]);           // Try next exception handler
      }
      if (hr != -1) {           // Found a handler for exn
        pc = Untag(s[hr+1]);    //   execute the handler code (exnlab)
	sp = hr-1; 	       //    after popping frames above hr
	hr = Untag(s[hr+2]);    //   with current handler being hr 
	while (bp > sp)  
	  bp = Untag(s[bp-1]);  // Restore bp to stack frame containing the exception handler description.
      } else {
	printf("\nResult value: Uncaught exception %d", exn);
	return 0;
      }
    } break;
    case PUSHHDLR: { // stack,exn  -> stack,exn,lab,prevHr
      //	printf("\n pc=%d, hr=%d, sp=%d, bp=%d\n", pc, hr, sp, bp);		      
      s[++sp] = (word)(Tag(p[pc++]));
      s[++sp] = Tag(hr);
      hr = sp-2;
    } break;
    case POPHDLR: { // stack,exn,lab,prevHr,v -> stack,v
      hr = Untag(s[sp-1]);
      s[sp-3] = s[sp];
      sp = sp - 3;
    } break;
    default:                  
      printf("Illegal instruction %d at address %d (%d)\n", p[pc-1], pc-1, (word)&p[pc-1]);
      heapStatistics();
      return -1;
    }
  }
}

// Read program from file, and execute it

int execute(int argc, char** argv, int /* boolean */ trace) {
  int filenameidx = 1 + (trace?1:0) + (silent?1:0); /* Index to filename depends on interpreter options. */
  int argsidx = filenameidx+1; /* Index to extra program arguments depends on interpreter options. */
  int *p = readfile(argv[filenameidx/*trace ? 2 : 1*/]);         // program bytecodes: int[]
  int *s = (int*)malloc(sizeof(int)*(STACKSIZE+STACKSAFETYSIZE));   // stack: int[] 
  int iargc = argc-argsidx; /*trace ? argc - 3 : argc - 2;*/
  int *iargs = (int*)malloc(sizeof(int)*iargc);   // program inputs: int[]
  
  int i;
  for (i=0; i<iargc; i++)                         // Convert commandline arguments
    iargs[i] = atoi(argv[i+argsidx/*trace ? i+3 : i+2*/]);
  // Measure cpu time for executing the program
  struct rusage ru1, ru2;
  getrusage(RUSAGE_SELF, &ru1);
  int res = execcode(p, s, iargs, iargc, trace);  // Execute program proper
  getrusage(RUSAGE_SELF, &ru2);
  struct timeval t1 = ru1.ru_utime, t2 = ru2.ru_utime;
  double runtime = t2.tv_sec-t1.tv_sec+(t2.tv_usec-t1.tv_usec)/1000000.0;
  printf("\nUsed %7.3f cpu seconds\n", runtime);
  return res;
}

// Read code from file and execute it

int main(int argc, char** argv) {
  if (sizeof(word)!=4 || sizeof(word*)!=4 || sizeof(int)!=4) {
    printf("Size of word, word* or int is not 32 bit, cannot run\n");
    return -1;
  } else if (argc < 2) {
    printf("Usage: msmlmachine [-trace] [-silent] <programfile> <arg1> ...\n");
    return -1;
  } else {
    int trace = argc >= 3 && (0==strncmp(argv[1], "-trace", 7) || 0==strncmp(argv[2], "-trace", 7));
    silent = argc >= 3 && (0==strncmp(argv[1], "-silent", 7) || 0==strncmp(argv[2], "-silent", 7));
    initheap();
    return execute(argc, argv, trace);
  }
}
