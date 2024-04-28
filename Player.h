#ifndef PLAYER_H
#define PLAYER_H

#include <string.h>
#include <stdlib.h>

#define SCROLL_SIZE 127
#define SCROLL_AMOUNT 10

struct Player
{
	int x, y;
	char **inventory;
};

void playerInventoryAllocate (struct Player*);

void playerMoveUp		(struct Player*); 
void playerMoveDown		(struct Player*); 
void playerMoveLeft		(struct Player*); 
void playerMoveRight	(struct Player*); 
void playerNotMove		(struct Player*); 

int playerScrollAdd		(struct Player*, char scroll[127]); // adds scroll to player's inventory 

#endif
