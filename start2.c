#include<stdio.h>
#include<stdlib.h>
#include"pstack.h"
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

istack* pos_val(int* arr){
	istack s, *p;
	i_init(&s);
	int i;
	for(i = 1; i < 5; i++){
		if(arr[i] == 0){
			i_push(&s, i);	
		}	
	}
	p = &s;
	return p;
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
	int i, j, val;
	istack *w;
	pstack POS;
	init(&POS);

// 0 denotes an empty cell

/*Taking puzzle input*/
	puz = (int **)malloc(sizeof(int) * ROW);
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
	while(i != 4 && j != 4){
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
/*
	w = pos_val(p);
	push(&POS, w);
	w = pop(&POS);
	while(!i_empty(w)){
		num = i_pop(w);
		printf("%d\n", num);

	}	
	i_push(w, num);
	if(!i_empty(w)){
		num = i_pop(w);
		if(i_empty(w)){
			s = clash(puz, i, j, num);
			printf("s = %d\n", s);
			if(s == CLASH){
				printf("CLash\n");	
			}
			else
				puz[i][j] = num;	
		}
		else 
			i_push(w, num);	
	}

/*
* set position to the top left corner
* scan right till 0 is found
* at this position deduce the possible digits
* if the only possible digit is clashing, then go back to the previous 0 index and take the next possibility,
if this next possible digit also clashes and all possibilities of that position are over then go back to the previous 0 index
* deduce the possibilities by scanning the row, column and block of that index
* store these possibilities
* take the first and continue till next zero
* when end of the row is reached, go to the next row and continue as above
* when bottom right corner is reached, that means all the right digits have been chosen and the puzzle is solved
*/

/*
enter the possible values in a stack which is in a stack;
pop and use that as that cell's value;
continue to find next empty cell;
find possible values and add them in a stack to the stack of stack;
pop and use that as that cell's value;
if this value clashes with already filled in cells, pop from that stack and use this next value and continue;
if the next value also clashes with already filled cells, do the above again till no clashes;
if the stack is empty, pop that stack from the stack of stack and go to the previous empty cell and use the popped value as the new value and proceed again;
if that stack is also empty go to the previous cell and do the same;
*/
/*
- stack of stack pointers; how many?
- find empty cell and possible values function
- check for clashes function
*/

	return 0;
}

