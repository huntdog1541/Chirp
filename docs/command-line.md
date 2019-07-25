# Command line

The chirp compiler uses a command line interface to compiler your program with the needed parameters.

## Compiling your single file program

Before reading endless pages of reference, you want to first know the basics of compiling a program with Chirp. Below is an example.

```bash
chirp test.ch -o test.o
```

This should compile your program to ``test.o``.

## Compiling your multiple file program

*work in progress, i didn't even start working on the import keyword. Just remember that it should automatically get the other files using the "import" in your code unlike with g++ where you need to specify each files in the command line*

## Flags

| Flag | Action |
| --- | --- |
| -o | ``optional`` Specify the output file |
| -v | ``optional`` Activate verbose mode |
| -asm | ``optional`` Keeps the assembly file(s) |

## Developper tools

Theses are tools that should be used by people developping this compiler, but really anyone can use it. Currently there is only two developper settings ``-v`` and ``-asm``, but more will be added. Below is what I use most of the time.

```bash
chirp test.ch -v -asm
```

### Verbose mode

Verbose mode is activated by ``-v`` and activates debug message, it provides **a lot** of compile time information.  Below is an example of the logs created by the compilation of the program ``int: a = 123``

```
LOG: Verbose mode enabled, so you'll see debug messages too
WARNING:  Assembly file won't be cleaned up
WARNING:  No output file specified, using default.
DEBUG:  Debug messages are now visible
DEBUG:  --===-- SYNTAX ANALYSIS --===--
DEBUG:  Matched confirm token
DEBUG:  Matched identifier token
DEBUG:  Not a declaration
ERROR:  Unrecognized statement, with token value::
DEBUG:  Not a declaration
DEBUG:  Identifier matched
DEBUG:  Assignement operator matched
DEBUG:  --===-- SEMANTIC ANALYSIS --===--
DEBUG:  -=- TREE TRAVERSAL BEGIN -=-
DEBUG:  Succesfully pushed value: root
DEBUG:  Succesfully pushed value: statement
DEBUG:  Succesfully pushed value: statement
DEBUG:  Succesfully pushed value: declaration
DEBUG:  Succesfully pushed value: assignment
DEBUG:  Succesfully pushed value: specifier
DEBUG:  Succesfully pushed value: identifier
DEBUG:  Succesfully pushed value: target
DEBUG:  Succesfully pushed value: target
DEBUG:  Succesfully pushed value: data_type
DEBUG:  Succesfully pushed value: a
DEBUG:  Succesfully pushed value: identifier
DEBUG:  Succesfully pushed value: expression
DEBUG:  Succesfully pushed value: int
DEBUG:  Succesfully pushed value: a
DEBUG:  Succesfully pushed value: litteral
DEBUG:  Succesfully pushed value: 123
DEBUG:  -=- TREE TRAVERSAL END -=-
DEBUG:  Analysed variable declaration
DEBUG:  type:int
DEBUG:  name:a
DEBUG:  Analysed variable assignement
DEBUG:  target:a
DEBUG:  source:123
DEBUG:  --===-- IR GENERATION --===--
DEBUG:  -=- TREE TRAVERSAL BEGIN -=-
DEBUG:  Succesfully pushed value: root
DEBUG:  Succesfully pushed value: entry
DEBUG:  Succesfully pushed value: declaration
DEBUG:  Succesfully pushed value: assignment
DEBUG:  Succesfully pushed value: int
DEBUG:  Succesfully pushed value: a
DEBUG:  Succesfully pushed value: target
DEBUG:  Succesfully pushed value: source
DEBUG:  Succesfully pushed value: a
DEBUG:  Succesfully pushed value: litteral
DEBUG:  Succesfully pushed value: 123
DEBUG:  -=- TREE TRAVERSAL END -=-
DEBUG:  Analysed assignment AST
DEBUG:  target:a
DEBUG:  source type:litteral
DEBUG:  source:123
DEBUG:  Registering variable
DEBUG:  Litteral found
DEBUG:  Result of variable assignement is:
<===> 
mov [rbp-4], 123
<===>
SUCCESS:  Nothing went wrong, and this is all it can do right now

```