#include "istack.h"

void i_init (istack *s){
	s->i = 0;
}

void i_push(istack *s, int x){
	s->arr[s->i] = x;
	(s->i)++;
}

int i_pop(istack *s){
	int x;
	(s->i)--;
	x = s->arr[s->i];
	return x;
}
int i_empty(istack *s){
	if((s->i) == 0)
		return 1;
	else
		return 0;
}
int i_full(istack *s){
	if((s->i) == SIZE)
		return 1;
	else
		return 0;
}



	

