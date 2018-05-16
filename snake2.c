#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include "snake2.h"



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
	put_food();
	//put six obstacles on the map
	for (int i = 0; i < 6; i ++) {
		put_obstacle();
	}
	output();
	//snake position: 0 = snake_move_dy, 1 = snake_move_dx, -1 = dead, -2 = win
	while(snake_position >= 0)	{
		scanf(" %c", &movement);
		
		if(movement == anti_move)	{
			output();
			continue;
		}
		int flag = 0;
		if (movement == 'a' || movement == 'A') {
			flag = 1;
		}
		if (movement == 'd' || movement == 'D') {
			flag = 2;
		}
		if (movement == 'w' || movement == 'W') {
			flag = 3;
		}
		if (movement == 's' || movement == 'S') {
			flag = 4;
		}
		//snake stepping: dy = -1(up),1(down); dx = -1(left),1(right),0 (no move)
		//snake position: 0 = snake_move_dy, 1 = snake_move_dx, -1 = dead
		
		//snake_move(move_num, &snake_position);
		switch (flag)	{
			case 3:
					anti_move = 'S';
					snake_position = 1;
					snake_move(-1, &snake_position);
					break;
			case 4:
					anti_move = 'W';
					snake_position = 1;
					snake_move(1, &snake_position);
					break;
			case 1:
					anti_move = 'D';
					snake_position = 0;
					snake_move(-1, &snake_position);
					break;
			case 2:
					anti_move = 'A';
					snake_position = 0;
					snake_move(1, &snake_position);
					break;
			default : break;
			}

		output();
	}

	if(snake_position == -1)
		gameover();
	if(snake_position == -2)
		printf("Congratulations!! You Win!!!\n\n");
	return 0;
}


/*Snake | Head on Wall & Body
actions:dead 
Snake | Head on Blank
actions:move
Snake | Head on Food
actions:move and grows*/

//put food randomizedly on a blank cell
/*
	get the random number
	WHILE NOT GAME OVER 
	DO
		Get x;
		get y;
		IF condition
			DO not get food;
		END IF
		ELSE
			get food;
		END ELSE
	END WHILE
*/
void put_food(void)	{
	//food position: 0 = something are on the position of food; 1 = food is on the blank
	int food_position = 0;
	int x = -1, y = -1;
	//get the position of food
	srand((unsigned)time(NULL));
	while(x <= 0 || y <= 0 || food_position == 0)	{
		x = rand() % 12;
		y = rand() % 12;

	//	printf("food(%d,%d)\nHead(%d,%d)",x,y,snakeX[snake_length-1],snakeY[snake_length-1]);
		if(map[x][y] == SNAKE_HEAD || map[x][y] == SNAKE_BODY || map[x][y] == WALL_CELL)	{
			food_position = 0;
		}
		else	{
			food_position = 1;
			map[x][y] = SNAKE_FOOD;
			break;
		}
	}
}

//output some obstacle(when the snake touch it, the snake dies.)
/*
	get the random number
	WHILE NOT GAME OVER 
	DO
		Get x;
		get y;
		IF condition
			DO not get obtacles;
		END IF
		ELSE
			get obtacles;
		END ELSE
	END WHILE

*/
void put_obstacle(void){
	//to put the obstacles on the map: when the flag == 1, get it:
	int flag = 0;
	int x = -1, y = -1;
	//to get the random position of the obstacles:
	srand((unsigned)time(NULL));
	while (x <= 0 || y <= 0 || flag == 0) {
		x = rand() % 12;
		y = rand() % 12;
		//when the obstacles does not appear on the blank, try again
		if (map[x][y] == SNAKE_HEAD || map[x][y] == SNAKE_BODY || map[x][y] == WALL_CELL
			|| map[x][y] == SNAKE_FOOD || map[x][y] == OBSTACLE ) {

			flag = 0;
		}
		else {
			flag = 1;
			map[x][y] = OBSTACLE ;
			break;
		}
	}
}

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
				put_food();
			}
		}
	}
	//snake_dy
	if(*position == 1)	{
		snakeX[snake_length-1] += step;
		//when snake meet with Wall or body or obstacle
		if(map[(snakeX[snake_length-1])][(snakeY[snake_length-1])] == WALL_CELL
			|| map[(snakeX[snake_length-1])][(snakeY[snake_length-1])] == SNAKE_BODY
			|| map[(snakeX[snake_length-1])][(snakeY[snake_length-1])] == OBSTACLE)	{
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
				put_food();
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