#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "CARD.h"
#include "PLAYER.h"

int CARD::randomCard()//Restituisce un numero casuale da 0 a 6, usata per riempire la struttura mazzo
{
	int tmp[25] = { 0,0,0,0,1,1,2,2,2,2,3,3,4,5,5,5,6,6,6,6,6,7,7,7,7 };
	int value;
	value = tmp[rand() % 25];
	return value;
}