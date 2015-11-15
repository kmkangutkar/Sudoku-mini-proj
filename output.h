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
#define ROW 9
#define COL 9

void init_curses(void);
void print_board(void);
void display_puz(int **puz);
void move_cursor(char ip);
void user_input(int*, int *, char);
void print_digit(char);
void position(int*, int*);
int score(int, int, int);
