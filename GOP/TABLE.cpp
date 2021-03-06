#include "GAME.h"
#include "TABLE.h"
#include <cstdlib>
#include <iostream>

using namespace std;

TABLE::TABLE(int input)//costruttore tabella, inizializza tutti i campi e prende in input la lunghezza
{
	lenght = input;
	valid = true;
	int temp[50] = { 0,0,0,0,0,0,0,0,1,1,1,1,1,1,2,2,2,2,3,3,3,3,3,3,4,4,4,4,5,5,5,6,6,6,6,7,7,7,7,7,7,7,8,8,8,8,8,9,9,9 };
	pt = new int[lenght];
	pt[0] = 0;
	for (int i = 1; i < lenght - 1; i++) pt[i] = temp[rand() % 50];
	pt[lenght - 1] = 0;
}

int TABLE::getType(int input)//traduttore da numero casella a tipo di casella
{
	return pt[input - 1];
}

void TABLE::printTable()//stampa la tabella e il traduttore per i tipi di casella
{
	if (valid)
	{
		cout << "\nFormato casella: |Numero Casella| Tipo Casella (vedi traduttore sottostante)|" << endl;
		cout << "+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+";
		cout << endl;
		for (int j = 0; j < lenght; j++)
		{
			cout << "|" << j + 1 << "| " << pt[j] << "\t";
			if ((j+1) % 14 == 0)
			{
				cout << "|\n+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+------";
				cout << "-+-------+\n";
			}
		}
		if ((lenght % 14) != 0) cout << "|" << endl;
	}
	else
	{
		cout << "\nErrore: nessuna tabella da stampare." << endl;
	}
	cout << "0=casella vuota\t	1=vai avanti di uno\t2=vai avanti di due\t3=vai indietro di 1\t4=vai indietro di 2";
	cout << "\n5=scambia col primo\t6=salta il turno\t7=tira di nuovo il dado\t8=pesca una carta\t9=torna all'inizio";
}