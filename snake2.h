#ifndef SNAKE2_H
#define SNAKE2_H

#include <stdio.h>

#define SNAKE_MAX_LENGTH 20
#define SNAKE_HEAD 'H'
#define SNAKE_BODY 'X'
#define BLANK_CELL ' '
#define SNAKE_FOOD '$'
#define WALL_CELL '*'
#define OBSTACLE '#'

//snake position: 0 = snake_move_dy, 1 = snake_move_dx, -1 = dead, -2 = win
int snake_position = 0; 

//define vars for snake, notice name of vars in C
int snakeY[SNAKE_MAX_LENGTH]={1,2,3,4,5};
int snakeX[SNAKE_MAX_LENGTH]={1,1,1,1,1};
int snake_length = 5;

char map[12][13]=
	{"************",
	"*XXXXH     *",
	"*          *",
	"*          *",
	"*          *",
	"*          *",
	"*          *",
	"*          *",
	"*          *",
	"*          *",
	"*          *",
	"************"
	};
//move the snake: dy = -1(up), 1(down); dx = -1(left), 1(right), 0(no move)
void snake_move(int step,int *position);
//put food randomizedly on a blank cell
void put_food(void);
//output the map every movement
void output(void);
//output some obstacle(when the snake touch it, the snake dies.)
void put_obstacle(void);
//output when gameover
void gameover(void);

#endif