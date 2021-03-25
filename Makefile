
C = gcc
GDB = gdb

CFLAGS = -std=c89 -Wall -Werror -Wfatal-errors

MODULES = $(sort $(dir $(wildcard /modules/*/)))

MODULES := c_utils win_utils graphics_utils
SOURCES := $(wildcard *.c $(patsubst %, %/*.c, $(MODULES)))
OBJECTS := $(patsubst %.c, objects/%.o, $(SOURCES))

INCLUDE := -I"$(abspath .)" $(patsubst %, -I"$(abspath %)", $(MODULES))
LDFLAGS := -lopengl32 -lgdi32 -shared-libgcc
GDBFLAGS = -cd ./output/

DEBUG = FALSE
ifeq ($(DEBUG), TRUE)
DEFINES =
OPTIMIZE = -g
else
DEFINES = -DNDEBUG
OPTIMIZE = -Os -s
endif

submodule-push:
	git submodule foreach 'git commit -a || :'
	git submodule foreach 'git push || :'

submodule-pull:
	git submodule foreach 'git pull || :'

all: directories clean build

directories:
	-mkdir "output"
	-md "output"
	-mkdir "objects"
	-md "objects"

build: $(OBJECTS) main/main.c main/main.h
	$(C) $(DEFINES) $(OPTIMIZE) $(CFLAGS) $(OBJECTS) $(INCLUDE) -Imain main/main.c -o output/main.exe $(LDFLAGS)

./objects/%.o: ./%.c  ./%.h
	-mkdir "$(@D)"
	-md "$(@D)"
	$(C) $(DEFINES) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	-rm ./objects/*.o ./output/*.exe -f
	-del .\\objects\\*.o .\\output\\*.exe /F /Q
	
debug:
	$(GDB) $(GDBFLAGS) main.exe