CC=g++ 
LD=ld
CCFLAGS= -O2 -lGL -lglut -lGLU
CFLAGS= -c
PROG= universe
OBJECTS= main.o

program: $(OBJECTS) # In order for program to be made, the OBJECTS targets must..
	$(CC) -g $(OBJECTS) $(CCFLAGS) -o $(PROG)

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

clean:
	rm -f *.o universe
