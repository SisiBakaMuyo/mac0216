CC     = gcc
CFLAGS = -Wall -O -pedantic
LIBS = -lGL -lGLU -lglut -lm -lX11 -lXpm
OBJECTS = graphic.o orbit.o spaceLib.o xwc.o control.o

#------------------------------------------------

spaceWar: graphic.o orbit.o spaceLib.o xwc.o control.o
	$(CC) graphic.o orbit.o spaceLib.o xwc.o control.o -o spaceWar $(LIBS)	

graphic.o: graphic.c graphic.h xwc.h spaceLib.h
	$(CC) $(CFLAGS) -c graphic.c 

orbit.o: orbit.c graphic.h spaceLib.h
	$(CC) $(CFLAGS) -c orbit.c

spaceLib.o: spaceLib.c spaceLib.h graphic.h control.h
	$(CC) $(CFLAGS) -c spaceLib.c	

xwc.o: xwc.c xwc.h
	$(CC) $(CFLAGS) -c xwc.c

control.o: control.c control.h graphic.h 
	$(CC) $(CFLAGS) -c control.c	

clean :
	rm -rf  $(OBJECTS)

