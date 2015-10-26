#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include"pstack2.h"
#define ROW 9
#define COL 9
#define CLASH 1
int found = 0;
void empty_cell(int **p, int *i, int *j){
	int a, b;
	int **k;
	int n = 0;
	a = *i;
	b = *j;
//	printf("%d %d\n", a, b);
	while(a < ROW){
//	for(; a < ROW; a++){
//		printf("IN WHILE ROW\n");
		b = 0;
		while(b < COL){
//			printf("IN WHILE COL\n");
			if(p[a][b] == 0){
//				printf("found zero\n");
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
	static int counter[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	if(num == -1){
		for(i = 0; i < 10; i++){
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
istack pos_val(int* arr){
	istack s, *p, t;
	int val;
	i_init(&s);
	i_init(&t);
	int i;
	for(i = 9; i > 0; i--){
		if(arr[i] == 0){
			i_push(&s, i);
		}
	}
	p = &s;
/*	printf("Possible values: ");
	if(i_empty(p)){
		printf("Empty\n");
	}
	while(!i_empty(p)){
		val = i_pop(p);
		printf("%d ", val);
		i_push(&t, val);
	}
*///	printf("\n");
	//p = &t;
//	return t;
	return s;
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
//	printf("scanROW\n");
	for(n = 0; n < COL; n++){
//		printf("%d ", arr[n]);
	}
//	printf("\n");
	
	//scan column
	a = 0;
	for(n = 0; n < ROW; n++){
		num = arr[a++] = puz[n][j];
		count(num);
	}
//	printf("scanCOL\n");
	for(n = 0; n < ROW; n++){
//		printf("%d ", arr[n]);
	}
//	printf("\n");
	
	//scan block
	a = 0;
	//first decide which block, then how to access each element//
	if(i < ROW/3){
		if(j < COL/3){
			//in top left block
			for(n = 0; n < ROW/3; n++){
				for(p = 0; p < COL/3; p++){
					num = arr[a++] = puz[n][p];
					c = count(num);	
				}
			}		
		}
		else if(j >= COL/3 && j < (2 * COL / 3)){
			//in top middle block
			for(n = 0; n < ROW/3; n++){
				for(p = COL/3; p < (2 * COL / 3); p++){	
					num = arr[a++] = puz[n][p];
					c = count(num);	
				}
			}	
		}
		else if(j >= (2*COL/3) && j < COL){
			//in top right block
			for(n = 0; n < ROW/3; n++){
				for(p = (2*COL/3); p <  COL; p++){	
					num = arr[a++] = puz[n][p];
					c = count(num);	
				}
			}	
		}
			
	}	

	if(i >= ROW/3 && i < (2*ROW/3)){
		if(j < COL/3){
			//in middle left block
			for(n = ROW/3; n < (2*ROW/3); n++){
				for(p = 0; p < COL/3; p++){
		 			num = arr[a++] = puz[n][p];
					c = count(num);	
				}
			}
		}
		else if(j >= COL/3 && j < (2*COL/3)){
			//in middle middle block
			for(n = ROW/3; n < (2*ROW/3); n++){
				for(p = COL/3; p < (2 * COL / 3); p++){	
					num = arr[a++] = puz[n][p];
					c = count(num);	
				}
			}
		}
		else if(j >= (2*COL/3) && j < COL){
			//in middle right block
			for(n = ROW/3; n < (2*ROW/3); n++){
				for(p = (2*COL/3); p <  COL; p++){	
					num = arr[a++] = puz[n][p];
					c = count(num);	
				}
			}
		}
	}
	if(i >= (2*ROW/3) && i < ROW){
		if(j < COL/3){
			//in bottom left block
			for(n = (2*ROW/3); n < ROW; n++){
				for(p = 0; p < COL/3; p++){
		 			num = arr[a++] = puz[n][p];
					c = count(num);	
				}
			}
		}
		else if(j >= COL/3 && j < (2*COL/3)){
			//in bottom middle block
			for(n = (2*ROW/3); n < ROW; n++){
				for(p = COL/3; p < (2 * COL / 3); p++){	
					num = arr[a++] = puz[n][p];
					c = count(num);	
				}
			}
		}
		else if(j >= (2*COL/3) && j < COL){
			//in bottom right block
			for(n = (2*ROW/3); n < ROW; n++){
				for(p = (2*COL/3); p <  COL; p++){	
					num = arr[a++] = puz[n][p];
					c = count(num);	
				}
			}
		}
	}
//	printf("scanBLOCK\n");
	for(n = 0; n < ROW; n++){
//		printf("%d ", arr[n]);
	}
//	printf("\n");
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
			printf("row clash\n");
			return CLASH;
		}
	}
	//check column
	for(n = 0; n < ROW; n++){
		if(n == i)
			continue;
		if(puz[n][j] == val){
			printf("column clash\n");
			return CLASH;
		}
	}
	//check block
	//first decide which block, then how to access each element//
	if(i < ROW/3){
		if(j < COL/3){
			//in top left block
			for(n = 0; n < ROW/3; n++){
				for(p = 0; p < COL/3; p++){
					if(n == i && p == j){
						continue;
					}
					if(puz[n][p] == val){
						printf("1\n");
						return CLASH;
					}
				}
			}
		}

		else if(j >= COL/3 && j < (2 * COL / 3)){
			//in top middle block
			for(n = 0; n < ROW/3; n++){
				for(p = COL/3; p < (2 * COL / 3); p++){
					if(n == i && p == j){
						continue;
					}
					if(puz[n][p] == val){
						printf("2\n");
						return CLASH;
					}
				}
			}
		}
		else if(j >= (2*COL/3) && j < COL){
			//in top right block
			for(n = 0; n < ROW/3; n++){
				for(p = (2*COL/3); p <  COL; p++){	
					if(n == i && p == j){
						continue;
					}
					if(puz[n][p] == val){
						printf("3\n");
						return CLASH;
					}
				}
			}
		}
	}

	if(i >= ROW/3 && i < (2*ROW/3)){
		if(j < COL/3){
			//in middle left block
			for(n = ROW/3; n < (2*ROW/3); n++){
				for(p = 0; p < COL/3; p++){
		 			if(n == i && p == j){
						continue;
					}
					if(puz[n][p] == val){
						printf("4\n");
						return CLASH;
					}
				}
			}
		}

		else if(j >= COL/3 && j < (2*COL/3)){
			//in middle middle block
			for(n = ROW/3; n < (2*ROW/3); n++){
				for(p = COL/3; p < (2 * COL / 3); p++){	
					if(n == i && p == j){
						continue;
					}
					if(puz[n][p] == val){
						printf("5\n");
						return CLASH;	
					}
				}	
			}
		}	
		else if(j >= (2*COL/3) && j < COL){
			//in middle right block
			for(n = ROW/3; n < (2*ROW/3); n++){
				for(p = (2*COL/3); p <  COL; p++){	
					if(n == i && p == j){
						continue;
					}
					if(puz[n][p] == val){
						printf("6\n");
						return CLASH;		
					}
				}	
			}
		}
	}	
	if(i >= (2*ROW/3) && i < ROW){
		if(j < COL/3){
			//in bottom left block
			for(n = (2*ROW/3); n < ROW; n++){
				for(p = 0; p < COL/3; p++){
		 			if(n == i && p == j){
						continue;
					}
					if(puz[n][p] == val){
						printf("7\n");
						return CLASH;	
					}
				}		
			}
		}	
		else if(j >= COL/3 && j < (2*COL/3)){
			//in bottom middle block
			for(n = (2*ROW/3); n < ROW; n++){
				for(p = COL/3; p < (2 * COL / 3); p++){	
					if(n == i && p == j){
						continue;
					}
					if(puz[n][p] == val){
						printf("8\n");
						return CLASH;		
					}
				}	
			}
		}	
		else if(j >= (2*COL/3) && j < COL){
			//in bottom right block
			for(n = (2*ROW/3); n < ROW; n++){
				for(p = (2*COL/3); p <  COL; p++){	
					if(n == i && p == j){
						continue;
					}
					if(puz[n][p] == val){
						printf("9\n");
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
}cell[ROW * COL];

void solve(int **puz){
	int *p, s = 0, count = 0;
	int i, j, val, val1;
	istack w, t;
	char c;
	pstack POS;
	init(&POS);
/*printing puzzle input*/	
//	printpuz(puz);
	//set to top left corner
	i = j = 0;
	while(i != 9){
		empty_cell(puz, &i, &j);
		if(!found){
		//	printpuz(puz);
			return;	
		}
//		printf("zero at %d %d\n", i, j);
		p = scan(puz, i, j);
		w = pos_val(p);
		check:
		if(i_empty(&w)){
//			printf("no possible values\n");
			//no possible values
			if(!empty(&POS)){
//				printf("In here\n");
				w = pop(&POS);
				puz[i][j] = 0;
//				printf("change back to %d\n", puz[i][j]);
				count--;
//				printf("countback = %d\n", count);
			//	printpuz(puz);
				i = cell[count].x;
				j = cell[count].y;
//				printf("go back to %d %d\n", i, j);
				goto check;
			}	
		}
		else if(!i_empty(&w)){
			val = i_pop(&w);
//			printf("Count = %d Val = %d\n",count, val);
			push(&POS, w);
			cell[count].x = i;
			cell[count].y = j;
			count++;
		//	printf("Pstack: \n");
		//	printpstack(&POS);	
		}
		s = clash(puz, i, j, val);
		if(s == 0){
			puz[i][j] = val;
		}
		else{
//			printf("clash\n");
			return;
			
		}
		if(j == 8){
			i++;	
		}
		j = (j + 1) % COL;
//		printpuz(puz);
			
	}
	
	return;
}

void puz_init(int **puz){
	int i, j;
	for(i = 0; i < ROW; i++){
		for(j = 0; j < COL; j++){
			puz[i][j] = 0;	
		}
	}
}


int get_random(int max, int excl){
	int x, y;
	time_t t;
	again:
	x = rand();
	x = x % (max + 1);
	if(x == excl){
		goto again;
	}
	return x;
}

void set_one(int **puz){
	srand(time(NULL));
	int i, j, val;
	val = get_random(9, 0);
	i = get_random(8, -1);
	j = get_random(8, -1);
	printf("Random\nval = %d\ni = %d\nj = %d\n", val, i, j);
	puz[i][j] = val;
	return;
}

void set_three(int **puz){
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
	/*	if(i == j){
			goto again;
		}*/
		printf("i = %d, j = %d, val = %d", i, j, val[p]);
		puz[i][j] = val[p];
	}
	return;
}
struct place{
	int x, y;
}box[2];
void mutual_exchange_digits(int **puz){
	srand(time(NULL));
	int x, y, temp, i, j, flag = 0;
	x = get_random(9, 0);
	again:
	y = get_random(9, 0);
	if(x == y){
		goto again;	
	}
	printf("x = %d, y = %d\n", x, y);
	for(i = 0; i < ROW; i++){
		flag = 0;
		while(flag != 2){
			for(j = 0; j < COL; j++){
				if(puz[i][j] == x){
					box[0].x = i;
					box[0].y = j;
				//	printf("%d at %d %d\n", x, box[0].x, box[0].y);
					flag++;
				}		
				if(puz[i][j] == y){
					box[1].x = i;
					box[1].y = j;
				//	printf("%d at %d %d\n", y, box[1].x, box[1].y);
					flag++;
				}
			}	
		}
		temp = puz[box[0].x][box[0].y];
		puz[box[0].x][box[0].y] = puz[box[1].x][box[1].y];
		puz[box[1].x][box[1].y] = temp;
	}	
}

void generate(int **puz){
	int opt;
	srand(time(NULL));
	opt = get_random(2, 0);
	printf("opt = %d\n",opt);
	if(opt == 1){
		printf("1\n");
		set_one(puz);
		printpuz(puz);	
	}	
	else if(opt == 2){
		printf("2\n");
		set_three(puz);
		printpuz(puz);
	}
	solve(puz);
	printpuz(puz);
	mutual_exchange_digits(puz);
	return;
}

int main(){
	int **puz;
	int i;



// 0 denotes an empty cell

/*Taking puzzle input*/
	puz = (int **)malloc(sizeof(int*) * ROW);
	for(i = 0; i < ROW; i++){
		puz[i] = (int *)malloc(sizeof(int) * COL);
	}
	
	generate(puz);
	printf("randomly generated\n");
	printpuz(puz);
	return 0;
}


















/*			
	for(i = 0; i < ROW; i++){
		for(j = 0; j < COL; j++){
			scanf("%d", &puz[i][j]);
		}	
	}
*/

