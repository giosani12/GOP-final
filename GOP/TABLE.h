#ifndef TABLE_H_
#define TABLE_H_

class GAME;
class TABLE;
typedef TABLE* ptTABLE;

#include "GAME.h"

class TABLE : public GAME
{
protected:
	int *pt;
	bool valid;
public:
	int lenght;

	TABLE(int);
	int getType(int);
	void printTable();
};
#endif
