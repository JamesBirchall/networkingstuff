CFLAGS= -Wall 

all:	showip.o 
	gcc showip.c -lm -g -o showip

clean:
	rm -f showip.o showip 
