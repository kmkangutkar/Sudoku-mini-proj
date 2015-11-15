/***************************************************************************
  SUDOKU - solver and generator
    Copyright (C) 2015 Komal Kangutkar
   
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
   
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
   
    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "functions.h"
#include "output.h"

/*for istack - stack of integers*/

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


/*for pstack - stack of integer stacks*/

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


/*for solve*/

int checker(int *c){
/*if a digit appears more than once in the array returns WRONG_IP else 0*/
	int i;
	for(i = 1; i < 10; i++){
		if(c[i] > 1){
			return WRONG_IP;
		}
	}
	return 0;
}

int* count_check(int num){
/*counts the number of times the digits appear and returns the array pointer*/
	int i;
	static int counter[10]/* = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}*/;
	if(num == -1){
		for(i = 0; i < 10; i++){
			counter[i] = 0;
		}
	}
	else{
		counter[num] = counter[num] + 1;
	}
	return &counter[0];
}

int get_random(int max, int excl){
/*returns a random number up to max excluding excl*/
	int x, y;
//	time_t t;
	again:
	x = rand();
	x = x % (max + 1);
	if(x == excl){
		goto again;
	}
	return x;
}

void empty_cell(int **p, int *i, int *j){
/*searches for the next empty cell*/	
	int a, b;
	int flag = 0;
	a = *i;
	b = *j;
	flag = 1;
	while(a < ROW){
		if(!flag)
			b = 0;
		while(b < COL){
			if(p[a][b] == EMPTY){
				*i = a;
				*j = b;
				f.found = 1;
				return;	
			}	
			b++;
			flag = 0;	
		}
		a = (a + 1) % ROW;
		if(a == *i)
			break;	
	
	}
	f.found = 0;
}

int* count(int num){
/*returns array that indicates the digits present*/
	int i;
	static int counter[10]/* = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}*/;
	if(num == -1){
		for(i = 0; i < 10; i++){
			counter[i] = 0;
		}
	}
	else{
		counter[num] = counter[num] + 1;
	}
	return &counter[0];
}
istack pos_val(int* arr){
/*stores the possible values at a position in an integer stack and returns the stack*/
	istack s, *p, t;
	int val, random;
	random = get_random(4, 0);
	i_init(&s);
	i_init(&t);
	int i;
	
	for(i = 9; i > 0; i--){
		if(arr[i] == 0){
			i_push(&s, i);
		}
	}
	p = &s;
	if(random % 2 == 1){
		while(!i_empty(p)){
			val = i_pop(p);
			i_push(&t, val);
		}
		return t;
	}
	else if(random % 2 == 0){
		return s;
	}
}


int check_ip(int **puz){
/*checks whether the given input in correct, column-wise and row-wise*/
	int *d, check, i, j, *c, num;
	d = count_check(-1);
	//check row-wise input
	for(i = 0; i < ROW; i++){
		for(j = 0; j < COL; j++){
			num = puz[i][j];
			d = count_check(num);
			check = checker(d);
			if(check == WRONG_IP){
				return WRONG_IP;
			}
		}
		d = count_check(-1);

	}
	//check col-wise input
	for(j = 0; j < COL; j++){
		for(i = 0; i < ROW; i++){
			d = count_check(puz[i][j]);
			check = checker(d);
			if(check == WRONG_IP){
				return WRONG_IP;
			}
		}
		d = count_check(-1);
	}

	return 0; //correct input
	
}
int* scan_block(int **puz, int row, int col, int w, int z){
/*scans the block and returns the pointer to the array indicating digits present*/
	int n, p, num, check;
	int *c, *d;
	d = count_check(-1);
	for(n = w; n < row; n++){
		for(p = z; p < col; p++){
			num = puz[n][p];
			c = count(num);	
			d = count_check(num);	
			check = checker(d);
			if(check == WRONG_IP){
				return NULL;
			}
		}
		d = count_check(-1);
	}
	return c;

}
int *scan(int **puz, int i, int j){
/*returns the pointer to the array that indicates all the digits present in the block, row, col of the element at (i, j)*/
	int *c, *d;
	c = count(-1);
	int n, p, num;
	int check;
	//scan row
	for(n = 0; n < COL; n++){
		num = puz[i][n];
		c = count(num);
	}
	d = count_check(-1);
	//scan column
	for(n = 0; n < ROW; n++){
		num = puz[n][j];
		count(num);

	}
	d = count_check(-1);	
	//scan block
	if(i < ROW/3){
		if(j < COL/3){
		//top left block
			c = scan_block(puz, ROW/3, COL/3, 0, 0);
			if(c == NULL) return NULL;
		}
		else if(j >= COL/3 && j < (2 * COL / 3)){
		//top middle block
			c = scan_block(puz, ROW/3, (2 * COL / 3), 0, COL/3);
			if(c == NULL) return NULL;
		}
		else if(j >= (2*COL/3) && j < COL){
		//top right block
			c = scan_block(puz, ROW/3, COL, 0, (2 * COL / 3));
			if(c == NULL) return NULL;
		}
	}
	if(i >= ROW/3 && i < (2*ROW/3)){
		if(j < COL/3){
		//top left block
			c = scan_block(puz, (2*ROW/3), COL/3, ROW/3, 0);
			if(c == NULL) return NULL;
		}
		else if(j >= COL/3 && j < (2 * COL / 3)){
		//top middle block
			c = scan_block(puz, (2*ROW/3), (2 * COL / 3), ROW/3, COL/3);
			if(c == NULL) return NULL;
		}
		else if(j >= (2*COL/3) && j < COL){
		//top right block
			c = scan_block(puz, (2*ROW/3), COL, ROW/3, (2 * COL / 3));
			if(c == NULL) return NULL;
		}
	}	
	if(i >= (2*ROW/3) && i < ROW){
		if(j < COL/3){
		//top left block
			c = scan_block(puz, ROW, COL/3, (2*ROW/3), 0);
			if(c == NULL) return NULL;
		}
		else if(j >= COL/3 && j < (2 * COL / 3)){
		//top middle block
			c = scan_block(puz, ROW, (2 * COL / 3), (2*ROW/3), COL/3);
			if(c == NULL) return NULL;
		}
		else if(j >= (2*COL/3) && j < COL){
		//top right block
			c = scan_block(puz, ROW, COL, (2*ROW/3), (2 * COL / 3));
			if(c == NULL) return NULL;
		}
	}
	

	return c;
	
}
void traverse_line(int *i, int *j){
/*traverses the array from left to right and from top to bottom*/
	if(*j == COL - 1){
		*i = (*i + 1) % ROW;
	}
	*j = (*j + 1) % COL;
}

void printpuz(int **puz){
/*print the sudoku 2d array*/
	int i, j;
	for(i = 0; i < ROW; i++){
		for(j = 0; j < COL; j++){
			printf("%d ", puz[i][j]);
		}	
		printf("\n");	
	}
}


int solve(int **puz, int *x, int *y, int display){
/*solves the given sudoku stored in puz, returns 1 if solve successful, returns WRONG_IP if i/p was invalid*/
	int *p, s = 0, count = 0, r, q;
	srand(time(NULL));
	int i, j, val;
	istack w;
	char c, chk;
	pstack POS;
	init(&POS);
	chk = check_ip(puz);
	if(chk == WRONG_IP){
		return WRONG_IP;
	}
	if(x == NULL){
		i = j = 0;
	}
	else{
		i = *x;
		j = *y;
	}
	while(i != ROW){
		empty_cell(puz, &i, &j);
		if(!f.found){
			if(display){
				display_puz(puz);
				refresh();
			}
			return 1;	
		}
		p = scan(puz, i, j);
		if(p == NULL){
			return WRONG_IP;	
		}
		w = pos_val(p);
		check:
		if(i_empty(&w)){
			/*no possible values*/
			if(!empty(&POS)){
				w = pop(&POS);
				puz[i][j] = EMPTY;
				if(display){
					display_puz(puz);
					refresh();
				}	
				count--;
				i = cell[count].x;
				j = cell[count].y;
				goto check;
			}	
		}
		else if(!i_empty(&w)){
			val = i_pop(&w);
			push(&POS, w);
			cell[count].x = i;
			cell[count].y = j;
			count++;
		}
		puz[i][j] = val;
		if(display){
			display_puz(puz);
			refresh();
		}
		traverse_line(&i, &j);
	}
	f.flag = 0;
	return 1;
}


/*for generate*/

void puz_init(int **puz){
/*sets all the cells empty */
	int i, j;
	for(i = 0; i < ROW; i++){
		for(j = 0; j < COL; j++){
			puz[i][j] = EMPTY;	
		}
	}
}



void set_one(int **puz){
/*sets one random value, at one random position*/
	srand(time(NULL));
	int i, j, val;
	val = get_random(9, 0);
	i = get_random(8, -1);
	j = get_random(8, -1);
	puz[i][j] = val;
	return;
}

void set_three(int **puz){
/*sets three random values, at three random positons*/
	srand(time(NULL));
	int i, j, val[3], p;
	val[0] = get_random(9, 0);
	again2:
	val[1] = get_random(9, 0);
	if(val[0] == val[1]){
		goto again2;
	}
	again3:
	val[2] = get_random(9, 0);
	if(val[0] == val[2] || val[1] == val[2]){
		goto again3;
	}
	for(p = 0; p < 3; p++){
		i = get_random(8, -1);
		again:
		j = get_random(8, -1);
		puz[i][j] = val[p];
	}
	return;
}

void mutual_exchange_digits(int **puz){
/*exchanges the positon of 2 digits in a row*/
	srand(time(NULL));
	int x, y, temp, i, j, flag = 0;
	x = get_random(9, 0);
	again:
	y = get_random(9, 0);
	if(x == y){
		goto again;	
	}
	for(i = 0; i < ROW; i++){
		flag = 0;
		while(flag != 2){
			for(j = 0; j < COL; j++){
				if(puz[i][j] == x){
					box[0].x = i;
					box[0].y = j;
					flag++;
				}		
				if(puz[i][j] == y){
					box[1].x = i;
					box[1].y = j;
					flag++;
				}
			}
		}
		temp = puz[box[0].x][box[0].y];
		puz[box[0].x][box[0].y] = puz[box[1].x][box[1].y];
		puz[box[1].x][box[1].y] = temp;
	}
}


void set_position(int *x, int *y){
/*randomly sets x and y*/
	*x = get_random(ROW - 1, -1);
	*y = get_random(COL - 1, -1);	
	return;
}



int check_row(int **puz, int x, int lim){
/*checks row condition, returns 1 if satisfied, 0 if not*/	
	int y, v, sum = 0;
	for(y = 0; y < COL; y++){
		if(puz[x][y])
			sum++;	
	}
	if(sum >= lim)
		v = 1;
	return v;
}

int check_col(int **puz, int y, int lim){
/*checks col condition, returns 1 if satisfied, 0 if not*/
	int x, sum = 0, v = 0;
	for(x = 0; x < COL; x++){
		if(puz[x][y])
			sum++;	
	}
	if(sum >= lim)
		v = 1;
	return v;
}

void dig(int **puz, int x, int y, int emp_lim, int rc_lim){
/*randomly empties positions of a completed sudoku to generate a new puzzle, according to the limits passed*/	
	int g = 0, v, s;	
	srand(time(NULL));
	while(g <= emp_lim){
		if(puz[x][y]){
			if((v = check_row(puz, x, rc_lim)) && (s = check_col(puz, y, rc_lim))){
				g++;
				puz[x][y] = EMPTY;
			}
		}
		set_position(&x, &y);
	}	
	return;
}

int** generate(int **puz, int level){
/*generates a new puzzle and returns its solution*/
	int opt, x, y, i, j;
	int **soln;
	soln = (int **)malloc(sizeof(int*) * ROW);
        for(i = 0; i < ROW; i++){
                soln[i] = (int *)malloc(sizeof(int) * COL);
        }
	srand(time(NULL));
	opt = get_random(3, 0);
	if(opt == 1){
		set_one(puz);
		set_position(&x, &y);
		solve(puz, &x, &y, 0);
	}
	else if(opt == 2){
		set_three(puz);
		set_position(&x, &y);
		solve(puz, &x, &y, 0);
	}
	else if(opt == 3){
		set_position(&x, &y);
		solve(puz, &x, &y, 0);
	}
	mutual_exchange_digits(puz);
	for(i = 0; i < ROW; i++)
		for(j = 0; j < COL; j++)
			soln[i][j] = puz[i][j];
	set_position(&x, &y);
	if(level == EASY)
		dig(puz, x, y, E_EMP_LIM, E_RC_LIM);
	else if(level == MED)
		dig(puz, x, y, M_EMP_LIM, M_RC_LIM);
	else if(level == DIF)
		dig(puz, x, y, H_EMP_LIM, H_RC_LIM);
	return soln;
}
