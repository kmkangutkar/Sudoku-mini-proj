project: 9x9works.o istack.o pstack2.o
	cc 9x9works.o istack.o pstack2.o -o project
9x9works.o : 9x9works.c pstack2.h
	cc -c 9x9works.c
istack.o: istack.c istack.h
	cc -c istack.c
pstack2.o: pstack2.c pstack2.h
	cc -c pstack2.c
run: 
	cat 4x4.txt | ./project
run1: 
	cat expml5.txt | ./project
