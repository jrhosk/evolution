# Makefile to compile seria evolution code
#       Joshua Hoskins 
#

LIB        = -L/usr/lib64/ -L/usr/lib/
INCLUDES   = -Iinclude/ -I/usr/include/
CC         = g++
SRC        = src
CFLAGS     = -O -std=c++11 -Wall

all: evolution rungekutta

%.o: %.cc
	${CC} ${INCLUDES} ${CFLAGS} -c -o $@ $< 
evolution : evolution.cc ${SRC}/FemtoEvolve.o ${SRC}/gpd.o
	${CC} ${INCLUDES} -o $@  ${CFLAGS} $^ ${LIB}
rungekutta : runge_kutta.cc
	${CC} ${INCLUDES} -o $@  ${CFLAGS} $^ ${LIB}
clean:
	rm -f *.o *~
