//#include <allgero.h>
#include "Actor.h"
#include <math.h>

//functions
//Actor::Actor()
//{
//	direction = 0;
//	alive 	  = true;
//	xSpeed    = 0;
//	ySpeed    = 0;
//}
Actor::Actor()
{
	//index into the board array//
    squareRow = 0;
	squareCol = 0;
	//////////////////////////////
	direction = STOP; //NORTH, WEST, EAST, SOUTH
	prevDirection = STOP;
	alive	  = true;
	xSpeed	  = 0;
	ySpeed	  = 0;
	motion = false;
	movingToSquare = false;
	pixelsMoved    = 0;

    xDelayCounter = 0;
	yDelayCounter = 0;
	
	xDelay = 0;
	yDelay = 0;
	//****************
	state = 0;
	speed = 0;

	targetReached = false;
}
void Actor::setState( int newState)
{
	state = newState;
}
int Actor::getState()
{
	return state;
}

Actor::~Actor()
{
	//if (westSprite != NULL)
	//{
	//	destroy_bitmap(westSprite);
	//	}
	//if (eastSprite != NULL)
	//	destroy_bitmap(eastSprite);
	//if (northSprite != NULL)
	//	destroy_bitmap(northSprite);
	//if (southSprite != NULL)
	//	destroy_bitmap(southSprite);
}

//getters/////////////////////////////////////
int Actor::getSquareRow()
{
	return squareRow;
}
int Actor::getSquareCol()
{
	return squareCol;
}
int Actor::getDirection(){
	return direction;
}
int Actor::getAlive(){
	return alive;
}
int Actor::getXSpeed(){
	return xSpeed;
}
int Actor::getYSpeed(){
	return ySpeed;
}
bool Actor::hasMotion()
{
	return motion;
}

//////////////////////////////////////////////

//Setters/////////////////////////////////////
void Actor::setDirection(int newDir){
	direction = newDir;
}

void Actor::setAlive(bool newAlive){
	if (newAlive == true || newAlive == false){
		alive = newAlive;
	}
	else {
		newAlive = false;	
	}
}

void Actor::setXSpeed(int newXSpeed){
	xSpeed = newXSpeed;
}

void Actor::setYSpeed(int newYSpeed){
	ySpeed = newYSpeed;
}

void Actor::setMotion(bool newMotion)
{
	motion = newMotion;
}
//////////////////////////////////////////////



////////other functions///////////////////////
bool Actor::isNotWall(int targetArray[][board_height], int arrayRows, int arrayColumns, int row, int column){
	if (row < arrayRows && column < arrayColumns)
	{
		if (targetArray[row][column] != WALL_1)
			if (targetArray[row][column] != WALL_2)
				if (targetArray[row][column] != WALL_3)
					return true; 
	}
	return false; //square is occupied
}

void Actor::movement()
{
	
	if (motion){

		
		if (direction == NORTH){
			if (++yDelayCounter >= yDelay) {
			//setY(getY() + -getYSpeed());//
				y -= ySpeed;
				pixelsMoved += ySpeed;
				yDelayCounter = 0;
			}
		}
		else if (direction == SOUTH){
			if (++yDelayCounter >= yDelay) {
				y += ySpeed;
				pixelsMoved += ySpeed;
				yDelayCounter = 0;
			}
		}
		else if (direction == EAST){
			if (++xDelayCounter >= yDelay) {
			x += xSpeed;
			pixelsMoved += xSpeed;
			xDelayCounter = 0;

			}

		}
		else if (direction == WEST){
			if (++xDelayCounter >= yDelay) {
				x -= xSpeed;
				pixelsMoved += xSpeed;	
				xDelayCounter = 0;

			}
		}

	}
	//reset pixelMoved
	if (pixelsMoved >= block_size){
		movingToSquare = false;
		
	}
}


//if there is a wall collision set motion to false;
void Actor::checkGameBoardCollision(int gameBoard[][board_height], int gameSquareRows , int gameSquareColumns)
{
	//depending on direction, check for colision in appropriate square

		//NORTH

	if (movingToSquare == false)
	{
		if (direction == NORTH){ // check square above player
			
			if ( isNotWall(gameBoard, gameSquareRows, gameSquareColumns, squareRow, squareCol-1) ){
					squareRow	 = squareRow; //index 15
					squareCol    = squareCol-1; //index 11
					motion = true;
					movingToSquare = true;
					pixelsMoved = 0;
			}

			else {
					motion = false;
					direction = STOP;
			}

		}
		//SOUTH
		else if (direction == SOUTH){ //check square below player
			if ( isNotWall(gameBoard, gameSquareRows, gameSquareColumns, squareRow, squareCol+1) ){
					squareRow	 = squareRow; //index 15
					squareCol    = squareCol+1;
					motion = true;
					movingToSquare = true;
					pixelsMoved = 0;
			}
			else {
					motion = false;
					direction = STOP;
			}
		}
		//EAST
		else if (direction == EAST){ //check square to right of player
			if ( isNotWall(gameBoard, gameSquareRows, gameSquareColumns, squareRow+1, squareCol) ){
					squareRow	 = squareRow + 1 ; //index 15
					squareCol    = squareCol;
					motion = true;
					movingToSquare = true;
					pixelsMoved = 0;
			}
			else {
					motion = false;
					direction = STOP;
			}

		}
		//WEST
		else if (direction == WEST){ //check square left of player
			if ( isNotWall(gameBoard, gameSquareRows, gameSquareColumns, squareRow-1, squareCol) ){

					squareRow	 = squareRow - 1 ; //index 15
					squareCol    = squareCol;	
					motion = true;
					movingToSquare = true;
					pixelsMoved = 0;
			}
			else {
					motion = false;
					direction = STOP;
			}

		}
	}

}

//if  motion-- make sprite animate
void Actor::animateMotion()
{
	if (motion && direction != STOP){
	//	maxFrame = 3;
	}
	else {
		maxFrame = 0;

	}

	if (direction == NORTH || direction == STOP){
		sprite = northSprite;
	}
	else if (direction == SOUTH){
		sprite = southSprite;
	}
	else if (direction == EAST){
		sprite = eastSprite;
	}
	else if (direction == WEST){
		sprite = westSprite;
	}
}

///////////////////////////////////////////
// Colision ///////////////////////////////

bool Actor::collided(int otherX, int otherY, int otherW, int otherH) //others == what your colliding with
{
	//bottom to other's top
	if (y + height < otherY) {
		return false;
	}
	//top to other's bottom
	if (y > otherY + otherH) {
		return false;
	}
	//right to other's left
	if (x + width < otherX) {
		return false;
	}
	//left to other's right
	if (x > otherX + otherW) {
		return false;
	}

	//there is a collision
	return true;

}
void Actor::warpSprite()
{
	if  (pixelsMoved == block_size)
	if(motion == true)
	{
		if(squareRow == board_width-1)
		{
			if (direction == EAST)
			{
				   motion = false;
				   squareRow = 0;
				   x = block_size;
				   pixelsMoved = block_size;
				   movingToSquare = false;
			}
		}

		else if(squareRow == 0)
		{
			if(direction == WEST)
			{
				
				motion = false;
				squareRow = board_width -1;
				x = board_width * block_size - block_size*0;
				pixelsMoved = block_size;
				movingToSquare = false;

			}
		}

		//vertical
		else if (squareCol == 0)
		{
			if (direction == NORTH)
			{

				motion = false;
				squareCol = board_height - 1;
				y = board_height * block_size - block_size*1;
				pixelsMoved = block_size;
				movingToSquare = false;

			}

		}
		else if (squareCol == board_height-1)
		{
			if (direction == SOUTH)
			{

				motion = false;
				squareCol = 0;
				y = board_height * block_size * squareCol;
				pixelsMoved = block_size;
				movingToSquare = false;

			}

		}
	}
}


void Actor::setSquarePos(int row, int col)
{

	squareRow	 = row; //index 15
	squareCol    = col; //index 11
	
	x = squareRow * block_size + block_size;
	y = squareCol * block_size; //- block_size*2;
	
	direction = false;
	pixelsMoved    = block_size;
	motion = false;
	movingToSquare = false;

}

//mainly used for enemy functions////////////////////////////////////////////////////

bool Actor::isIntersection(int board[board_width][board_height],int row, int col)
{
		int paths = 0;
	//NORTH
		if ( isNotWall(board, board_width, board_height, row, col -1) )
		{
			paths++;
		}
	//SOUTH
		if ( isNotWall(board, board_width, board_height, row, col +1) )
		{
			paths++;
		}
	//EAST
		if ( isNotWall(board, board_width, board_height, row +1, col) )
		{
			paths++;
		}
	//WEST
	    if ( isNotWall(board, board_width, board_height, row-1, col) )
		{
			paths++;
		}

		//subtract 1 path that it just came from
		paths--;
		////////////////////////////////////////

		if (paths > 1)
		{
			return true;
		}
			
		return false;

}
	
void Actor::setPath(int board[board_width][board_height], int row, int  col, int targetRow, int targetCol)
{
	bool northPath = false;
	bool southPath = false;
	bool eastPath  = false;
	bool westPath  = false;

	findPathOptions(board, row, col, northPath, southPath, eastPath, westPath);

	///Stores the distances to the target
	int northDistance = 0;
	int southDistance = 0;
	int eastDistance  = 0;
	int westDistance  = 0;
///////////////////////////////////////////////////////////////////////////////
//***********get th path distances
	//north/
	if (northPath)
	{
		northDistance = getDistance(row, targetRow, col-1, targetCol);
	}
	else
	{
		northDistance = board_width * board_height;
	}
	/////////////////////////////////////////////////////////////////////////
	//south
	if (southPath)
	{
		southDistance = getDistance(row, targetRow, col+1, targetCol);
	}
	else
	{
		southDistance = board_width * board_height;
	}
	/////////////////////////////////////////////////////////////////////////
	//east
	if (eastPath)
	{
		eastDistance = getDistance(row +1, targetRow, col, targetCol);
	}
	else
	{
		eastDistance = board_width * board_height;
	}
	/////////////////////////////////////////////////////////////////////////
	//west
	if (westPath)
	{
		westDistance = getDistance(row -1, targetRow, col, targetCol);
	}
	else
	{
		westDistance = board_width * board_height;
	}
	/////////////////////////////////////////////////////////////////////////
  //**********

  //set direction to shortest path
	if (pixelsMoved == block_size)
	{
		

		direction = getShortestPathDir(northDistance, southDistance, eastDistance, westDistance); 
		prevDirection = direction;
		//motion = true;
	}
	//if any distance = 0, set targetReched to true;
	if (northDistance == 0   ||    southDistance == 0  
		 ||   eastDistance == 0   ||   westDistance == 0)
		 targetReached = true;

}
//calls this --

void Actor::findPathOptions(int board[board_width][board_height], int row, int col, 
						bool & northOp, bool & southOp, bool & eastOp, bool & westOp)
{
	//NORTH
		if ( isNotWall(board, board_width, board_height, row, col -1) )
		{
			northOp = true;
		}
		else
		{
			northOp = false;
		}
	//SOUTH
		if ( isNotWall(board, board_width, board_height, row, col +1) )
		{
			southOp = true;
		}
		else
		{
			southOp = false;
		}
	//EAST
		if ( isNotWall(board, board_width, board_height, row +1, col) )
		{
			eastOp = true;
		}
		else
		{
			eastOp = false;
		}
	//WEST
	    if ( isNotWall(board, board_width, board_height, row-1, col) )
		{
			westOp = true;
		}
		else
		{
			westOp = false;
		}

	//set direction just came from to false
		if (direction == NORTH    ||    (direction == STOP  &&  prevDirection == NORTH))
		{
			southOp = false;
		}
		if (direction == SOUTH    ||    (direction == STOP  &&  prevDirection == SOUTH))
		{
			northOp = false;
		}
		if (direction == WEST    ||    (direction == STOP  &&  prevDirection == WEST))
		{
			eastOp = false;
		}
		if (direction == EAST    ||    (direction == STOP  &&  prevDirection == EAST))
		{
			westOp = false;
		}
}

int Actor::getDistance(int row1, int row2, int col1, int col2)
{
	return sqrt( pow((double)(row2 - row1), 2) + pow((double)(col2 - col1), 2) );
}

int Actor::getShortestPathDir(int northDis, int southDis, int eastDis, int westDis)
{
	if (northDis <= southDis  &&  northDis <= eastDis  &&  northDis <= westDis)
	{
		return NORTH;
	}
		if (southDis <= northDis  &&  southDis <= eastDis  &&  southDis <= westDis)
	{
		return SOUTH;
	}
	if (eastDis <= southDis  &&  eastDis <= northDis  &&  eastDis <= westDis)
	{
		return EAST;
	}
	if (westDis <= northDis  &&  westDis <= eastDis  &&  westDis <= westDis)
	{
		return WEST;
	}
	else
		return STOP;
}

void Actor::getNextSquare(int gameBoard[board_width][board_height], int &row, int &col)
{
	if (direction == NORTH)
	{	
		 if (isNotWall(gameBoard, board_width, board_height, row, col-1) )
			col -= 1;
	}
	else if (direction == SOUTH)
	{
		 if (isNotWall(gameBoard, board_width, board_height, row, col+1) )
			col += 1;
	}
	else if (direction == EAST)
	{
		 if (isNotWall(gameBoard, board_width, board_height, row+1, col) )
			row += 1;
	}
	else if (direction == WEST)
	{
		 if (isNotWall(gameBoard, board_width, board_height, row-1, col) )
			row -= 1;
	}
}

void Actor::reverseDirection()
{
	if(direction == NORTH)
	{
		direction = SOUTH;
	}
	else if (direction == SOUTH)
	{
		direction = NORTH;
	}
	else if (direction == EAST)
	{
		direction = WEST;
	}
	else if (direction == WEST)
	{
		direction = EAST;
	}
}


bool Actor::hasReachedTarget()
{
	return targetReached;
}
/////////////////////////////////////////////////////////////////////////////////////
