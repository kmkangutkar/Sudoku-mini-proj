#include<stdio.h>
#include"pstack2.h"

void init(pstack *w){
	w->i = 0;	
}
void push(pstack *w, istack p){
	w->arr[w->i] = p;
	(w->i)++;
}
istack pop(pstack *w){
	istack s;
	(w->i)--;
	s = w->arr[w->i];
	return s;
}
int empty(pstack *w){
	return (w->i == 0);
}
int full(pstack *w){
	return (w->i == PSIZE);
}


