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

typedef struct sudoku{
	int**puz;
	int ROW, COL;
}sudoku;


/*for istack*/ 

#define SIZE 128
typedef struct istack{
	int i;
	int arr[SIZE];
}istack;

void i_init(istack *s);
void i_push(istack *s, int x);
int i_pop(istack *s);
int i_empty(istack *s);
int i_full(istack *s);


/*for pstack*/

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

void initialize(int **puz);

/*for solve*/
#define EMPTY 0
#define ROW 9
#define COL 9
#define CLASH 1
#define WRONG_IP 43
int get_random(int max, int excl);
struct k{
	int found;
	int flag;
}f;
int checker(int *c);
int* count_check(int num);
void empty_cell(int **p, int *i, int *j);
int* count(int num);
istack pos_val(int* arr);
int *scan(int **puz, int i, int j);
void traverse_line(int *i, int *j);
void printpuz(int **puz);

struct position{
	int x, y;
}cell[ROW * COL];

int solve(int **puz, int *x, int *y, int);

/*for generate*/
#define E_EMP_LIM 36
#define E_RC_LIM 4
#define M_EMP_LIM 45
#define M_RC_LIM 3
#define H_EMP_LIM 52
#define H_RC_LIM 2
enum levels{EASY, MED, DIF};
void puz_init(int **puz);
void set_one(int **puz);
void set_three(int **puz);

struct place{
	int x, y;
}box[2];

void mutual_exchange_digits(int **puz);
void set_position(int *x, int *y);
int** generate(int **puz, int);
int check_count(int *c, int lim);
int check_row(int **, int, int);
int check_col(int **, int, int);
void dig(int **puz, int x, int y, int emp_lim, int rc_lim);



