
VPATH = obj src 

CC = gcc
CFLAGS = -Wall
BUILD_LIB = ar -crs

INCLUDE= -I./include
SOURCE = -c $<
OBJ = -o $@

all:bin/out.exe

bin/out.exe : main.o lib/libdllSpec.a
	@mkdir -p $(@D)
	$(CC) $^ $(OBJ)
obj/main.o: main.c
	@mkdir -p $(@D)
	$(CC) $(SOURCE) $(INCLUDE) $(CFLAGS) $(OBJ)

lib/libdllSpec.a: bigNum_int.o dllSpec.o
	@mkdir -p $(@D)
	$(BUILD_LIB) $@ $^

obj/bigNum_int.o: bigNum_int.c
	$(CC) $(SOURCE) $(INCLUDE) $(CFLAGS) $(OBJ)
obj/dllSpec.o: dllSpec.c
	@mkdir -p $(@D)
	$(CC) $(SOURCE) $(INCLUDE) $(CFLAGS) $(OBJ)

clean:
	del /f obj/*.o bin/*.exe

