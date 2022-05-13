#include "Game.h"
#include <allegro.h>


Game::Game(int numberOfLevels, Level firstLevel, bool titleOrEnd)
{
     currentLevel = 0;
	 
	 levels[0]       = firstLevel; //the other one are garbage!
	 activeLevel     = firstLevel;
	 totalLevels     = numberOfLevels;
	 levelTransition = false;
	 titleOrEnd      = titleOrEnd;
//	 score = 1600;
}
Game:: Game()
{
	//does nothing, make sure to call init() if using this
}
void Game::init(int numberOfLevels, Level firstLevel, bool titleOrEnd)
{
     currentLevel = 0;
	 
	 levels[0]       = firstLevel; //the other one are garbage!
	 activeLevel     = firstLevel;
	 totalLevels     = numberOfLevels;
	 levelTransition = false;
	 titleOrEnd      = titleOrEnd;
//	 score = 1600;
}


Game::~Game()
{


}

	//getters//////////////
	int Game::getCurrentLevel()
	{
		return currentLevel;
	}
	Level Game::getLevel(int level)
	{
		return levels[level];
	}
	int Game::getTotalLevels()
	{
		return totalLevels;
	}

	bool Game::isLevelTransition()
	{
		return levelTransition;
	}
	bool Game::isTitleOrEnd()
	{
		return titleOrEnd;
	}

	//////////////////////////
	//setters//////////////////////////////////
	void Game::setLevel(Level level, int levelNumber)
	{
		levels[levelNumber] = level;
	}
	
	void Game::setTransitioning(bool isTransitioning)
	{
		levelTransition = isTransitioning;
	}
	void Game::setTitleOrEnd(bool isTitleOrEnd)
	{
		titleOrEnd = isTitleOrEnd;
	}
	////////////////////////////////////////////


    //OtherFunctions///////////////////////////	

	///// updates //////////////////////////////////
	void Game::update()
	{
		
	}
	///////////////////////////////////////////////


	bool Game::skipToLevel(int levell)
	{
		return true;
	}


	void Game::transitionLevel(BITMAP* dest)
	{
		//transitionLevel(

	}


	void Game::transitionLevel(const char* cutsceneFrames[], int size)
	{

		transitionLevel(cutsceneFrames, size, NULL);
	}

	void Game::transitionLevel(const char* frame, void* callbackFunction())
	{
		const char* temp[1] = {frame};
		transitionLevel(temp, 1, callbackFunction);
	}

	void Game::transitionLevel(const char* cutsceneFrames[], int size, void* callbackFunction())
	{
		if (levelTransition == true)
		{

			for(int i = 0; i < size; i++)
			{
				cutsceneFrame(500, cutsceneFrames[i], callbackFunction);
			}
			currentLevel++;
			if (currentLevel < totalLevels)
			{
				activeLevel = levels[currentLevel];
			
			}
			else
			{
				currentLevel = 0;
				activeLevel = levels[currentLevel];
			}
			levelTransition = false;
		}
	}

	void Game::transitionLevelInput(const char* frame, void* callbackFunction())
	{
		const char* temp[1] = {frame};
		transitionLevelInput(temp, 1, callbackFunction);
	}


	void Game::transitionLevelInput(const char* cutsceneFrames[], int size, void* callbackFunction())
	{
		if (levelTransition == true)
		{

			for(int i = 0; i < size; i++)
			{

					cutsceneFrame(1, cutsceneFrames[i], callbackFunction);				
				while (!key[KEY_ENTER])
				{
				}
				//readkey();
			}

			currentLevel++;
			if (currentLevel < totalLevels)
			{
				activeLevel = levels[currentLevel];
			
			}
			else
			{
				currentLevel = 0;
				activeLevel = levels[currentLevel];
			}
			levelTransition = false;
		}
	}

void Game::transitionLevelInput(const char* cutsceneFrames, void* callbackFunction(), int theKey)
	{
		if (levelTransition == true)
		{

			//for(int i = 0; i < size; i++)
			//{

					cutsceneFrame(1, cutsceneFrames, callbackFunction);	
				if (theKey == KEY_ENTER)
					while (!key[KEY_ENTER])
					{
					}
				else
					while (!key[KEY_ESC])
					{
					}
				//readkey();
			//}

			currentLevel++;
			if (currentLevel < totalLevels)
			{
				activeLevel = levels[currentLevel];
			
			}
			else
			{
				currentLevel = 0;
				activeLevel = levels[currentLevel];
			}
			levelTransition = false;
		}
	}


void Game::fade_in(BITMAP *bmp_orig, int speed, int color)
{
   BITMAP *bmp_buff;
   bmp_buff = create_bitmap(SCREEN_W, SCREEN_H);
    if ((bmp_buff))
    {
        int a;
		
        if (speed <= 0) speed = 16;
        
        for (a = 0; a < 256; a+=speed)
        {
            clear_to_color(bmp_buff, color);
            set_trans_blender(getr(color),getg(color),getb(color),a);
            draw_trans_sprite(bmp_buff, bmp_orig, 0, 0);
            blit(bmp_buff, screen, 0,0, 0,0, SCREEN_W, SCREEN_H);
        }
        destroy_bitmap(bmp_buff);
    } 

    blit(bmp_orig, screen, 0,0, 0,0, SCREEN_W, SCREEN_H);
}

void Game::fade_out(int speed, int color)
{
    BITMAP *bmp_orig, *bmp_buff;
	bmp_orig = create_bitmap(SCREEN_W, SCREEN_H);
    bmp_buff = create_bitmap(SCREEN_W, SCREEN_H);
	if (bmp_orig)
    {
        if (bmp_buff)
        {
            int a;
            blit(screen, bmp_orig, 0,0, 0,0, SCREEN_W, SCREEN_H);
            if (speed <= 0) speed = 16;
        
            for (a = 255-speed; a > -speed; a-=speed)
            {
				clear_to_color(bmp_buff, color);
                set_trans_blender(0,0,0,a);
                draw_trans_sprite(bmp_buff, bmp_orig, 0, 0);
                blit(bmp_buff, screen, 0,0, 0,0, SCREEN_W, SCREEN_H);
            }
            destroy_bitmap(bmp_buff);
        }
        destroy_bitmap(bmp_orig);
    }
}

//CUTSCENE FUNCTIONS
//should pause the other stuff
void Game::cutsceneFrame(int time, BITMAP* frame)
{
	cutsceneFrame(time, frame, NULL);
}

void Game::cutsceneFrame(int time, BITMAP* frame, void* callbackFunction())
{
	//call fadeIn
	clear_bitmap(screen);

	draw_sprite(screen, frame, (SCREEN_W - frame->w) / 2, (SCREEN_H - frame->h) / 2  );
    for (int i = 0; i < time; i++)
	{
		if (callbackFunction != NULL)
			callbackFunction();
		rest(1);
	}
}

void Game::cutsceneFrame(int time, const char* frame)
{
	cutsceneFrame(time, frame, NULL);
}

void Game::cutsceneFrame(int time, const char* frame, void* callbackFunction())
{
	BITMAP* temp = getSprite(frame);
	
	cutsceneFrame(time, temp);

	destroy_bitmap(temp);

}

///////////////////////////////////////////////////////////////////////////////////

bool Game::setSprite(BITMAP* bitmapToSet, const char* filename)
{
		bitmapToSet = load_bitmap(filename, 0);

		if (bitmapToSet != 0)
		{
			return true;

		}

		//set to glitch sprite
		else
			allegro_message("ERRROR loading bitmapToSet in Game class");
		return false;
}

BITMAP* Game::getSprite(const char* filename)
{
		BITMAP* bitmapToSet = load_bitmap(filename, 0);

		if (bitmapToSet != 0)
		{

			return bitmapToSet;
		
		}

		//set to glitch sprite
		else
			allegro_message("ERRROR loading bitmapToSet in Game class GETsPRITE");

		exit(-1);
		return NULL;
}
	///////////////////////////////////////////



 void Game::playSound(const char* wavFile)
{
	//voice_set_playMode(int voice
	SAMPLE* sound = load_sample(wavFile);

	if (sound == NULL)
	{

		allegro_message("error loading sound!");
		exit(-1);

	}

	play_sample(sound, 255, 128, 1000, FALSE);
	destroy_sample(sound);
}

SAMPLE* Game::loadSound(const char* file)
{
    SAMPLE* sound = load_sample(file);
	if (sound == NULL)
	{

		allegro_message("error loading sound!");
		exit(-1);

	}
	return sound;
}
void Game::playSound(SAMPLE* sound, int playMode)
{
	//voice_set_playMode(int voice
	play_sample(sound, 255, 128, 1000, FALSE);

}