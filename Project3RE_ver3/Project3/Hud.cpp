#include "Hud.h"



Hud::Hud(BITMAP* newHudBackGround, BITMAP* towerButton1,  BITMAP* towerButton2,  BITMAP* towerButton3,  BITMAP* towerButton4)
{

}
Hud::Hud()
{
	hudBuffer;
	x = 0; 
	y = SCREEN_H - block_size;

	w = SCREEN_W;
	h = SCREEN_H;

	 hudBackGround = create_bitmap(w,h);
	 
	 clear_to_color(hudBackGround, makecol(0, 0, 255));
	 
	 buttonT1.init(  w / 5 * 1, y, 64, 64, "Turret1PH.bmp", 1, 0);

	 buttonT2.init( w / 5 * 1 + block_size, y, 64, 64, "Turret1PH.bmp", 1, 1); 
	 buttonT3.init( w / 5 * 1 + block_size*2, y, 64, 64, "Turret1PH.bmp", 1, 0);
	 buttonT4.init( w / 5 * 1 + block_size*3, y, 64, 64, "Turret1PH.bmp", 1, 0);

	 holdingTower = false; //false once player has clicked a valid square
	 //selectedTower; //says what stats to display

	 towerToPlace = buttonT1.getSprite();
}

Hud::~Hud(void)
{
}
bool Hud::isHoldingTower()
{
	return holdingTower;
}
void Hud::setIsHoldingTower(bool holding)
{
	holdingTower = holding;
}


bool  Hud::inside(int x, int y, int left, 
                    int top, int right, int bottom)
{
     if (x > left && x < right && y > top && y < bottom)
        return true;
     else
         return false;                         
}

void Hud::update(bool &isInHud, int board[board_width][board_height])
{
	//if (isInHud || holdingTower)
	//{
	//	//if (holdingTower)
	//	

	//}
	if (mouse_b & 1)
		{
			//if (buttonT1.collided(mouse_x, mouse_y, 1, 1))
			if ( inside(mouse_x, mouse_y, buttonT1.getX(), buttonT1.getY(), 
				buttonT1.getX() + buttonT1.getWidth(), buttonT1.getY() + buttonT1.getHeight() )
			   )
			{
				holdingTower = true;
			}
		}
}

void Hud::draw(BITMAP* dest, BITMAP* staticDest)
	{
		if (holdingTower)
		{
			draw_sprite(staticDest, towerToPlace, mouse_x -32, mouse_y - 32);
		}




		draw_sprite(staticDest, hudBackGround, x, y);

		buttonT1.drawFrame(staticDest);
		buttonT2.drawFrame(staticDest);
		buttonT3.drawFrame(staticDest);
		buttonT4.drawFrame(staticDest);
	}
