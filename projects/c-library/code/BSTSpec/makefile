
VPATH = obj src

CC = gcc
CFLAGS = -Wall
BUILD_LIB = ar -crs

INCLUDE= -I./include
SOURCE = -c $<
OBJ = -o $@

all:out.exe

out.exe : obj/main.o lib/libBSTSpec.a
	$(CC) $^ $(OBJ)

obj/main.o: main.c
	mkdir -p $(@D)
	$(CC) $(SOURCE) $(INCLUDE) $(CFLAGS) $(OBJ)

lib/libBSTSpec.a: BST_int.o BSTSpec.o
	mkdir -p $(@D)
	$(BUILD_LIB) $@ $^

obj/BST_int.o: BST_int.c
	mkdir -p $(@D)
	$(CC) $(SOURCE) $(INCLUDE) $(CFLAGS) $(OBJ)
obj/BSTSpec.o: BSTSpec.c
	mkdir -p $(@D)
	$(CC) $(SOURCE) $(INCLUDE) $(CFLAGS) $(OBJ)

clean:
	del /f obj/*.o bin/*.exe
