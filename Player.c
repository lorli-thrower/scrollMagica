#include "Player.h"
#include <stdio.h>

void playerInventoryAllocate(struct Player* player)
{
	player->inventory = calloc(SCROLL_AMOUNT, sizeof(player->inventory[0]));
	for (int i = 0; i < SCROLL_AMOUNT; i ++)
		player->inventory[i] = calloc(SCROLL_SIZE, sizeof(player->inventory[i][0]));
}

void playerMoveUp(struct Player *player) 
{
	player->y -= 1;
}

void playerMoveDown(struct Player *player) 
{
	player->y += 1;
}

void playerMoveLeft(struct Player *player) 
{
	player->x -= 1;
}

void playerMoveRight(struct Player *player) 
{
	player->x += 1;
}

void playerNotMove(struct Player *player)
{
	// To move or not to move? Big questions, isn't it?
	// And the most importantly, what do you move when you don't?
	// Do you even have to do anything? Or will flowing down the
	// river really help you in this situation?
	// I guess void isn't that bad after all
	(void*)player;
}

int playerScrollAdd(struct Player* player, char scroll[SCROLL_SIZE]) // adds scroll to player's inventory 
{
	int i;
	for (i = 0; player->inventory[i][0] != '\0'; i++)
		if (i >= SCROLL_AMOUNT - 1) return -1;
	memcpy(player->inventory[i], scroll, SCROLL_SIZE * sizeof(char));
	return 0;
}
