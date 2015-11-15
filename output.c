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

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "output.h"

void keytable(void){
/*prints the table in the window*/
	int i;
	init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
	attron(COLOR_PAIR(6));
	for(i = 2; i < 25; i++){
		mvaddch(4, i, '-');
		mvaddch(19, i, '-');
	}
	for(i = 4; i < 20; i++){
		mvaddch(i, 2, '|');
		mvaddch(i, 24, '|');
	}
	mvprintw(11, 5, "MOVE : a, s, d, w");
	mvprintw(13, 5, "Spacebar to enter");
	mvprintw(14, 5, "number");
	mvprintw(5, 5, "NEW : ESC + n");
	mvprintw(7, 5, "SOLVE : ESC + s");
	mvprintw(9, 5, "HINT : ESC + h");
	mvprintw(18, 5, "QUIT : ESC + q");
	mvprintw(16, 5, "GIVE I/P : ESC + i");
}
void print_board(void){
/*prints the board*/
	int x, y;
	int i;
	int flag = 0;
	attron(A_BOLD | A_UNDERLINE);
	mvprintw(1.5, 40, "SUDOKU SOLVER AND GENERATOR");
	attroff(A_UNDERLINE);
	mvprintw(5, 80, "MOVES : ");
	keytable();
	init_pair(1, COLOR_BLUE, COLOR_BLACK);
	init_pair(2, COLOR_YELLOW, COLOR_BLACK);
	attron(COLOR_PAIR(1));
	for(i = 4; i < 22; i+=2){
		for(x = 30; x < 76; x+=5){
			if(x == 30 || x == 45 || x == 60 || x == 75){
				attron(COLOR_PAIR(2));
				flag = 1;	
			}	
			mvaddch(i, x, '|');
			attron(COLOR_PAIR(1));	
		}
		for(x = 30; x < 76; x++){
			if(i == 4 || i == 10 || i == 16 || i == 22){
				attron(COLOR_PAIR(2));
			}
			mvaddch(i-1, x, '-');	
			attron(COLOR_PAIR(1));	
		}
			
	}
	attron(COLOR_PAIR(2));
	for(y = 30; y < 76; y++){
		mvaddch(i-1, y, '-');
	}
	attroff(COLOR_PAIR(1));
	attroff(COLOR_PAIR(2));
	move(4, 33);
	return ;
}

/*
y = 3 5 7 9 11 13 15 17 19 21 --- lines here
  = 4 6 8 10 12 14 16 18 20 --- blank spots
x = 33 38 43 48 53 58 63 68 73 --- blank spots
*/

void display_puz(int **puz){
/*displays the sudoku in the board printed in the window*/
	int i, j, x, y;
	init_pair(3, COLOR_RED, COLOR_BLACK);
	init_pair(4, COLOR_WHITE, COLOR_BLACK);
	attron(COLOR_PAIR(4));
	x = 33;
	y = 4;
	move(y, x);
	for(i = 0; i < ROW; i++){
		for(j = 0; j < COL; j++){
			if(puz[i][j]){
				mvprintw(y, x, "%d", puz[i][j]);
			}
			else{
				attron(COLOR_PAIR(3));
				mvprintw(y, x, "%c", ' ');	
			}
			if(j == COL - 1){
				y = y + 2;
				x = 33;
			}
			else{
				x = x + 5;
			}
			attron(COLOR_PAIR(4));
		}
	}
	usleep(10000);
	move(4, 33);
	return;	
}

void init_curses(void){
/*basic ncurses initialization functions*/
	initscr();
	cbreak();
	noecho();
	start_color();
	keypad(stdscr, TRUE);
	return;	
}

void print_digit(char ip){
/*prints ip at current cursor position*/
	int x, y;
	init_pair(5, COLOR_GREEN, COLOR_BLACK);
	attron(COLOR_PAIR(5));
	if(ip >= '0' && ip <= '9'){
		getyx(stdscr, y, x);
		mvprintw(y, x, "%c", ip);
	}
	attroff(COLOR_PAIR(5));
	move(y, x);
}



/*
y = 3 5 7 9 11 13 15 17 19 21 --- lines here
  = 4 6 8 10 12 14 16 18 20 --- blank spots
x = 33 38 43 48 53 58 63 68 73 --- blank spots
*/


void position(int *q, int *p){
/*gets current cursor position*/
	getyx(stdscr, *q, *p);
	return;
}

void user_input(int *i, int *j, char ip){
/*moves the cursor according to ip and moves within the 2d array accordingly*/
	int x, y;
	getyx(stdscr, y, x);
	switch(ip){
	//up
		case 'w':
			if(y != 4 && y < 21){
				move(y - 2, x);
				*i = *i - 1;
			}
			break;
	//down
		case 's':
			if(y != 20 && y > 3){
				move(y + 2, x);
				 *i = *i + 1;
			}
			break;
	//right
		case 'd':
			if(x != 73 && x > 32){
				move(y, x + 5);
				*j = *j + 1;
			}
			break;
	//left
		case 'a':
			if(x != 33 && x < 74){
				move(y, x - 5);
				*j = *j - 1;
			}
			break;
		default:
			break;
	}
	return;
}

int moves(int curr_moves){
/*calculates the score using no. of moves and num i/p and displays */
	curr_moves = curr_moves - 1; 
	int x, y;
	getyx(stdscr, y, x);
	mvprintw(5, 88, "%d\t\t", curr_moves);
	move(y, x);
	return curr_moves;
}
