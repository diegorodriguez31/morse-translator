SOURCES = $(wildcard *.c)
BINAIRES = $(patsubst %.c, %.o, ${SOURCES})
GCC = gcc
WIRINGPI = -lwiringPi


all: main

main: ${BINAIRES}
	${GCC} $^ -o $@ ${WIRINGPI}

%.o: %.c %.h
	${GCC} -c $<
	
clean:
	rm -r *.o
