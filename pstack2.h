#include"istack.h"
#define PSIZE 81
typedef struct pstack{
	istack arr[PSIZE];
	int i;	
}pstack;

void init(pstack *w);
void push(pstack *w, istack p);
istack pop(pstack *w);
int empty(pstack *w);
int full(pstack *w);


