# <span style="color: red;">Warning: This tool will expire on <span style="color: yellow;">2024-08-26</span> and will no longer be usable.</span>

# Please do not use it in an offensive or defensive environment. The author will not be held responsible for any losses that occur.

# The author does not bear any legal responsibility for the consequences of this tool

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
	@ echo [+] Build obj file for x64
	@ $(CCX64) $(CFLAGS) $(SOURCES)
	@ echo [+] Build bin file
	@ $(LINKER) -e $(ENTRYPOINT) -p script/params.json -i script/api.json -o bin/$(PROJECT).x64.bin -f .
	@ $(MAKE) clean

x86:
	@ echo [+] Build obj file for x86
	@ $(CCX86) $(CFLAGS) $(SOURCES)
	@ echo [+] Build bin file
	@ $(LINKER) -e $(ENTRYPOINT) -p script/params.json -i script/api.json -o bin/$(PROJECT).x86.bin -f .
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
// params.json

{
    "format": "zisbnfw",
    "values": [
        "Hello String",
        12345678,
        65535,
        128,
        true,
        "file.txt",
        "你好 天天"
    ]
}
```

```c
// entry.c

#include <entry.h>
#include <parse.h>
#include <a.h>

void go( PVOID Buffer, INT Length, PDATA Sections )
{
    PARSER Parser = { 0 };
    LPVOID Data   = NULL;
    SIZE_T Size   = 0x1000;

    ParserCreate( &Parser, Buffer, Length );

    printf( "%s\n", ParserExtract( &Parser, NULL ) );           // 'z'
    printf( "%d\n", ParserInt( &Parser ) );                     // 'i'
    printf( "%d\n", ParserWord( &Parser ) );                    // 's'
    printf( "%d\n", ParserByte( &Parser ) );                    // 'b'
    printf( "%s\n", ParserBool( &Parser ) ? "true" : "false" ); // 'n'
    printf( "%s\n", ParserExtract( &Parser, NULL ) );           // 'f'

    // 'w'
    MessageBoxW( 0, ParserExtract( &Parser, NULL ), L"WCHAR String", MB_OK );

    NtAllocateVirtualMemory( GetCurrentProcess(), &Data, 0, &Size, MEM_COMMIT, PAGE_READWRITE );

    memset( Data, 0, Size );

    sprintf( Data, "Hello World 11111" );

    printf( "%s\n", Data );

    a();
    b();
    c();
    d();
}
```

---

> The above describes how to pass and receive parameters

---

## Subsequent upgrades

- Encrypted storage of data segments and other information
- Or use a more secure API call strategy
- Size optimization ( I think it's a bit large )
- Maybe there are other places...

## Upgrade

- A new Sections parameter is added to the entry function to obtain TEXT, DATA, RDATA, and BSS section information.

---

```c
// demo

typedef struct
{
    INT   Size;
    PVOID Data;
} DATA, *PDATA;

#define SEC_TEXT  ( 0x0000 )
#define SEC_DATA  ( 0x0001 )
#define SEC_RDATA ( 0x0002 )
#define SEC_BSS   ( 0x0003 )

void entry( PVOID Buffer, INT Length, PDATA Sections )
{
    for( INT Sec = 0; Sec < 4; Sec++ )
    {
        printf( "Section Infomation: 0x%08X | 0x%p\n", Sections[ Sec ].Size, Sections[ Sec ].Data );
    }
}
```
