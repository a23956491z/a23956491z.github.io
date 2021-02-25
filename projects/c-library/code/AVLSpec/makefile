
VPATH = obj src

CC = gcc
CFLAGS = -Wall
BUILD_LIB = ar -crs

INCLUDE= -I./include
SOURCE = -c $<
OBJ = -o $@

all:out.exe
lib: lib/libAVLSpec.a


out.exe : obj/main.o lib/libTreeSpec.a
	$(CC) $^ $(OBJ)

lib/libTreeSpec.a: obj/AVLSpec.o obj/BSTSpec.o
	mkdir -p $(@D)
	$(BUILD_LIB) $@ $^

obj/main.o: main.c
	mkdir -p $(@D)
	$(CC) $(SOURCE) $(INCLUDE) $(CFLAGS) $(OBJ)

obj/AVLSpec.o: AVLSpec.c
	mkdir -p $(@D)
	$(CC) $(SOURCE) $(INCLUDE) $(CFLAGS) $(OBJ)

obj/BSTSpec.o: BSTSpec.c
	mkdir -p $(@D)
	$(CC) $(SOURCE) $(INCLUDE) $(CFLAGS) $(OBJ)
clean:
	del /f obj/*.o bin/*.exe

run:
	./out
