#include "GAME.h"
#include "TABLE.h"
#include "PLAYER.h"
#include "CARD.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main()//main
{
	srand((unsigned int)time(NULL));
	ptGAME GIOCO= new GAME();
	GIOCO->firstTurn();
	return 0;
}