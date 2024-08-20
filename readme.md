# Warning: This tool will expire on 2024-08-24 and will no longer be usable.
# Linker and Generate Tools Usage Guide

## Linker Tool (`linker.exe`)
---

### Description
Link obj to a position-independent executable.

---

### Usage
```sh
linker.exe [-h] [-e ENTRY] -o OUTPUT -p PARAMS -i IMPORTS -f FILE [FILE ...] [-m MODE]

Link obj to a position-independent executable.

options:
  -h, --help            show this help message and exit
  -e ENTRY, --entry ENTRY
                        Specify the function from which to start execution (entry point)
  -o OUTPUT, --output OUTPUT
                        The output file name
  -p PARAMS, --params PARAMS
                        JSON file path to the arguments to pass to the executable
  -i IMPORTS, --imports IMPORTS
                        JSON file path to the functions to import
  -f FILE [FILE ...], --file FILE [FILE ...]
                        obj path (multiple objs are separated by spaces) or directory
  -m MODE, --mode MODE  Encountered a function processing mode that could not be loaded: ( none, quit )
```

---

### Assume the directory structure is as follows
- Project
    - bin
        - ...
    - script
        - apis.json
        - args.json
        - linker.exe
        - generate.exe
    - include
        - 1.h
        - 2.h
        - 3.h
        - ...
    - src
        - 1.c
        - 2.c
        - 3.c
        - ...
    - x.o

---

> The above file structure assumes that the o files we compile are all in the Project project
> the entry function is go
> and the parameter json and dependency json are both in the script directory

---

### Example
```sh
linker.exe -e go -o payload -p script/args.json -i script.apis.json -f . -m none
```

---

### Explain
> - -e entry
>   - Set our entry function to go
> - -o payload
>   - Set the output file name to payload
> - -p script/args.json
>   - Setting parameter files
> - -i script.apis.json
>   - Set the API dependency file path we need
> - -f .
>   - This parameter can pass the obj path or the path. When the path is passed, all .o or .obj files in this path will be searched by default.
> - m none
>   - Set up how we handle empty functions, Empty functions refer to APIs that do not exist in low-version or high-version systems. How to deal with such APIs

---

### Makfile
``` makefile
MAKEFLAGS    += --no-print-directory

PROJECT      := Demo
ENTRYPOINT   := go

CCX64        := x86_64-w64-mingw32-gcc
CCX86        := i686-w64-mingw32-gcc
LINKER       := script/linker.exe

INCLUDE_DIRS := include

SOURCES      := $(wildcard src/*.c)
CFLAGS       := $(addprefix -I, $(INCLUDE_DIRS)) -masm=intel -s -w -Wall -c -U UNICODE

all: x64 x86

clean:
	@ del /q /f *.o *.obj

x64:
	@ $(CCX64) $(CFLAGS) $(SOURCES)
	@ $(LINKER) -e $(ENTRYPOINT) -p script/args.json -i script/apis.json -o bin/$(PROJECT).x64.bin -f .
	@ $(MAKE) clean

x86:
	@ $(CCX86) $(CFLAGS) $(SOURCES)
	@ $(LINKER) -e $(ENTRYPOINT) -p script/args.json -i script/apis.json -o bin/$(PROJECT).x86.bin -f .
	@ $(MAKE) clean
```

---

## Generate Tool (`generate.exe`)

---

### Description
Generate export function JSON information based on DLL.

---

### Usage
```sh
generate.exe [-h] -o OUTPUT -f FILE [FILE ...]

Generate export function json information based on dll.

options:
  -h, --help            show this help message and exit
  -o OUTPUT, --output OUTPUT
                        The output file name (excluding the suffix)
  -f FILE [FILE ...], --file FILE [FILE ...]
                        dll path (multiple dlls are separated by spaces)
```

---

### Example
```sh
generate.exe -o apis -f a.dll b.dll c.dll d.dll ...
```

---

## Parameter passing method
```json
// args.json

{
    "format": "zbsifn",
    "values": [
        "Hello World Parameters",
        65,
        20,
        483913,
        "a.txt",
        false
    ]
}
```

```c
// main.c

#include <stdio.h>
#include <parse.h>

void go( void* buffer, int length )
{
    PARSER parser;
    char*  data;
    int    size;

    /* create parser */
    ParserCreate( &parser, buffer, length );

    /* format 'z' */
    data = ParserExtract( &parser, &size );
    printf( "z -> %d | %s\n", size, data );

    /* format 'b' */
    printf( "b -> %d\n", ParserByte( &parser ) );

    /* format 's' */
    printf( "s -> %d\n", ParserWord( &parser ) );

    /* format 'i' */
    printf( "i -> %d\n", ParserInt( &parser ) );

    /* format 'f' */
    data = ParserExtract( &parser, &size );
    printf( "f -> %d | %s\n", size, data );

    /* format 'n' */
    printf( "n -> %s\n", ParserBool( &parser ) ? "true" : "false" );
}
```

---

> The above describes how to pass and receive parameters

