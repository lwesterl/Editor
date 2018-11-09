# Author: Lauri Westerholm
# A really simple Makefile
# Used to build the test files
# Creates libbezier.a


CC = g++
CFLAGS = -Wall -pedantic
Files = lib vector2_test bezier_test
O_Files = test_bezier.o vector2.o
EXE = bezier_test vector2_test
STATIC_F = ar rcs




default: all

all: $(Files)

lib:	vector2.o test_bezier.o
	$(STATIC_F) libbezier.a vector2.o test_bezier.o


bezier_test:	lib
	$(CC) $(CFLAGS) bezier_test.cpp -L. -lbezier -o bezier_test

vector2_test:	lib
	$(CC) $(CFLAGS) vector2_test.cpp -L. -lbezier -o vector2_test

vector2.o:
	$(CC) $(CFLAGS) ../src/vector2.cpp -c

test_bezier.o:
	$(CC) $(CFLAGS) test_bezier.cpp -c


clean:
	$(RM) ${EXE} ${O_Files} libbezier.a

clean-objects:
	$(RM) ${O_Files}

clean-lib:
	$(RM) libbezier.a
