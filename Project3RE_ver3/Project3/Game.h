#ifndef GAME_H
#define GAME_H 2
#include "Level.h"
#include <allegro.h>


class Game
{
public:
	Level activeLevel;
protected:
 
	
	int currentLevel;
	Level levels[5]; //title, 1-3, credits

	
	//vector<Level> levels;
	int totalLevels;
	bool levelTransition;
	bool titleOrEnd;

public:
	//int score;
	
	

	//background sounds for each level
public:
	//constructor
	Game(int numberOfLevels, Level firstLevel, bool titleOrEnd);

	~Game();
	Game(); //must call init after

	void init(int numberOfLevels, Level firstLevel, bool titleOrEnd);


	//getters//////////////
	int getCurrentLevel();
	Level getLevel(int level);
	int getTotalLevels();

	bool isLevelTransition();
	bool isTitleOrEnd();
	//////////////////////////
	//setters//////////////////////////////////
	void setLevel(Level level, int levelNumber);
	
	void setTransitioning(bool isTransitioning);
	void setTitleOrEnd(bool isTitleOrEnd);
	////////////////////////////////////////////
	void Game::update();
	//OtherFunctions///////////////////////////
	

	bool skipToLevel(int levell);
	//bool skipToLevel(int levell);

	void Game::transitionLevel(BITMAP* dest);
	void Game::transitionLevel(const char* frame, void* callbackFunction());
	void Game::transitionLevel(const char* cutsceneFrames[], int size);
	void Game::transitionLevel(const char* cutsceneFrames[], int size, void* callbackFunction());

	void Game::transitionLevelInput(const char* frame, void* callbackFunction());
	void Game::transitionLevelInput(const char* cutsceneFrames[], int size, void* callbackFunction());
	void Game::transitionLevelInput(const char* cutsceneFrames, void* callbackFunction(), int theKey);

	void Game::fade_out(int speed, int color);
	void Game::fade_in(BITMAP *bmp_orig, int speed, int color);
	//CUTSCENE FUNCTIONS/////////////////////////////////////////////////////////////////////
	//should pause the other stuff
	void cutsceneFrame(int time, BITMAP* frame);
	void cutsceneFrame(int time, const char* frame);
	void Game::cutsceneFrame(int time, BITMAP* frame, void* callbackFunction());
	void Game::cutsceneFrame(int time, const char* frame, void* callbackFunction());
	/////////////////////////////////////////////////////////////////////////////////////////

	//helps cutscene function
	bool setSprite(BITMAP* bitmapToSet, const char* filename);
	BITMAP* Game::getSprite(const char* filename);

	static void Game::playSound(SAMPLE* sound, int playMode);
	static void playSound(const char* wavFile);
	static SAMPLE* loadSound(const char* file);
};

#endif