#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Player.h"

#define BOARD_HIGHT 46
#define BOARD_WIDTH 213
//#define BOARD_HIGHT 73
//#define BOARD_WIDTH 273

enum SingleplayerControlls 
{
UP				= 'k', 
DOWN			= 'j', 
LEFT			= 'h', 
RIGHT			= 'l', 
UP_LEFT			= 'y', 
DOWN_LEFT		= 'b', 
UP_RIGHT		= 'u', 
DOWN_RIGHT		= 'n', 
NOT_MOVE		= '.', 
CREATE_SCROLL	= 's', 
FIRE_SCROLL		= 'f', 
CHAIN_SCROLLS	= 'c'
};

bool running = true;

void render(char **board, struct Player *player);
void processInputs(char *inputs, struct Player*);

int main()
{
	struct Player player1;
	player1.x = BOARD_WIDTH / 2;
	player1.y = BOARD_HIGHT / 2;
	char* inputs = malloc(sizeof(char) * 255);
	size_t length = 255;
	char **board = malloc(sizeof(char*) * BOARD_HIGHT);
	for (int i = 0; i < BOARD_HIGHT; i++)
		board[i] = malloc(sizeof(char) * BOARD_WIDTH);

	for (int i = 0; i < BOARD_HIGHT; i++)
		for (int j = 0; j < BOARD_WIDTH; j++)
			board[i][j] = '.';

	while (running)
	{
		render(board, &player1);
		getline(&inputs, &length, stdin);
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
				printf("@");
			else printf("%c", board[i][j]);
		}
		printf("\n");
	}
}

void processInputs(char *inputs, struct Player *player)
{
	char c = ' ';
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
	// executing commands
	c = ' ';
	for (int i = 0; c != '\0'; i++)
	{
		c = inputs[i];
		switch(c)
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
			break;
		case FIRE_SCROLL:
			break;
		case CHAIN_SCROLLS:
			break;
		}
	}
}
