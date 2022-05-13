//care ver
//#include <vector>

#include <allegro.h>
#include "global.h"
#include "Level.h"
#include "Game.h"
#include "RunGame.h"
#include "Enemy.h"
void init(); 
void setCorners(int c[board_width][board_height], Enemy& evil1, 
	Level levels);
void loadSound(const char*);
void playSound();

SAMPLE* sound;
void cameraScroll(int playerX, int playerY, int &cameraX, int &cameraY, int worldW, int worldH);

volatile long timer = 0;
void increment()
{
	timer++;
}
END_OF_FUNCTION(increment);

int main()
{
	using namespace std;
	allegro_init();
	init();
	/////////// Timer stuff ///////////////
	LOCK_FUNCTION(increment);
	LOCK_VARIABLE(timer);


	install_int_ex(increment, BPS_TO_TIMER(100));

	/////////////////////////////

	// BUFFERS ////////////////////////////////
	BITMAP* buffer = create_bitmap(32 * block_size, board_height * block_size);
	BITMAP* finalBuffer = create_bitmap(board_width * block_size, board_height * block_size+ block_size); //other buffers blit to this
	///////////////////////////////////////////

	


//////initialize the running game
	RunGame runGame;
	bool end = false;

	int camX = 0;
	int camY = 0;
//////////////////////////////////

//////////////////////
///// MAIN LOOP //////
//////////////////////
	while (!end)
	{
		//updates
		while (timer > 0)
		{
			if (timer == 1)
			{
				    runGame.update();

					if (key[KEY_ESC])
					{
						end = true;
					}

					clear_to_color(buffer, makecol(255,0,255));

			}
			timer--;
		}

		clear_bitmap(finalBuffer);
//DRAWS///////////////////////////////////////////////////////
		runGame.drawAll(buffer);

		//draw_sprite(finalBuffer,buffer,0,0);

		//blit buffer..
		acquire_screen();
		blit(buffer, screen, camX, camY, 0, 0, SCREEN_W, SCREEN_H);
		release_screen();

		//CHEATS///////////////////////////////////////////
		if (key[KEY_D])
		{
			
		}

		if (key[KEY_L])
		{
//			player.lives = 3;
		}
	}
	
	return 0;

	destroy_bitmap(buffer);
//	destroy_bitmap(backBuffer);
	destroy_bitmap(finalBuffer);
	//stop_sample(sound);
	//destroy_sample(sound);


}

END_OF_MAIN()


void init() 
{
	int depth, res;
	allegro_init();
	depth = desktop_color_depth();
	if (depth == 0) depth = 32;
	set_color_depth(depth);
	res = set_gfx_mode(GFX_AUTODETECT_WINDOWED, 1024, 768, 0, 0);//960
	
	if (res != 0) {
		allegro_message(allegro_error);
		exit(-1);
	}

    if (install_sound(DIGI_AUTODETECT, MIDI_NONE, "") != 0)
	{
	//	allegro_message("error init sound!!");
	//	exit(-1);
	}

	install_timer();
	install_keyboard();
	install_mouse();
	show_mouse(screen);
	/* add other initializations here */
}

void setCorners(int c[board_width][board_height], Enemy& evil1, 
	Level levels)
{
	int count = 0;
	bool first = true;
	int tempx = 0;
	int tempy = 0;
	for(int x = 0; x < board_width; x++)
	{
		for(int y = 0; y < board_height; y++)
		{
			if(!(evil1.isNotWall(levels.gameBoard, board_width, board_height, x, y)))
			{
				c[x][y] = 0;
			}
			else
			{
				bool top =    evil1.isNotWall(levels.gameBoard, board_width, board_height, x  , y-1);
				bool bottom = evil1.isNotWall(levels.gameBoard, board_width, board_height, x  , y+1);
				bool left =   evil1.isNotWall(levels.gameBoard, board_width, board_height, x-1, y  );
				bool right =  evil1.isNotWall(levels.gameBoard, board_width, board_height, x+1, y  );
				if((top && right) || (top && left) || (bottom && left) || 
					(bottom && right))
				{
					if(first)
						/*set first corner in top left as the first running 
						point*/
					{
						c[x][y] = 2;
						first = false;
						tempx = x;
						tempy = y;
					}
					else if((!right && (x+2 == board_width)) && tempy == y)
						/*set the last corner on the same y as the first 
						running point as the second running point*/
					{
						c[x][y] = 2;
					}
					else if(tempx == x && (!bottom && (y+2 == board_height)))
						/*set the last corner on the same x as the first
						running point as the third running point*/
					{
						c[x][y] = 2;
					}
					else if((!right && (x+2 == board_width)) && 
						(!bottom && (y+2 == board_height)))
						/*if this is the last corner to the right and the 
						last corner to the bottom set as the fourth running 
						point*/
					{
						c[x][y] = 2;
					}
					else
					{
						c[x][y] = 1;
					}
				}
				else
				{
					c[x][y] = 0;
				}
			}
		}
	}
}

void playSound(const char* wavFile)
{
	//voice_set_playMode(int voice
	SAMPLE* sound;
	sound = load_sample(wavFile);
	if (sound == NULL)
	{

	//	allegro_message("error loading sound!");
	//	exit(-1);

	}

	play_sample(sound, 255, 128, 1000, FALSE);
//	destroy_sample(sound);
}

void loadSound(const char* file)
{
	stop_sample(sound);
	destroy_sample(sound);
    sound = load_sample(file);
	if (sound == NULL)
	{

		allegro_message("error loading sound!");
		exit(-1);

	}
	playSound();
}

void playSound()
{
	play_sample(sound, 255, 128, 1000, FALSE);
}


void cameraScroll(int playerX, int playerY, int &cameraX, int &cameraY, int worldW, int worldH)
{
	cameraX = playerX; //- (SCREEN_W / 2);
	cameraY = playerY; //- (SCREEN_H / 2);

	if (cameraX < 0 )
		cameraX = 0;
	if (cameraX > worldW - SCREEN_W)
		cameraX  =  worldW - SCREEN_W;              

	if (cameraY < 0)
		cameraY = 0;

	if (cameraY > worldH - SCREEN_H)
	{
		cameraY = worldH - SCREEN_H;
	}

}
//#include <allegro.h>
//
//void init() 
//{
//	int depth, res;
//	allegro_init();
//	depth = desktop_color_depth();
//	if (depth == 0) depth = 32;
//	set_color_depth(depth);
//	res = set_gfx_mode(GFX_AUTODETECT_WINDOWED, 1024, 768, 0, 0);//960
//	
//	if (res != 0) {
//		allegro_message(allegro_error);
//		exit(-1);
//	}
//
//    if (install_sound(DIGI_AUTODETECT, MIDI_NONE, "") != 0)
//	{
//	//	allegro_message("error init sound!!");
//	//	exit(-1);
//	}
//
//	install_timer();
//	install_keyboard();
//	install_mouse();
//	show_mouse(screen);
//	/* add other initializations here */
//}
//int main()
//{
//
//	init();
//	readkey();
//	return 0;
//
//}
//
//END_OF_MAIN()