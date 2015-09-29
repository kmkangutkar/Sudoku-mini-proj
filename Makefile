project: start1.o istack.o pstack.o
	cc start1.o istack.o pstack.o -o project
start1.o : start1.c pstack.h
	cc -c start1.c
istack.o: istack.c istack.h
	cc -c istack.c
pstack.o: pstack.c pstack.h
	cc - cpstack.c
