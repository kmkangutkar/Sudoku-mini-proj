TITLE: SUDOKU SOLVER AND GENERATOR

NAME: KOMAL M KANGUTKAR

MISID: 111403020


For storing the puzzle data, a dynamically allocated 2D array is used.
A stack of integer stacks is used to keep track of the possible values at the positions and so it can backtrack when needed.
<ncurses> library is used for the graphical interface of this game. 

This game has the following features:
	- Generate a sudoku for the user to solve of desired level (easy, medium ,difficult).
	- Provide a hint at a position if the user is stuck while solving the sudoku.
	- Solve the puzzle (entire or remaining part) using brute force technique.
	  It also displays graphically how the solver solves the sudoku.
	- User can input a sudoku for the program to solve. The given sudoku's validity is checked before proceeding to solve it. 
