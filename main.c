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
#define ESC 27

int main(){
	int **puz, **soln = NULL;
	int i, j, p, q, check;
	char ip, c, ch[3];
	int moves = 0;
	int curr_score = 10000;
	f.found = 0;
	f.flag = 0;
	puz = (int **)malloc(sizeof(int*) * ROW);
        for(i = 0; i < ROW; i++){
                puz[i] = (int *)malloc(sizeof(int) * COL);
        }
        puz_init(puz);
	init_curses();
	print_board();
	display_puz(puz);
	i = 0;
	j = 0;
	play:
	ip = getch();
	while(ip != ESC){
		switch(ip){
			case ' ':
				position(&q, &p);
                		mvprintw(15, 80, "INPUT MODE\t\t\t");
                		move(q, p);
			        ip = getch();
			        if(soln && !f.flag){
			        	if(soln[i][j] == atoi(&ip)){
						puz[i][j] = atoi(&ip);
						print_digit(ip);
						position(&q, &p);
						mvprintw(15, 80, "CORRECT!\t\t\t");
						move(q, p);
						moves++;
						curr_score = score(atoi(&ip), moves, curr_score);
					}
					else{ 
						position(&q, &p);
						mvprintw(15, 80, "INCORRECT!\t\t\t");
						move(q, p);
						moves++;
						curr_score = score(atoi(&ip), moves, curr_score);
					}
				}
				else if(!soln && f.flag){
					puz[i][j] = atoi(&ip);
					print_digit(ip);
				}
				break;
                	case 'a': case 's': case 'w': case 'd': 
                		user_input(&i, &j, ip);
                		position(&q, &p);
                		mvprintw(15, 80, "CURSOR MOVING..\t\t\t");
                		move(q, p);
                		p = i;
                		q = j;
                		empty_cell(puz, &p, &q);
                		if(!f.found){
                			position(&q, &p);
                			mvprintw(15, 80, "SUDOKU SOLVED!!\t\t\t");
                			move(q, p);
                			soln = NULL;
                			moves = 0;
                			curr_score = 10000;
                			score(0, 0, curr_score);
                		}
                		break;
                	default: 
                		break;
                
                
		}
		ip = getch();
	}
	esc_options:
	if(ip == ESC){
		position(&q, &p);
	        mvprintw(15, 80, "ESC mode\t\t\t");
        	move(q, p);
		ip = getch();
		switch(ip){
			case 'q': //quit
				endwin();
				return 0;
			case 's': //solve
				position(&q, &p);
                		mvprintw(15, 80, "SOLVING..\t\t\t");
                		move(q, p);
				check = solve(puz, NULL, NULL, 1);
				if(check == WRONG_IP){
					position(&q, &p);
	                		mvprintw(15, 80, "WRONG INPUT GIVEN\t\t\t");
	                		move(q, p);
				}
				else{
					position(&q, &p);
                			mvprintw(15, 80, "SUDOKU SOLVED!!\t\t\t");
                			move(q, p);
                			moves = 0;
                			soln = NULL;
                			curr_score = 10000;
                			score(0, 0, curr_score);
				}
				move(4,33);
				f.flag = 0;
		//		soln = NULL;
				goto play;
			case 'n': //new
				 puz_init(puz);
				 mvprintw(15, 80, "e: EASY m: MEDIUM d: DIFFICULT\t\t");
				 move(4, 33);
				 c = getch();
				 if(c == 'e'){
				 	soln = generate(puz, EASY);
				 	mvprintw(15, 80, "EASY\t\t\t\t");
				 	move(4, 33);
				 }
				 else if(c == 'm'){
				 	soln = generate(puz, MED);
				 	mvprintw(15, 80, "MEDIUM\t\t\t\t");
				 	move(4, 33);
				 	}
				 	else if(c == 'd'){
				 		soln = generate(puz, DIF);
				 		mvprintw(15, 80, "DIFFICULT\t\t\t\t");
						move(4, 33);
				 	}
				 display_puz(puz);
				 refresh();
				 i = j = 0;
				 goto play;
			case 'h': //hint
				if(soln){
					position(&q, &p);
                			mvprintw(15, 80, "HINT!\t\t\t");
                			move(q, p);
					puz[i][j] = soln[i][j];
					sprintf(ch, "%d", puz[i][j]);
					print_digit(ch[0]);
					moves += 2;
					curr_score = score(10, moves, curr_score);
				}
				goto play;
			case 'i'://input from user
				soln = NULL;
				puz_init(puz);
				display_puz(puz);
				position(&q, &p);
				mvprintw(15, 80, "INPUT SUDOKU PUZZLE\t\t");
				move(q, p);
				move(4,33);
				f.flag = 1;
				i = j = 0;
				goto play;	
			case 'p': //play
				goto play;
			default: 
				goto play;	
		}
	}
	end:
	getch();
	endwin();
	return 0;
}

