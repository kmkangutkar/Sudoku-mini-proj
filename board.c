#include<ncurses.h>

void print_board(void){
//printBoard function
	int x, y;
	int i;
	int flag = 0;
	attron(A_BOLD);
	mvprintw(5, 60, "SUDOKU");
	mvprintw(8, 60, "OPTIONS:");

	start_color();
	init_pair(1, COLOR_BLUE, COLOR_BLACK);
	init_pair(2, COLOR_YELLOW, COLOR_BLACK);
/*	attron(COLOR_PAIR(2));
	for(y = 0; y < 46; y++){
		mvaddch(0, y, '-');
	}
*/	attron(COLOR_PAIR(1));
	for(i = 1; i < 19; i+=2){
		for(x = 10; x < 56; x+=5){
			if(x == 10 || x == 25 || x == 40 || x == 55){
				attron(COLOR_PAIR(2));
				flag = 1;	
			}	
			mvaddch(i, x, '|');
			attron(COLOR_PAIR(1));	
		}
		for(x = 10; x < 56; x++){
			if(i == 1 || i == 7 || i == 13 || i == 19){
				attron(COLOR_PAIR(2));
			}
			mvaddch(i-1, x, '-');	
			attron(COLOR_PAIR(1));	
		}
			
	}
	attron(COLOR_PAIR(2));
	for(y = 10; y < 56; y++){
		mvaddch(i-1, y, '-');
	}
	attroff(COLOR_PAIR(1));
	attroff(COLOR_PAIR(2));
//	raw();
/*	printw("hello world\nhow are you?\n");
	mvprintw(20, 20, "Is this the middle?");
*/	return ;
}

int main(){
	initscr();
	cbreak();
	
	print_board();
	
	getch();
	endwin();
	
	}
