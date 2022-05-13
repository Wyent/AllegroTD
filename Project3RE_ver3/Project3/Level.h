#ifndef LEVEL_H
#define LEVEL_H 1
#include "baseClass.h"

//#include "Bonus.h"

#include "global.h"
#include <allegro.h>

/**board layout eaxample***

//////row0//row1//row2//
col0//
col1//
col2//

***************************/

class Level
{
public:
	int gameBoard[board_width][board_height];
int dotsLeft;

protected:
	//add point cap later
	int score; //the players total score
	int currentLevel; 

 

	BaseClass wall1;

public:	
	Level();
	void init(int level, int numberOfLevels, int totalDots,
					const char* bonus1Sprite, const char* bonus2Sprite, 
					const char* wall1Sprite,  const char* wall2Sprite, const char* wall3Sprite, 
					const char* dotSprite,    const char* PowerPelletSprite);

	Level(int level, int numberOfLevels, int totalDots,
					const char* bonus1Sprite, const char* bonus2Sprite, 
					const char* wall1Sprite,  const char* wall2Sprite, const char* wall3Sprite, 
					const char* dotSprite,    const char* PowerPelletSprite);
	Level(int level, int numberOfLevels, int totalDots,
					const char* bonus1Sprite, const char* bonus2Sprite, 
					const char* wall1Sprite,  const char* wall2Sprite, const char* wall3Sprite, 
					const char* dotSprite,    const char* PowerPelletSprite, int gameBoardArray[board_height][board_width], bool isFlipArray);
	Level(int level, int numberOfLevels, int totalDots,
					const char* bonus1Sprite, const char* bonus2Sprite, 
					const char* wall1Sprite,  const char* wall2Sprite, const char* wall3Sprite, 
					const char* dotSprite,    const char* PowerPelletSprite, int gameBoardArray[board_width][board_height]);
	~Level();

	//initializations////
	void init();
	/////////////////////

	//draws//////////////////////
	void drawBoard(BITMAP* dest);

	/*void drawScore(BITMAP* dest);*/

	/////////////////////////////

	///setters////////////////////

	void setLevel(int newLevel);

	void addScore(int points);

	void subtractScore(int points);

	//board setters///////////////////////////////////////////////////////////////////
	void populateBoard(const int boardArray[][board_height], int rows, int columns);

	void setSquare (int row, int column, int value);

	void setBoard (int boardArray[board_height][board_width]);
	/////////////////////////////////////////////////////////////////////////////////


	//getters/////////////
	int getSquare (int row, int column);
	//int getTotalLevels();
	int getScore();
	int getLevel();



	/////////////////////
	
};

#endif