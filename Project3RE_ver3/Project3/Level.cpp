#include "Level.h"
#include <allegro.h>

Level::Level ()
{
	score = 0;
		
	currentLevel = 0; 
	
}

///constructors////////////////////////////////////////////////////////////////////////////////
void Level::init(int level, int numberOfLevels, int totalDots,
					const char* bonus1Sprite, const char* bonus2Sprite, 
					const char* wall1Sprite,  const char* wall2Sprite, const char* wall3Sprite, 
					const char* dotSprite,    const char* PowerPelletSprite)
{
	
	score = 0;

	wall1.init(0,0,block_size,block_size, wall1Sprite,1,0);



}
Level::Level(int level, int numberOfLevels, int totalDots,
					const char* bonus1Sprite, const char* bonus2Sprite, 
					const char* wall1Sprite,  const char* wall2Sprite, const char* wall3Sprite, 
					const char* dotSprite,    const char* PowerPelletSprite)
{

	init( level,  numberOfLevels,  totalDots,
					 bonus1Sprite, bonus2Sprite, 
					 wall1Sprite,   wall2Sprite, wall3Sprite, 
					 dotSprite,     PowerPelletSprite);


}

Level::Level(int level, int numberOfLevels, int totalDots,
					const char* bonus1Sprite, const char* bonus2Sprite, 
					const char* wall1Sprite,  const char* wall2Sprite, const char* wall3Sprite, 
					const char* dotSprite,    const char* PowerPelletSprite, int gameBoardArray[board_height][board_width], bool isFlipArray)
{
	init( level,  numberOfLevels,  totalDots,
					 bonus1Sprite, bonus2Sprite, 
					 wall1Sprite,   wall2Sprite, wall3Sprite, 
					 dotSprite,     PowerPelletSprite);
	setBoard(gameBoardArray);
}

Level::Level(int level, int numberOfLevels, int totalDots,
					const char* bonus1Sprite, const char* bonus2Sprite, 
					const char* wall1Sprite,  const char* wall2Sprite, const char* wall3Sprite, 
					const char* dotSprite,    const char* PowerPelletSprite, int gameBoardArray[board_width][board_height])
{
		init( level,  numberOfLevels,  totalDots,
					 bonus1Sprite, bonus2Sprite, 
					 wall1Sprite,   wall2Sprite, wall3Sprite, 
					 dotSprite,     PowerPelletSprite);
		populateBoard(gameBoardArray, board_width, board_height);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Level::~Level()
{
}

//initializations////
void Level::init(){

}
/////////////////////

//updates////////////////////

/////////////////////////////

//draws//////////////////////
void Level::drawBoard(BITMAP* dest)
{
	static bool set = false;

	for (int r=0; r < board_width; r++)
	 {
		for (int c=0; c<board_height; c++)
		{

			
			if (false){
				gameBoard[r][c] = WALL_1;//0 + rand() % 8;
				
			
				gameBoard[29][ min_board_x / 2]       = EMPTY;  ///right edge
				gameBoard[0][ min_board_x / 2]       = EMPTY;  ///left edge
				gameBoard[10][ 0]       = EMPTY;  ///top edge
				gameBoard[10][ board_height -1]       = EMPTY;  ///top edge

				//rows are width, height = columns
				gameBoard[board_width / 2 -1][ board_height / 2 +4]       = EMPTY;  //start square
				gameBoard[board_width / 2 -2][ board_height / 2 +4]       = EMPTY;
				gameBoard[board_width / 2 ] [ board_height / 2 +4]        = EMPTY;
				gameBoard[board_width / 2-1][ board_height / 2 +5]        = EMPTY;
				gameBoard[board_width / 2-1][ board_height / 2 +3]        = EMPTY;
				
				gameBoard[board_width / 2-1][ board_height / 2 +4]        = EMPTY;

				gameBoard[board_width / 2-2][ board_height / 2 +4]        = BONUS_1;

				gameBoard[board_width / 2-3][ board_height / 2 +4]        = EMPTY;
				gameBoard[board_width / 2-4][ board_height / 2 +4]        = EMPTY;
				gameBoard[board_width / 2-5][ board_height / 2 +4]        = EMPTY;

				gameBoard[board_width / 2-1][ board_height / 2 +5]        = EMPTY;
				gameBoard[board_width / 2-1][ board_height / 2 +6]        = EMPTY;
				gameBoard[board_width / 2-1][ board_height / 2 +7]        = EMPTY;
				gameBoard[board_width / 2-1][ board_height / 2 +8]        = EMPTY;
				gameBoard[board_width / 2-1][ board_height / 2 +9]        = EMPTY;

			}
			if(gameBoard[r][c]!=false)
			{
				if (gameBoard[r][c] == WALL_1 || gameBoard[r][c] == WALL_2 || gameBoard[r][c] == WALL_3)
				{
					wall1.drawFrame(dest,block_size + r*block_size, c*block_size);
				}

			}
		}
		
	 }
	set = true;

}


void Level::addScore(int points)
{
		score += points;
}

void Level::subtractScore(int points){
	if (score - points >= 0)
		addScore( (points*-1) );
	else 
		score = 0;
}

//board setters//
void Level::populateBoard(const int boardArray[][board_height], int rows, int columns)
{
	if (rows == min_board_x && columns == min_board_y)
		for (int r = 0; r < rows; r++){

			for (int c = 0; c < columns; c++)
				gameBoard[r][c] = boardArray[r][c];
		}
}

int Level::getSquare (int row, int column)
{
	return gameBoard[row][column];
}

void Level::setSquare (int row, int column, int value)
{
	if (row < board_width && column < board_height)
		gameBoard[row][column] = value;
}

void Level::setBoard (int boardArray[board_height][board_width])
{
	for (int r = 0; r < board_width; r++)
		for (int c = 0; c < board_height; c++)
			gameBoard[r][c] = boardArray[c][r];
}

//getters/////////////
int Level::getScore(){
	return score;
}
int Level::getLevel(){
	return currentLevel;
}
