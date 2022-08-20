#ifndef GAME_OF_LIFE_CELL
#define GAME_OF_LIFE_CELL
#include<array>
#include "Rect2D.h"


class GOLCell {
public:
	GOLCell();
	GOLCell(bool lifeStatus);
	bool alive;
	bool isAlive();
	void setAlive(bool lifeStatus);
	GOLCell checkForLife(GOLCell*);
	Rect2D square;
};


#endif