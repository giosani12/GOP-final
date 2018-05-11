#ifndef PLAYER_H_
#define PLAYER_H_

class PLAYER;
typedef PLAYER* ptPLAYER;

#include "GAME.h"

class PLAYER : public GAME
{
public:
	bool jumpTurn;
	int position;
	int numero;
	int points;
	char name[20];
	ptPLAYER next;

	PLAYER(int, char[]);
};
#endif