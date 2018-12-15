# Author: Lauri Westerholm
# Simple Makefile
# Used to build the test files
# Creates libbezier.a


CC = g++
CFLAGS = -Wall -pedantic -Wextra
Files = lib Vector2_test Bezier_test
EXE = Bezier_test Vector2_test
STATIC_F = ar rcs
SRC = ../src/


default: all

all: $(Files)

lib:	Vector2.o Test_bezier.o
	$(STATIC_F) libbezier.a $^


Bezier_test:	lib
	$(CC) $(CFLAGS) Bezier_test.cpp -L. -lbezier -o $@

Vector2_test:	lib
	$(CC) $(CFLAGS) Vector2_test.cpp -L. -lbezier -o $@

# auto compile objects
%.o:	$(SRC)%.cpp
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	$(RM) *.o *_test libbezier.a

clean-objects:
	$(RM) *.o

clean-lib:
	$(RM) libbezier.a
