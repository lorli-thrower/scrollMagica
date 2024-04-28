#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Player.h"

#define BOARD_HIGHT 46
#define BOARD_WIDTH 213
//#define BOARD_HIGHT 73
//#define BOARD_WIDTH 273

#define CH_PLAYER		'@'

#define UP				'k' 
#define DOWN			'j' 
#define LEFT			'h' 
#define RIGHT			'l' 
#define UP_LEFT			'y' 
#define DOWN_LEFT		'b' 
#define UP_RIGHT		'u' 
#define DOWN_RIGHT		'n' 
#define NOT_MOVE		'.' 
#define CREATE_SCROLL	's' 
#define FIRE_SCROLL		'f' 
#define CHAIN_SCROLLS	'c'

#define SCROLL_BIG		'd'
#define SCROLL_MEDIUM	'f'
#define SCROLL_SMALL	'g'
#define SCROLL_FIRE		'r'

bool running = true;

void render(char **board, struct Player *player);
void processInputs(char *inputs, struct Player*);
void readLine(char* inputs, int length);

int main()
{
	struct Player player1;
	playerInventoryAllocate(&player1);
	player1.x = BOARD_WIDTH / 2;
	player1.y = BOARD_HIGHT / 2;
	char* inputs = malloc(sizeof(char) * 255);
	int length = 255;
	char **board = malloc(sizeof(char*) * BOARD_HIGHT);
	for (int i = 0; i < BOARD_HIGHT; i++)
		board[i] = malloc(sizeof(char) * BOARD_WIDTH);

	for (int i = 0; i < BOARD_HIGHT; i++)
		for (int j = 0; j < BOARD_WIDTH; j++)
			board[i][j] = '.';

	while (running)
	{
		render(board, &player1);
		printf("1: %s 2: %s 3: %s", player1.inventory[0], player1.inventory[1], player1.inventory[2]);
		readLine(inputs, length);
		processInputs(inputs, &player1);
	}
	return 0;
}

void render(char **board, struct Player *player)
{
	for (int i = 0; i < BOARD_HIGHT; i++)
	{
		for (int j = 0; j < BOARD_WIDTH; j++)
		{
			if (i == player->y && j == player->x)
				putchar(CH_PLAYER);
			else putchar(board[i][j]);
		}
		printf("\n");
	}
}

void processInputs(char *inputs, struct Player *player)
{
	char c = 0;
	// making sure that player can't move up and up-right at the same time
	// (removing contriditing moves)
	char* finilized = NULL;
	for (int i = 0; c != '\0'; i++)
	{
		c = inputs[i];
		if (c == UP || c == DOWN || c == LEFT || c == RIGHT || c == UP_LEFT || c == DOWN_LEFT ||
			c == DOWN_RIGHT || c == UP_RIGHT || c == UP_LEFT || c == NOT_MOVE)
		{
			if (finilized != NULL)
				*finilized = ' ';
			finilized = &inputs[i];
		}
	}
	free(finilized);
	// executing commands
	while (inputs[0] != '\0')
	{
		switch(inputs[0])
		{
		case UP:
			playerMoveUp(player);
			break;
		case DOWN:
			playerMoveDown(player);
			break;
		case LEFT:
			playerMoveLeft(player);
			break;
		case RIGHT:
			playerMoveRight(player);
			break;
		case UP_LEFT:
			playerMoveUp(player);
			playerMoveLeft(player);
			break;
		case DOWN_LEFT:
			playerMoveDown(player);
			playerMoveLeft(player);
			break;
		case UP_RIGHT:
			playerMoveUp(player);
			playerMoveRight(player);
			break;
		case DOWN_RIGHT:
			playerMoveDown(player);
			playerMoveRight(player);
			break;
		case NOT_MOVE:
			playerNotMove(player);
			break;
		case CREATE_SCROLL:
			{
				char scroll[127];
				int i = 0;
				while (inputs[1] == SCROLL_BIG ||  inputs[1] == SCROLL_MEDIUM ||  inputs[1] == SCROLL_SMALL ||  inputs[1] == SCROLL_FIRE)   
				{
					scroll[i] = inputs[1];
					i++;
					inputs++;
				}
				playerScrollAdd(player, scroll);
			}
			break;
		case FIRE_SCROLL:
			break;
		case CHAIN_SCROLLS:
			break;
		}
		inputs++;
	}
}

void readLine(char* inputs, int length)
{
	char c = 0;
	for (int i = 0; i < length - 1 && c != '\n'; i++)
	{
		c = getchar();
		inputs[i] = c;
	}
}


