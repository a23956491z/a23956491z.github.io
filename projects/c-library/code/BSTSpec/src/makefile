
CC = gcc
CFLAGS = -Wall
BUILD_LIB = ar -crs

INCLUDE = -I../include
SOURCE = -c $<
OBJ = -o $@

all:test.exe

test.exe : dllSpec.o
	$(CC) $^ $(OBJ)
	del /f *.o

dllSpec.o: dllSpec.c
	$(CC) $(SOURCE) $(INCLUDE) $(CFLAGS) $(OBJ)

clean:
	del /f *.exe *.o
