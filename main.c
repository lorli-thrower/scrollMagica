#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Player.h"

#define RENDER 0

#define BOARD_WIDTH 191
#define BOARD_HIGHT 63

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
	char* inputs = calloc(255, sizeof(char));
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
		for (int i = 0; i < SCROLL_AMOUNT; i++)
			printf("%d: %s ", i+1, player1.inventory[i]);
		printf("You act: ");
		readLine(inputs, length);
		processInputs(inputs, &player1);
	}
	return 0;
}

void render(char **board, struct Player *player)
{
#if RENDER
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
#endif
}

void processInputs(char *inputs, struct Player *player)
{
	char c = ' ';
	// making sure that player can't move up and up-right at the same time
	// (removing contriditing or same actions)
	for (int i = 0; inputs[i] != '\0'; i++)
		for (int j = i + 1; inputs[j] != '\0'; j++)
			if (inputs[i] == inputs[j])
			{
				inputs[i] = ' ';
				break;
			}
	char* finilizedMovement = NULL;
	for (int i = 0; c != '\0'; i++)
	{
		c = inputs[i];
		if (c == UP || c == DOWN || c == LEFT || c == RIGHT || c == UP_LEFT || c == DOWN_LEFT ||
			c == DOWN_RIGHT || c == UP_RIGHT || c == UP_LEFT || c == NOT_MOVE)
		{
			if (finilizedMovement != NULL)
				*finilizedMovement = ' ';
			finilizedMovement = &inputs[i];
		}
	}
	// removing spaces so that the above actually works with scrolls too
	for (int i = 0; inputs[i] != '\0'; i++)
	{
		if (inputs[i] == ' ')
		{
			int j, k = i;
			for (j = i + 1; inputs[j] == ' '; j++);
			while (inputs[j] != '\0')
			{
				inputs[k] = inputs[j];
				inputs[j] = 0;
				k++;
				j++;
			}
		}
	}
	// executing commands
	printf("Inputs: %s", inputs);
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
				int i;
				char scroll[SCROLL_SIZE];
				for (i = 0; i < SCROLL_SIZE; i++)
					scroll[i] = 0;
				i = 0;
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
		inputs[0] = 0;
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


