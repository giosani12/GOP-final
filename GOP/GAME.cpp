#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include "GAME.h"
#include "CARD.h"
#include "PLAYER.h"
#include "TABLE.h"

using namespace std;

GAME::GAME() {
}

void GAME::throwDice()//funzione del lancio dado
{
	int j = (rand() % 6) + 1;
	playerList->position = playerList->position + j;
	if (playerList->position > ptTab->lenght) playerList->position = ptTab->lenght;
	cout << "\nIl giocatore " << playerList->name << " tira il dado ed esce " << j << ", ora " << playerList->name << " e\' in posizione " << playerList->position << ".";
}

void GAME::addToPosition(int num)//funzione utile per gli effetti di movimento sulla tabella, somma alla posione del giocatore il numero in input
{
	if ((num + playerList->position) > 0)
	{
		playerList->position = playerList->position + num;
		if (playerList->position > ptTab->lenght) playerList->position = ptTab->lenght;
	}
	else playerList->position = 1;
}

void GAME::tabTypeTranslate()//chiamante per gli effetti della tabella
{
	switch (ptTab->getType(playerList->position))
	{
	case 0:
		cout << "\nEffetto casella: casella vuota!";
		break;
	case 1:
		addToPosition(1);
		cout << "\nEffetto casella: il giocatore " << playerList->name << " e\' andato avanti di una casella e ora e\' in posizione " << playerList->position;
		break;
	case 2:
		addToPosition(2);
		cout << "\nEffetto casella: il giocatore " << playerList->name << " e\' andato avanti di due caselle e ora e\' in posizione " << playerList->position;
		break;
	case 3:
		addToPosition(-1);
		cout << "\nEffetto casella: il giocatore " << playerList->name << " e\' andato indietro di una casella e ora e\' in posizione " << playerList->position;
		break;
	case 4:
		addToPosition(-2);
		cout << "\nEffetto casella: il giocatore " << playerList->name << " e\' andato indietro di due caselle ed ora e\' in posizione " << playerList->position;
		break;
	case 5:
		swapWithFirst();
		cout << "\nEffetto casella: il giocatore " << playerList->name << " ha scambiato la sua posizione con il primo in classifica";
		break;
	case 6:
		playerList->jumpTurn = true;
		cout << "\nEffetto casella: il giocatore " << playerList->name << " saltera\' il prossimo turno";
		break;
	case 7:
		cout << "\nEffetto casella: il giocatore " << playerList->name << " tira due volte il dado";
		throwDice();
		break;
	case 8:
		cout << "\nEffetto casella: il giocatore " << playerList->name << " pesca una carta.";
		cardTypeTranslate();
		break;
	case 9:
		playerList->position = 1;
		cout << "\nEffetto casella: il giocatore " << playerList->name << " e\' tornato all'inizio ed ora e\' in posizione 1";
		break;
	default:
		cout << "\nINTERNAL_ERROR -Prego allontanarsi dal computer ";
	}
}

void GAME::cardTypeTranslate()//chiamante per gli effetti del mazzo di carte
{
	switch (ptDeck->type)
	{
	case 0:
		addToPosition(1);
		cout << "\nEffetto carta: il giocatore " << playerList->name << " e\' andato avanti di una casella e ora e\' in posizione " << playerList->position;
		break;
	case 1:
		addToPosition(2);
		cout << "\nEffetto carta: il giocatore " << playerList->name << " e\' andato avanti di due caselle e ora e\' in posizione " << playerList->position;
		break;
	case 2:
		addToPosition(-1);
		cout << "\nEffetto carta: il giocatore " << playerList->name << " e\' andato indietro di una casella e ora e\' in posizione " << playerList->position;
		break;
	case 3:
		addToPosition(-2);
		cout << "\nEffetto carta: il giocatore " << playerList->name << " e\' andato indietro di due caselle ed ora e\' in posizione " << playerList->position;
		break;
	case 4:
		swapWithFirst();
		cout << "\nEffetto carta: il giocatore " << playerList->name << " ha scambiato la sua posizione con il primo in classifica";
		break;
	case 5:
		cout << "\nEffetto carta: il giocatore " << playerList->name << " tira di nuovo il dado";
		throwDice();
		break;
	default:
		cout << "\nINTERNAL_ERROR -Prego allontanarsi dal computer ";
	}
	ptDeck = ptDeck->next;
}


void GAME::getFirst(ptPLAYER *out)//funzione che restituisce un array di puntatori al (o ai) giocatore primo in classifica 
{
	int i, counter = 0;
	bool found = false;
	ptPLAYER ptTMP = playerList;
	for (i = ptTab->lenght; ((i > 0) && !found); i--)
	{
		for (int j = 0; j<NUMERO_GIOCATORI; j++)
		{
			if ((i == playerList->position) && !found)
			{
				out[0] = playerList;
				found = true;
				counter++;
				out[counter] = NULL;
			}
			else if ((i == playerList->position) && found)
			{
				out[counter] = playerList;
				counter++;
				out[counter] = NULL;
			}
			playerList = playerList->next;
		}
	}
	playerList = ptTMP;
}


void GAME::swapWithFirst()//scambia la posizione del giocatore corrente con il primo e viceversa (funziona anche con più giocatori a pari merito)
{
	ptPLAYER *first = new ptPLAYER[NUMERO_GIOCATORI + 1];
	getFirst(first);
	int temp = first[0]->position, i = 0;
	while (first[i] != NULL)
	{
		first[i]->position = playerList->position;
		i++;
	}
	delete first;
	playerList->position = temp;
}

void GAME::createPlayerList()//Inizializza il puntatore alla lista di giocatori (lista circolare) prendendo da input numero e nome dei giocatori.
{
	int num = 0, i = 1;
	char tmpName[20];
	string tmpNameSTR;
	ptPLAYER tmp, ptHead;
	tmpName[0] = '\0';
	do
	{
		cout << "\nInserire numero giocatori: ";
		cin >> num;
	} while (num < 1);
	NUMERO_GIOCATORI = num;
	cout << "\nInserire nome per giocatore " << i << ": ";
	cin.ignore(1, EOF);
	cin.getline(tmpName, 20, '\n');
	playerList = new PLAYER(1, tmpName);
	ptHead = playerList;
	i++;
	while (i <= num)
	{
		cout << "\nInserire nome per giocatore " << i << ": ";
		cin.getline(tmpName, 20, '\n');
		tmp = new PLAYER(i, tmpName);
		playerList->next = tmp;
		playerList = tmp;
		i++;
	}
	playerList->next = ptHead;//in uscita playerlist punta all'ultimo giocatore perchè il primo turno inizia con un playerlist=playerlist->next
}

void GAME::deletePlayerList()//Distrugge la lista di giocatori partendo dal puntatore al giocatore attuale
{
	ptPLAYER tmp;
	for (int i = 0; i < NUMERO_GIOCATORI; i++)
	{
		tmp = playerList->next;
		delete playerList;
		playerList = tmp;
	}
}
	


void GAME::drawCard()//pesca una carta casuale dal mazzo e ne esegue l'effetto.
{
	cardTypeTranslate();
	ptDeck = ptDeck->next;
}

void GAME::createDeck(int lenght)//Crea lista circolare di carte con testa in ptDeck
{
	ptDeck = new CARD();
	ptCARD tmp = ptDeck;
	for (int i = 0; i < lenght; i++)
	{
		tmp->type = tmp->randomCard();
		if (i < lenght-1)
		{
			tmp->next = new CARD();
			tmp = tmp->next;
		}
	}
	tmp->next = ptDeck;
	cout << "\nE\' stato creato un mazzo di " << lenght << " carte.";
	cout << "\nEffetti carte: vai avanti di uno, vai avanti di due, vai indietro di uno, vai indietro di due, scambia con primo in ";
	cout << "\nclassifica e tira di nuovo il dado.";
}

void GAME::deleteDeck()//Distrugge la sovrastante
{
	ptCARD tmp;
	for (int i = 0; i < NUMERO_GIOCATORI; i++)
	{
		tmp = ptDeck->next;
		delete ptDeck;
		ptDeck = tmp;
	}
}

void GAME::printChart()//Stampa la lista dei giocatori ordinati per posizione
{
	bool found = false;
	int pos = 0;
	cout << "\nCLASSIFICA:\n|Posizione\t|Posizione in Tabella\t|Nome Giocatore";
	for (int i = ptTab->lenght; i > 0; i--)
	{
		for (int j = 0; j<NUMERO_GIOCATORI; j++)
		{
			if ((i == playerList->position) && !found)
			{
				pos = pos + 1;
				cout << "\n|" << pos << "\t\t|" << "\n|" << playerList->points << "\t\t|" << playerList->position << "\t\t\t|" << playerList->name;
				found = true;
			}
			else if ((i == playerList->position) && found)
			{
				cout << "\n|" << pos << "\t\t|" << "\n|" << playerList->points << "\t\t|" << playerList->position << "\t\t\t|" << playerList->name;
			}
			playerList = playerList->next;
		}
		found = false;
	}
	cout << endl;
}

void GAME::firstTurn()//Inizializza la lista di giocatori, il mazzo e la tabella
{
	cout << "Questo e\' il gioco GOP per il progetto di programmazione";
	cout << "\n\t\t\t\t\t\tREGOLE:";
	cout << "\nAd ogni turno il giocatore tira il dado e si sposta sul tabellone in base al numero ottenuto, ogni casella ha ";
	cout << "\nun effetto(traduzione sottostante) e ad ogni turno il giocatore pesca anche una carta, anch'essa con un effetto.";
	cout << "\nUn giocatore vince quando riesce ad arrivare in fondo al tabellone.\n";
	createPlayerList();
	createDeck(rand() % 20 + 40);
	ptTab = new TABLE(rand() % 20 + 55);
	nextTurn();
	return;
}

void GAME::nextTurn()//Esegue la routine di un turno standard offrendo la possibilita\' di uscire o ricominciare
{
	char loop;
	playerList = playerList->next;
	if (!playerList->jumpTurn)
	{
		throwDice();
		if (playerList->position >= ptTab->lenght)
		{
			endGame(true); //True quando il gioco finisce in modo normale
			return;
		}
		tabTypeTranslate();
		if (playerList->position >= ptTab->lenght)
		{
			endGame(true); //True quando il gioco finisce in modo normale
			return;
		}
		drawCard();
	}
	else
	{
		cout << "\nIl giocatore " << playerList->name << " salta il turno.";
		playerList->jumpTurn = false;
	}
	ptTab->printTable();
	if (playerList->position >= ptTab->lenght)//True quando il gioco finisce in modo normale
	{
		endGame(true);
		return;
	}
	printChart();
	do
	{
		cout << "Se vuoi finire la partita scrivi Y, se vuoi continuare scrivi N, se bisogno di aiuto scrivi H (non case sensitive)\n";
		cin >> loop;
		if ((loop == 'H') || (loop == 'h'))
		{
			cout << "REGOLE:\nAd ogni turno il giocatore tira il dado e si sposta sul tabellone in base al numero ottenuto, ogni casella ha ";
			cout << "\nun effetto(traduzione sottostante) e ad ogni turno il giocatore pesca anche una carta, anch'essa con un effetto.";
			cout << "\nUn giocatore vince quando riesce ad arrivare in fondo al tabellone.";
			cout << "\nEffetti carte: vai avanti di uno, vai avanti di due, vai indietro di uno, vai indietro di due, scambia con primo in ";
			cout << "\nclassifica e tira di nuovo il dado.\n";
		}
	} while (loop != 'Y' && loop != 'y' && loop != 'N' && loop != 'n');
	if ((loop == 'Y') || (loop == 'y'))//False quando il gioco è interrotto dall'utente
	{
		endGame(false);
		return;
	}
	else// if ((loop == 'N') || (loop == 'n'))
	//{
		GAME::nextTurn();
	//	return;
	//}
	return;
}


void GAME::endGame(bool end)//Fa pulizia del gioco appena finito
{
	char loop;
	if (end)
	{
		ptPLAYER *tmp = new ptPLAYER[1];
		getFirst(tmp);
		cout << "\nLa partita e\' terminata.\nIl giocatore " << tmp[0]->name << " ha vinto! Consulta qui sotto la classifica finale";
		printChart();
		delete ptTab;
		deleteDeck();
		deletePlayerList();
		do
		{
			cout << "Se vuoi ricominciare scrivi Y, se vuoi uscire scrivi N (non case sensitive)";
			cin >> loop;
		} while (loop != 'Y' && loop != 'y' && loop != 'N' && loop != 'n');
		if ((loop == 'Y') || (loop == 'y')) firstTurn();
		else return;
	}
	else if (!end)
	{
		cout << "\nLa partita e\' stata terminata, consulta qua sotto la classifica finale\n " ;
		printChart();
		delete ptTab;
		deleteDeck();
		deletePlayerList();
		do 
		{
			cout << "Se vuoi ricominciare scrivi Y, se vuoi uscire scrivi N (non case sensitive)";
			cin >> loop;
		} while (loop != 'Y' && loop != 'y' && loop != 'N' && loop != 'n');
		if ((loop == 'Y') || (loop == 'y')) firstTurn();
		else return;
	}
}