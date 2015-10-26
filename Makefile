project: generate1.o istack.o pstack2.o
	cc generate1.o istack.o pstack2.o -o project
generate1.o : generate1.c pstack2.h
	cc -c generate1.c
istack.o: istack.c istack.h
	cc -c istack.c
pstack2.o: pstack2.c pstack2.h
	cc -c pstack2.c
run: 
	cat 4x4.txt | ./project
run1: 
	cat expml5.txt | ./project
