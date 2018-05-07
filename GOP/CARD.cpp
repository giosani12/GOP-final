#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "CARD.h"
#include "PLAYER.h"

CARD::CARD() {
}

int CARD::randomCard()//Restituisce un numero casuale da 0 a 6, usata per riempire la struttura mazzo
{
	int value;
	value = rand() % 8;
	return value;
}