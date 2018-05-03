#ifndef TABLE_H_
#define TABLE_H_

class GAME;
class TABLE;
typedef TABLE* ptTABLE;

class TABLE : public GAME
{
protected:
	int *pt;
	bool valid;
public:
	int lenght;
	TABLE(int);
	~TABLE();
	int getType(int);
	void printTable();
};
#endif
