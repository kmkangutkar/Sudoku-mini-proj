project: started2.o istack.o pstack2.o
	cc started2.o istack.o pstack2.o -o project
started2.o : started2.c pstack2.h
	cc -c started2.c
istack.o: istack.c istack.h
	cc -c istack.c
pstack2.o: pstack2.c pstack2.h
	cc -c pstack2.c
run: 
	cat 4x4.txt | ./project
run1: 
	cat expml5.txt | ./project
