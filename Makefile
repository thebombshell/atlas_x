
C = gcc
GDB = gdb

CFLAGS = -std=c89 -Wall -Werror -Wfatal-errors

MODULES = $(sort $(dir $(wildcard /modules/*/)))

MODULES := c_utils win_utils graphics_utils
SOURCES := $(wildcard *.c $(patsubst %, %/*.c, $(MODULES)))
OBJECTS := $(patsubst %.c, objects/%.o, $(SOURCES))
DISASSEMBLY := $(patsubst %.c, disassembly/%.s, $(SOURCES))

INCLUDE := -I"../zlib" -I"$(abspath .)" $(patsubst %, -I"$(abspath %)", $(MODULES))
LDFLAGS := -L"./" -lopengl32 -lgdi32 -lz -shared-libgcc
GDBFLAGS = -cd ./output/

DEBUG = FALSE
ifeq ($(DEBUG), TRUE)
DEFINES =
OPTIMIZE = -g
else
DEFINES = -DNDEBUG
OPTIMIZE = -Os -s
endif

all: directories clean build

push: submodule-push
	git commit -a
	git push

pull: submodule-pull
	git pull

submodule-push:
	git submodule foreach 'git commit -a || :'
	git submodule foreach 'git push || :'

submodule-pull:
	git submodule foreach 'git pull || :'

directories:
	-mkdir "output"
	-md "output"
	-mkdir "objects"
	-md "objects"
	-mkdir "disassembly"
	-md "disassembly"

disassembly: $(DISASSEMBLY) disassembly/main/main.s

build: $(OBJECTS) main/main.c main/main.h
	$(C) $(DEFINES) $(OPTIMIZE) $(CFLAGS) $(OBJECTS) $(INCLUDE) -Imain main/main.c -o output/main.exe $(LDFLAGS)

symbols: 

./objects/%.o: ./%.c  ./%.h
	-mkdir "$(@D)"
	-md "$(@D)"
	$(C) $(DEFINES) $(OPTIMIZE) $(CFLAGS) $(INCLUDE) -c $< -o $@

./disassembly/%.s: ./%.c  ./%.h
	-mkdir "$(@D)"
	-md "$(@D)"
	$(C) $(DEFINES) $(CFLAGS) $(INCLUDE) -S -fverbose-asm -c $< -o $@

clean:
	-rm ./objects/* ./output/*.exe -f -R
	-del .\\objects\\* .\\output\\*.exe /F /Q /S
	
debug:
	$(GDB) $(GDBFLAGS) main.exe