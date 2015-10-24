#include<stdio.h>
#include<stdlib.h>
#include"pstack2.h"
#define ROW 4
#define COL 4
#define CLASH 1
int found = 0;
void empty_cell(int **p, int *i, int *j){
	int a, b;
	int **k;
	int n = 0;
	a = *i;
	b = *j;
	printf("%d %d\n", a, b);
	while(a < ROW){
//	for(; a < ROW; a++){
//		printf("IN WHILE ROW\n");
		b = 0;
		while(b < COL){
//			printf("IN WHILE COL\n");
			if(p[a][b] == 0){
				printf("found zero\n");
				*i = a;
				*j = b;
				found = 1;
				return;	
			}	
			b++;	
		}
		a++;	
	}
	found = 0;
	
}

int* count(int num){
	int i;
	static int counter[5] = {0, 0, 0, 0, 0};
	if(num == -1){
		for(i = 0; i < 5; i++){
			counter[i] = 0;
		}
	}
	else{
		counter[num] = counter[num] + 1;
//		printf("Counter: ");
//		for(i = 0; i < 5; i++){
//			printf("%d ", counter[i]);
//		}
//		printf("\n");
	}
	return &counter[0];
}
int flag = 0;
istack pos_val(int* arr){
	istack s, *p, t;
	int val;
	i_init(&s);
	i_init(&t);
	int i;
	flag = 0;
	for(i = 4; i > 0; i--){
		if(arr[i] == 0){
			i_push(&s, i);	
			flag = 1;
		}	
	}
	p = &s;
	printf("Possible values: ");
	if(i_empty(p)){
		printf("Empty\n");
	}
	while(!i_empty(p)){
		val = i_pop(p);
		printf("%d ", val);
		i_push(&t, val);
	}
	printf("\n");
//	p = &t;
//	return p;
	return t;
}

int *scan(int **puz, int i, int j){
	int *c;
	c = count(-1);
	int n, p, a = 0, num;
	int arr[COL];
	
	//scan row
	for(n = 0; n < COL; n++){
		num = arr[a++] = puz[i][n];
		count(num);
	}
	printf("scanROW\n");
	for(n = 0; n < COL; n++){
		printf("%d ", arr[n]);
	}
	printf("\n");
	
	//scan column
	a = 0;
	for(n = 0; n < ROW; n++){
		num = arr[a++] = puz[n][j];
		count(num);
	}
	printf("scanCOL\n");
	for(n = 0; n < ROW; n++){
		printf("%d ", arr[n]);
	}
	printf("\n");
	
	//scan block
	a = 0;
	//first decide which block, then how to access each element//
	if(i < ROW/2){
		if(j < COL/2){
			//in top left block
			for(n = 0; n < ROW/2; n++){
				for(p = 0; p < COL/2; p++){
					num = arr[a++] = puz[n][p];
					c = count(num);	
				}
			}		
		}
		else if(j >= COL/2){
			//in top right block
			for(n = 0; n < ROW/2; n++){
				for(p = COL/2; p < COL; p++){	
					num = arr[a++] = puz[n][p];
					c = count(num);	
				}
			}	
		}	
	}	

	if(i >= ROW/2){
		if(j < COL/2){
			//in top left block
			for(n = ROW/2; n < ROW; n++){
				for(p = 0; p < COL/2; p++){
		 			num = arr[a++] = puz[n][p];
					c = count(num);	
				}
			}		
		}
		else if(j >= COL/2){
			//in top right block
			for(n = ROW/2; n < ROW; n++){
				for(p = COL/2; p < COL; p++){	
					num = arr[a++] = puz[n][p];
					c = count(num);	
				}
			}	
		}	
	}	
	printf("scanBLOCK\n");
	for(n = 0; n < ROW; n++){
		printf("%d ", arr[n]);
	}
	printf("\n");
	return c;
	
}
	
int clash(int **puz, int i, int j, int val){
//returns CLASH = 1 if value clashes, else 0
	int x = i;
	int y = j;
	int n, p;
	//check row
	for(n = 0; n < COL; n++){
		if(n == j)
			continue;	
		if(puz[i][n] == val){
			return CLASH;		
		}
	}
	//check column
	for(n = 0; n < ROW; n++){
		if(n == i)
			continue;	
		if(puz[n][j] == val){
			return CLASH;		
		}
	}
	//check block
	if(i < ROW/2){
		if(j < COL/2){
			//in top left block
			for(n = 0; n < ROW/2; n++){
				for(p = 0; p < COL/2; p++){
					if(n == i && p == j){
						continue;
					}
					if(puz[n][p] == val){
						return CLASH;	
					}
				}
			}
		}		

		else if(j >= COL/2){
			//in top right block
			for(n = 0; n < ROW/2; n++){
				for(p = COL/2; p < COL; p++){	
					if(n == i && p == j){
						continue;
					}
					if(puz[n][p] == val){
						return CLASH;	
					}
				}
			}	
		}	
	}

	if(i >= ROW/2){
		if(j < COL/2){
			//in top left block
			for(n = ROW/2; n < ROW; n++){
				for(p = 0; p < COL/2; p++){
					if(n == i && p == j){
						continue;
					}
					if(puz[n][p] == val){
						return CLASH;	
					}
				}
			}		
		}
		else if(j >= COL/2){
			//in top right block
			for(n = ROW/2; n < ROW; n++){
				for(p = COL/2; p < COL; p++){	
					if(n == i && p == j){
						continue;
					}
					if(puz[n][p] == val){
						return CLASH;	
					}
				}
			}	
		}	
	}	
	return 0;
}

void printpstack(pstack *s){
	istack w, t;
	pstack z;
	int r;
	i_init(&t);
	init(&z);
	while(!empty(s)){
		w = pop(s);
		printf("In stack: ");
		while(!i_empty(&w)){
			r = i_pop(&w);
//			printf("Here");
			printf("%d ", r);
			i_push(&t, r);	
		}	
		printf("\n");
		push(&z, t);
	}	
	while(!empty(&z)){
		push(s, pop(&z));
	}
	return;
}

void printpuz(int **puz){
	int i, j;
	for(i = 0; i < ROW; i++){
		for(j = 0; j < COL; j++){
			printf("%d ", puz[i][j]);
		}	
		printf("\n");	
	}
}
struct position{
	int x, y;
}cell[16];

int main(){
	int **puz;
	int *p, s, count = 0;
	int i, j, val, val1;
	istack w, t;
	char c;
	pstack POS;
	init(&POS);

// 0 denotes an empty cell

/*Taking puzzle input*/
	puz = (int **)malloc(sizeof(int*) * ROW);
	for(i = 0; i < ROW; i++){
		puz[i] = (int *)malloc(sizeof(int) * COL);
	}		
	for(i = 0; i < ROW; i++){
		for(j = 0; j < COL; j++){
			scanf("%d", &puz[i][j]);
		}	
	}
/*printing puzzle input*/	
	printpuz(puz);
	//set to top left corner
	i = j = 0;
	while(i != 4){
		empty_cell(puz, &i, &j);
		if(!found){
			printpuz(puz);
			return 0;	
		}
		printf("zero at %d %d\n", cell[count - 1].x, cell[count - 1].y);
		p = scan(puz, i, j);
		w = pos_val(p);
		check:
		if(i_empty(&w)){
			printf("no possible values\n");
			//no possible values
			if(!empty(&POS)){
				printf("In here\n");
				w = pop(&POS);
				puz[i][j] = 0;
				printf("change back to %d\n", puz[i][j]);
				count--;
				printf("countback = %d\n", count);
				printpuz(puz);
				i = cell[count].x;
				j = cell[count].y;
				printf("go back to %d %d\n", i, j);
				goto check;
			}	
		}
		else if(!i_empty(&w)){
			val = i_pop(&w);
			printf("Val = %d\n", val);
			push(&POS, w);
			cell[count].x = i;
			cell[count].y = j;
			count++;
		//	w = pop(&POS);
			printf("Pstack: \n");
		//	printpstack(&POS);	
		}
		s = clash(puz, i, j, val);
		if(s == 0){
			puz[i][j] = val;
		}
		else{
			printf("clash\n");
			return 0;
			
		//	return 0;
		//	if(!i_empty(&w)){
		//		goto one;
		//	}
		//	else
		//		goto two;
		}
		if(j == 3){
			i++;	
		}
		j = (j + 1) % COL;
		printpuz(puz);
			
	}	
/*
*In a loop till bottom right corner is reached
*1 find zero store in positon structure
*2 scan the row, column, block and get possible values
*3 pop from pstack = val
*4 store in pstack
*5 check val for clash
	- no clash: put that val at that  position
	- clash:
		- not empty stack, pop stack = val, check for clash again
		- empty stack, change x and y to previous using position structure, pop from pstack and pop stack = val, check for clash again
*6 increment the cell and loop  
*/



























/*	while(i != 4 && j != 4){
		printf("i = %d j = %d\n", i, j);
		//find empty cell
		empty_cell(puz, &i, &j);
		printf("%d %d\n", i, j);
		cell[count].x = i;
		cell[count].y = j;
		count++;
		if(found == 0){
			printpuz(puz);
			return 0;
		}
		p = scan(puz, i, j);
		w = pos_val(p);
		push(&POS, w);
		again:
		w = pop(&POS);
		if(!i_empty(w)){
			val = i_pop(w);
		}
		else 
			goto again;
		//	w = pop(&POS);
		check:
		s = clash(puz, i, j, val);
		if(s == 0){
			printf("%d no clash\n", val);
			puz[i][j] = val;
			push(&POS, w);	
		}
		if(s == CLASH){
			printf("%d clash\n", val);
			if(!i_empty(w)){
				printf("stack not empty\n");
				val = i_pop(w);
				goto check;	
			}
			else{
				printf("stack empty\n");
				count--;
				i = cell[count].x;
				j = cell[count].y;
				goto again;	
			}
		}
		if(i == COL - 1){
			i++;
		}
		j = (j + 1) % COL;
	}
	printpuz(puz);
*/	return 0;
}

