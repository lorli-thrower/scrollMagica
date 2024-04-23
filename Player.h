#ifndef PLAYER_H
#define PLAYER_H

struct Player
{
	int x, y;
	char **inventory;
};
void playerMoveUp		(struct Player*); 
void playerMoveDown		(struct Player*); 
void playerMoveLeft		(struct Player*); 
void playerMoveRight	(struct Player*); 
void playerNotMove		(struct Player*);

#endif
