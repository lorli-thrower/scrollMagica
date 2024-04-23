#include "Player.h"
#include <stdio.h>

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
	// I guess void isn't that bad after all->
	(void*)player;
}
