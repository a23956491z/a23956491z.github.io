
CC = gcc
CFLAGS = -Wall
BUILD_LIB = ar -crs

INCLUDE = -I../include
SOURCE = -c $<
OBJ = -o $@

all:test.exe

test.exe : bigNum_int.o dllSpec.o
	$(CC) $^ $(OBJ)
	del /f *.o

bigNum_int.o: bigNum_int.c
	$(CC) $(SOURCE) $(INCLUDE) $(CFLAGS) $(OBJ)
dllSpec.o: dllSpec.c
	$(CC) $(SOURCE) $(INCLUDE) $(CFLAGS) $(OBJ)

clean:
	del /f *.exe *.o

