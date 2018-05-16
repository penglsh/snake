#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include "snake1.h"



/*input food	
WHILE not game over 
DO
        input movement
        CASE movement DO
        	'A': mvre to left; break;
        	'D': mavo to right; break;
        	'W': move to upside; break;
        	'S': move down; break;
        END CASE
        output the map
END WHILE
output Game Over
ELSE
output WIN
*/

int main() {
	char movement = ' ';
	char anti_move = 'A';

	output();
	//snake position: 0 = snake_move_dy, 1 = snake_move_dx, -1 = dead, -2 = win
	while(snake_position >= 0)	{
		scanf(" %c", &movement);
		
		if(movement == anti_move)	{
			output();
			continue;
		}

		//snake stepping: dy = -1(up),1(down); dx = -1(left),1(right),0 (no move)
		//snake position: 0 = snake_move_dy, 1 = snake_move_dx, -1 = dead
		
		//snake_move(move_num, &snake_position);
		switch (movement)	{
			case 'W':
					anti_move = 'S';
					snake_position = 1;
					snake_move(-1, &snake_position);
					break;
			case 'S':
					anti_move = 'W';
					snake_position = 1;
					snake_move(1, &snake_position);
					break;
			case 'A':
					anti_move = 'D';
					snake_position = 0;
					snake_move(-1, &snake_position);
					break;
			case 'D':
					anti_move = 'A';
					snake_position = 0;
					snake_move(1, &snake_position);
					break;
			}

		output();
	}

	if(snake_position == -1)
		gameover();
	//if(snake_position == -2)
		//printf("Congratulations!! You Win!!!\n\n");
	return 0;
}


/*Snake | Head on Wall & Body
actions:dead 
Snake | Head on Blank
actions:move
Snake | Head on Food
actions:move and grows*/

//snake stepping: dy = -1(up), 1(down); dx = -1(left), 1(right), 0 (no move)
//snake position: 0 = snake_move_dy, 1 = snake_move_dx, -1 = dead, -2 = win
void snake_move(int step,int *position)	{
	//get the original location of the snake head
	int Hx = snakeX[snake_length-1], Hy=snakeY[snake_length-1];
	//get the original location of the snake body
	int bx = snakeX[snake_length-2], by=snakeY[snake_length-2];
	//grow: 0 = snake don't eat the food; 1 = snake has eaten the food
	int grow = 0;
	//snake_dx
	if(*position == 0)	{
		snakeY[snake_length-1] += step;
		//when snake meet with Wall or body or obstacles
		if(map[(snakeX[snake_length-1])][(snakeY[snake_length-1])] == WALL_CELL
			|| map[(snakeX[snake_length-1])][(snakeY[snake_length-1])] == SNAKE_BODY
			|| map[(snakeX[snake_length-1])][(snakeY[snake_length-1])] == OBSTACLE )	{

			*position=-1;
			return;
		}

		else	{
			//see whether the snake has eaten the food
			if(map[(snakeX[snake_length-1])][(snakeY[snake_length-1])] == SNAKE_FOOD)
				grow = 1;
			//move the snake on the map
			map[(snakeX[snake_length-1])][(snakeY[snake_length-1])] = SNAKE_HEAD;
			map[snakeX[0]][snakeY[0]] = BLANK_CELL;
			//get the location of the snake after move
			for(int i = snake_length-2; i >= 0; i --)	{
				map[Hx][Hy] = SNAKE_BODY;
				bx = snakeX[i];
				by = snakeY[i];
				snakeX[i] = Hx;
				snakeY[i] = Hy;
				Hx = bx;
				Hy = by;
			}
			//see whether the snake grows
			if(grow == 1)	{
				//grow
				snake_length ++;
				if(snake_length >= 20)	{
					*position = -2;
					return;
				}
				//remark the location of snake
				for(int i = snake_length; i > 0; i--)	{
					snakeX[i] = snakeX[i-1];
					snakeY[i] = snakeY[i-1];
				}
				snakeX[0] = bx;
				snakeY[0] = by;
				map[(snakeX[0])][(snakeY[0])] = SNAKE_BODY;
				grow = 0;
				//after eating the food, we should put another food on the map
				//put_food();
			}
		}
	}
	//snake_dy
	if(*position == 1)	{
		snakeX[snake_length-1] += step;
		//when snake meet with Wall or body
		if(map[(snakeX[snake_length-1])][(snakeY[snake_length-1])] == WALL_CELL
			|| map[(snakeX[snake_length-1])][(snakeY[snake_length-1])] == SNAKE_BODY)	{
			*position = -1;
			return;
		}

		else	{
			//see whether the snake has eaten the food
			if(map[(snakeX[snake_length-1])][(snakeY[snake_length-1])] == SNAKE_FOOD)
				grow = 1;
			//move the snake on the map
			map[(snakeX[snake_length-1])][(snakeY[snake_length-1])] = SNAKE_HEAD;
			map[snakeX[0]][snakeY[0]] = BLANK_CELL;
			map[Hx][Hy] = SNAKE_BODY;
			//get the location of the snake after move
			for(int i = snake_length-2; i>=0; i--)	{
				map[Hx][Hy] = SNAKE_BODY;
				bx = snakeX[i];
				by = snakeY[i];
				snakeX[i] = Hx;
				snakeY[i] = Hy;
				Hx = bx;
				Hy = by;
			}
			//see whether the snake grows
			if(grow == 1)	{
				//grow
				snake_length ++;
				if(snake_length >= 20)	{
					*position = -2;
					return;
				}
				//remark the location of snake
				for(int i = snake_length; i>0; i--)	{
					snakeX[i] = snakeX[i-1];
					snakeY[i] = snakeY[i-1];
				}
				snakeX[0] = bx;
				snakeY[0] = by;
				map[(snakeX[0])][(snakeY[0])] = SNAKE_BODY;
				grow = 0;
				//put_food();
			}
		}
	}
}

//output the map
/*
	clear the screen

	FOR
		FOR
			print every character
		END INSIDE FOR
		print "\n"
	END OUTSIDE FOR
*/
void output(void) {
	int x = 0,y = 0;
	//to clear
	//system("cls");
	printf ("\033[2J");

	for (x = 0; x < 12; x ++) {
		for ( y = 0; y < 12; y ++) {
			printf ("%c", map[x][y]);
		}
		printf ("\n");
	}
}

//outs when gameover
/*
	print GAME OVER!
	print others
*/
void gameover(void)	{

	printf ("GAME OVER!\n");
	printf ("You'd better be more careful!!!\n\n");

}