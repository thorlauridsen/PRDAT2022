# Programs as Data
Source code repository for code handed out during course.

## FsLexYacc

### A what?
In this course you will write small [lexers](https://en.wikipedia.org/wiki/Lexical_analysis) and [parsers](https://en.wikipedia.org/wiki/Parsing#Parser) using respectively [FsLex](https://fsprojects.github.io/FsLexYacc/fslex.html) and [FsYacc](https://fsprojects.github.io/FsLexYacc/fsyacc.html), and we have decided to keep it as minimal as possible. Instead of a full-blown Visual Studio project with excessively many tools and nuget packages, we have opted for a more minimal approach: you basically download and install the tools locally, and run them in your command line (typically Terminal.app on macOS and CMD/Powershell on Windows). If you are unfamiliar with running applications or scripts in your command line, or if all of this sounds like alien talk, please read the [following guide](https://www.theodinproject.com/paths/foundations/courses/foundations/lessons/command-line-basics-web-development-101), and do the exercises too. The guide is mostly relevant for Mac/Linux, but you can surely find stuff for Windows Powershell/CMD, too. The command line is a dear friend that you will use a lot in your professional life as well.

### Installation

#### Mac/Linux
*This guide was written on a Macbook Air with the M1 chip, but it should be the same for other Mac systems and Linux too. Please ping us if you have issues.*

As you may know, `.exe`-files are native executables on Windows, and therefore Mac/Linux will not understand them. For that, you need Mono. After that you will be able to do:

`mono my_executable.exe`

**Steps**
1. Clone this repository and grab the executables/DLLs from the `fsharp` directory, and put them in `$HOME/bin/fsharp` or `~/bin/fsharp` (or some other place you fancy; at least moving them out of `~/Downloads` is recommended)
2. Head to [Mono’s website](https://www.mono-project.com/download/stable/) and fetch latest version (I picked Visual Studio channel)
3. After installation, you should have `mono` available in your command line (close and reopen your Terminal if you cannot run it)

**Usage**

Follow the README's files in the respective directories, i.e. in `Expr/`. Generally, you want to do:

*(note that `<text>` means that you need to replace `<text>` with what makes sense)*


For lexing:
`mono ~/bin/fsharp/fslex.exe --unicode <lexer>.fsl`

And parsing (essentially the same):
`mono ~/bin/fsharp/fsyacc.exe --module <module-name> <parser>.fsy`


**Put a script on it**

*Note: out of scope for course / for terminal aficionados only*

Now, you will do this a lot, so a small script can come in handy

`fslex <lexer>.fsl` and `fsyacc <parser>.fsy`

**fslex**
```{bash}
#!/bin/bash
BASE=$HOME/bin/fsharp
FSLEX=$BASE/fslex.exe
mono $FSLEX --unicode $*
```

**fsyacc**
```bash
#!/bin/bash
BASE=$HOME/bin/fsharp
FSYACC=$BASE/fsyacc.exe
FILE_NAME=${1%%.*}
mono $FSYACC --module $FILE_NAME $*
```

Both scripts are placed in `~/bin` folder (which is added to path; look this up if unsure what it means), and made executable by running `chmod +x fslex fsyacc`.


## Known issues
* If you have issues with no syntax check (Intellisense) or type annotations from Ionide in Visual Studio Code, try changing your file extension from `.fs` to `.fsx` (or vice-versa) while developing
* If you get problems with `LexBuffer<byte>` expected `LexBuffer<char>`, make sure you have the unicode flag when running your lexer, i.e. `fslex --unicode <lexer>.fsl`
* If your have problems with "Lexing" namespace, try remove "Microsoft" from the namespace in your `.fsl` file, rerun `fslex --unicode <lexer>.fsl` and try again. If you are on Windows, you might NEED the "Microsoft." part in front of the Lexing namespace
* If you get an error like this when running your `<lexer>.exe`, i.e. on Mac/Linux `mono Lexer.exe`:

```
  Unhandled Exception:
System.BadImageFormatException: Could not resolve field token 0x04000026, due to: Could not load type of field ...
```

  you can try copy the FsLexYacc.Runtime.dll to your local folder. For some reason when running the executable it will look for the DLL in the current folder.
  Do the following in your terminal when you are inside the folder where your `exe` is (Linux/Mac):

```
  cp /Path/To/Your/FsLexYacc.Runtime.dll .
```
* If you get `<SOMETHING> is not recognized as an internal or external command`, that simply means that your commando line does not recognize the commando you just typed. In terms of `fsharpc` or similar, try instead `dotnet fsc`, or simply `fsc` – if none works, you need to find out where your F# compiler is on your machine, and then add it to your path. [Here](https://www.architectryan.com/2018/08/31/how-to-change-environment-variables-on-windows-10/) is a guide for Windows, and [here](https://osxdaily.com/2014/08/14/add-new-path-to-path-command-line/) for Mac/Linux

* The F# compiler (`fsc`) is not automatically added to a lot of users on Windows, and it's quite hard to find. One solution that has worked for me & others is to install F# through Visual Studio (you need either the Community or Enterprise version - **NOTE**: this is NOT Visual Studio Code), and then find the `fsc.exe` that appears. For me, it appears at `C:\Program Files (x86)\Microsoft Visual Studio\2019\Enterprise\Common7\IDE\CommonExtensions\Microsoft\FSharp` - if you are not sure, go to Visual Studio through your file explorer and search in the corner for `fsc.exe` - that should make it appear if it exists

* PowerPack and its DLL is depracated (dead and gone); you should only use `FsLexYacc.Runtime.dll`, and you should only use that very one that comes with your `fs(lex|yacc).exe` files
