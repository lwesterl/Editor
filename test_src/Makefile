# Author: Lauri Westerholm
# Simple Makefile
# Used to build the test files
# Creates libbezier.a


CC = g++
CFLAGS = -Wall -pedantic -Wextra
Files = lib vector2_test bezier_test
O_Files = test_bezier.o vector2.o
EXE = bezier_test vector2_test
STATIC_F = ar rcs
SRC = ../src/


default: all

all: $(Files)

lib:	vector2.o test_bezier.o
	$(STATIC_F) libbezier.a $^


bezier_test:	lib
	$(CC) $(CFLAGS) bezier_test.cpp -L. -lbezier -o $@

vector2_test:	lib
	$(CC) $(CFLAGS) vector2_test.cpp -L. -lbezier -o $@

# auto compile objects
%.o:	$(SRC)%.cpp
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	$(RM) *.o *_test libbezier.a

clean-objects:
	$(RM) *.o

clean-lib:
	$(RM) libbezier.a
