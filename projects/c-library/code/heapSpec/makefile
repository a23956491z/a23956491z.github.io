
VPATH = obj src

CC = gcc
CFLAGS = -Wall
BUILD_LIB = ar -crs
SHARE_LIB = -shared

INCLUDE= -I./include
SOURCE = -c $<
OBJ = -o $@

TEST = dynamic

all:out.exe

ifeq ($(TEST), static)
out.exe : obj/main.o lib/libheap.a
	$(CC) $^ $(OBJ)
else ifeq ($(TEST), dynamic)
out.exe : obj/main.o lib/libheap.dll
	$(CC) $^ $(OBJ)
else
out.exe : obj/main.o obj/dllSpec.o
	$(CC) $^ $(OBJ)
endif

obj/main.o: main.c
	mkdir -p $(@D)
	$(CC) $(SOURCE) $(INCLUDE) $(CFLAGS) $(OBJ)

obj/dllSpec.o: dllSpec.c
	mkdir -p $(@D)
	$(CC) $(SOURCE) $(INCLUDE) $(CFLAGS) $(OBJ)
lib/libheap.a: dllSpec.o
	mkdir -p $(@D)
	$(BUILD_LIB) $@ $^

lib/libheap.dll: dllSpec.o
	mkdir -p $(@D)
	$(CC) $(SHARE_LIB) $(OBJ) $^


clean:
	rm -f obj/*.o bin/*.exe
static_lib: lib/libheap.a
dynamic_lib: lib/libheap.dll
