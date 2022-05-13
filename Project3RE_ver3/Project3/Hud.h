#ifndef HUD_H
#define HUD_H 1
#include "BaseClass.h"
#include "Tower.h"
#include <allegro.h>
class Hud
{
protected:
	BITMAP* hudBuffer;
	int x, y;
	int w,h;
	BITMAP* hudBackGround;

	BaseClass buttonT1;
	BaseClass buttonT2;
	BaseClass buttonT3;
	BaseClass buttonT4;

	bool holdingTower; //false once player has clicked a valid square
	//Tower selectedTower; //says what stats to display

	BITMAP* towerToPlace;
	
	//Player player;

public:
	Hud(BITMAP* newHudBackGround, BITMAP* towerButton1,  BITMAP* towerButton2,  BITMAP* towerButton3,  BITMAP* towerButton4);
	Hud::Hud();
	~Hud();

	bool isHoldingTower();
	void setIsHoldingTower(bool holding);
	void draw(BITMAP* dest, BITMAP* staticDest);
	bool  inside( int x, int y, int left, 
                    int top, int right, int bottom);

	void update(bool &isInHud, int board[board_width][board_height]); //shoould see if the mouse clicks on a square, 
																	  //  if so what type of tower was the square
};																	  //  and display that tower's info until the user clicks another 
																	  //  tower/ tower button onthe hud	

#endif
