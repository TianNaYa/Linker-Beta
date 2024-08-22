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
