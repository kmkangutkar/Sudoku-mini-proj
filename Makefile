project: main.o functions.o output.o
	cc main.o functions.o output.o -o project -lncurses
main.o: functions.h output.h main.c 
	cc -c main.c
functions.o: functions.h output.h functions.c 
	cc -c functions.c
output.o: output.h output.c
	cc -c output.c
