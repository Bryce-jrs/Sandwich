WIDTH ?= 40
HEIGHT ?= 30
CFLAGS = -c -Wall -Wextra -std=c99 -g3 -ggdb
SANDWICH_FLAGS = -DWIDTH=$(WIDTH) -DHEIGHT=$(HEIGHT)

CC=gcc

OBJ= queue.o rule.o world.o options.o processus.o

all :  project


project : project.o $(OBJ)
	$(CC)  $(^) -o $(@)

test: test.o $(OBJ)
	gcc test.o  $(OBJ) -o test 

test.o : tst/test.c src/test.h src/rule.h src/queue.h src/processus.h
	$(CC)  -I src $(CFLAGS) $(SANDWICH_FLAGS)  $(<)  -o test.o

project.o :  src/project.c  src/global.h src/world_extended.h src/options.h src/queue.h src/rule.h src/processus.h
	$(CC)  -I src $(CFLAGS) $(SANDWICH_FLAGS)  $(<)  

queue.o :  src/queue.c src/global.h src/queue.h
	$(CC)  -I src $(CFLAGS) $(SANDWICH_FLAGS) $(<)  

rule.o :  src/rule.c src/rule.h 
	$(CC)  -I src $(CFLAGS) $(SANDWICH_FLAGS) $(<) 

world.o :  src/world.c src/global.h src/world.h
	$(CC)  -I src $(CFLAGS) $(SANDWICH_FLAGS) $(<)  

options.o :  src/options.c src/options.h
	$(CC)  -I src $(CFLAGS) $(SANDWICH_FLAGS) $(<)

processus.o : src/processus.c src/global.h src/processus.h src/queue.h src/rule.h
	$(CC)  -I src $(CFLAGS) $(SANDWICH_FLAGS) $(<)


clean :
	 @rm -f project test queue.o rule.o world.o project.o test.o options.o processus.o 


