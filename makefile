CFLAGS= -Wall 

tcpdaytimeserveripv4:	tcpdaytimeserveripv4.o 
	gcc tcpdaytimeserveripv4.c -lm -g -o tcpdaytimeserveripv4

cleantcpdaytimeserveripv4:
	rm -f tcpdaytimeserveripv4.o tcpdaytimeserveripv4

showip:	showip.o 
	gcc showip.c -lm -g -o showip

cleanshowip:
	rm -f showip.o showip 
