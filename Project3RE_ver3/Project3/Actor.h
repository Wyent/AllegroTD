#ifndef ACTOR_H
#define ACTOR_H 1

#include "baseClass.h"
#include "global.h"

class Actor : public BaseClass
{
//Fields
protected:
	int state;
	int speed;
	bool motion; //is the player moving
	bool movingToSquare;
	int pixelsMoved; //for moving fluidly from sqare to square

	int direction; //NORTH, WEST, EAST, SOUTH
	int prevDirection;

	bool alive;
	int xSpeed;
	int ySpeed;

	int xDelayCounter;
	int yDelayCounter;

	int xDelay;
	int yDelay;
	//double angle;

	//directional bitmaps// 
	//...these should be set to the real sprite derrived from baseClass
	BITMAP* northSprite;
	BITMAP* southSprite;
	BITMAP* westSprite;
	BITMAP* eastSprite;
	///////////////////////
	int squareRow;
	int squareCol;

	bool targetReached;

//functions
public:

	void setState( int newState);
	int getState();

	Actor::Actor();
	Actor::~Actor();
	//getters
	int getSquareRow();
	int getSquareCol();
	int getDirection();
	int getAlive();
	int getXSpeed();
	int getYSpeed();
	bool hasMotion();
	//setters
	void setDirection(int newDir);
	//void setDirection(int newDir);
	void setAlive (bool newAlive);
	void setXSpeed(int newXSpeed);
	void setYSpeed(int newYSpeed);
	void setMotion(bool newMotion);


	//other functions
	void movement();
	void checkGameBoardCollision(int gameBoard[][board_height], int gameSquareColumns, int gameSquareRows);//each square should be assigned a value
															//.. then if the square has an enemy in it
															//.. check for enemyCol and  destroy accordingly?
															//mybe set a bool(S) in here as to whether you collided with
															//..something other than wall, then make another function(S)
															//to execute if one of those bools is true--one for each col type-- 
	
	void animateMotion();
	bool isNotWall(int targetArray[][board_height], int arrayRows, int arrayColumns, int row, int column); //checks to see if a square is free
	bool Actor::collided(int otherX, int otherY, int otherW, int otherH); //others == what your colliding with

	void Actor::warpSprite();
	void setSquarePos(int row, int col);

//mainly used for enemy functions////////////////////////////////////////////////////

	bool isIntersection(int board[board_width][board_height], int row, int col);
	
	void setPath(int board[board_width][board_height], int row, int col, int targetRow, int targetCol);
	//calls this -->v
	void findPathOptions(int board[board_width][board_height], int row, int col, 
						 bool & northOp, bool & southOp, bool & eastOp, bool & westOp);
	int getDistance(int row1, int row2, int col1, int col2);

	int getShortestPathDir(int northDis, int southDis, int eastDis, int westDis);

	void Actor::getNextSquare(int gameBoard[board_width][board_height], int &row, int &col);

	void reverseDirection();

	bool Actor::hasReachedTarget();
/////////////////////////////////////////////////////////////////////////////////////
};

#endif