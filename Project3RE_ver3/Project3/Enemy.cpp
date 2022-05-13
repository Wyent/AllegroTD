#include "Enemy.h"
#include <time.h>
// static function

	static BITMAP* goblinSprN;
	static BITMAP* goblinSprE;
	static BITMAP* goblinSprW;
	static BITMAP* goblinSprS;

	static BITMAP* trollSprN;
	static BITMAP* trollSprE;
	static BITMAP* trollSprW;
	static BITMAP* trollSprS;

	static BITMAP* balrogSprN;
	static BITMAP* balrogSprE;
	static BITMAP* balrogSprW;
	static BITMAP* balrogSprS;

	static BITMAP* nazgulSprN;
	static BITMAP* nazgulSprE;
	static BITMAP* nazgulSprW;
	static BITMAP* nazgulSprS;

	static BITMAP* spiderSprN;
	static BITMAP* spiderSprE;
	static BITMAP* spiderSprW;
	static BITMAP* spiderSprS;


void Enemy::loadEnemySpr()
{
	goblinSprN = load_bitmap("Enemy1_n.bmp", NULL);
	goblinSprE = load_bitmap("Enemy1_e.bmp", NULL);
	goblinSprW = load_bitmap("Enemy1_w.bmp", NULL);
	goblinSprS = load_bitmap("Enemy1_s.bmp", NULL);

	trollSprN = load_bitmap("troll_n.bmp", NULL);
	trollSprE = load_bitmap("troll_e.bmp", NULL);
	trollSprW = load_bitmap("troll_w.bmp", NULL);
	trollSprS = load_bitmap("troll_s.bmp", NULL);

	balrogSprN = load_bitmap("Enemy1_n.bmp", NULL);
	balrogSprE = load_bitmap("Enemy1_e.bmp", NULL);
	balrogSprW = load_bitmap("Enemy1_w.bmp", NULL);
	balrogSprS = load_bitmap("Enemy1_s.bmp", NULL);

	nazgulSprN = load_bitmap("Enemy1_n.bmp", NULL);
	nazgulSprE = load_bitmap("Enemy1_e.bmp", NULL);
	nazgulSprW = load_bitmap("Enemy1_w.bmp", NULL);
	nazgulSprS = load_bitmap("Enemy1_s.bmp", NULL);

	spiderSprN = load_bitmap("spider_n.bmp", NULL);
	spiderSprE = load_bitmap("spider_e.bmp", NULL);
	spiderSprW = load_bitmap("spider_w.bmp", NULL);
	spiderSprS = load_bitmap("spider_s.bmp", NULL);

}


Enemy::Enemy( int enemyVersion )
{
	xDelay = 0;
	yDelay = 0;

	width = 64;
	height = 64;

	frameDelay  = 50;
	maxFrame    = 0;
	animColumns = 1;

	direction   = STOP;


	squareRow	 = ENEMY_START_ROW; //index 15
	squareCol    = ENEMY_START_COL; //index 11

	sprite		 = northSprite;

	movingToSquare = false;
	
	pixelsMoved    = 0;

  //////Enemy stuff////////////////////////
	homeSquareRow  =  ENEMY_START_ROW;
	homeSquareCol  =  ENEMY_START_COL;

	isHome    = false; //so not chasing
	state     = CHASE; //chase, scatter, flee
	goHome    = false;

	curWait       = 0;
	totalHomeWait = 0;
	reverseDir = false;
  /////////////////////////////////////
	otherSprSet = false;
	restart();

	//TD////////////////////
	enemyType = GENERIC;
	damage = 10;
   
	goldAmount = 25; //change this later

	if ( enemyVersion == SPIDER )
	{
		     HP		= 50; //should be passed in
			 ySpeed = 2;
			 xSpeed = 2;

			 xDelay = 0;
			 yDelay = 0;

			 northSprite = spiderSprN;
			 southSprite = spiderSprS;
			 eastSprite  = spiderSprE;
			 westSprite  = spiderSprW;


	}

	else if ( enemyVersion == GOBLIN )
	{
		    HP = 75; //should be passed in
			ySpeed = 2;
			xSpeed = 2;

			xDelay = 1;
			yDelay = 1;
			
		    northSprite  = goblinSprN;
			 southSprite = goblinSprS;
			 eastSprite  = goblinSprE;
			 westSprite  = goblinSprW;
	}

	else if ( enemyVersion == TROLL )
	{
		    HP = 150; //should be passed in
			// slow with a lot of HP
			ySpeed = 2;
			xSpeed = 2;

			xDelay = 2;
			yDelay = 2;

		     northSprite = trollSprN;
			 southSprite = trollSprS;
			 eastSprite  = trollSprE;
			 westSprite  = trollSprW;
	}

	else if ( enemyVersion == BALROG )
	{
		HP = 150; //should be passed in
		ySpeed = 1;
		xSpeed = 1;

		xDelay = 1;
		yDelay = 1;

		northSprite = balrogSprN;
		southSprite = balrogSprS;
		eastSprite  = balrogSprE;
		westSprite  = balrogSprW;
	}
	else if ( enemyVersion == NAZGUL )
	{
		    HP = 150; //should be passed in
			ySpeed = 2;
			xSpeed = 2;
			xDelay = 1;
			yDelay = 1;
			northSprite = nazgulSprN;
			southSprite = nazgulSprN;
			eastSprite  = nazgulSprN;
			westSprite  = nazgulSprN;
	}
	else
	{
			northSprite = nazgulSprN;
			southSprite = nazgulSprN;
			eastSprite  = nazgulSprN;
			westSprite  = nazgulSprN;
	}
	//else if ( enemyVersion == SPIDERS )
}


void Enemy::initEnemy(BITMAP* northSpr, BITMAP* southSpr, BITMAP* eastSpr, BITMAP* westSpr, int homeRow, int homeCol, int homeWait)
{
	/*rejuvSprite = create_bitmap(32,32);
	clear_to_color(rejuvSprite, makecol(255, 0, 250));

	fleeSprite = create_bitmap(32,32);
	clear_to_color(fleeSprite, makecol(255, 0, 0));*/


	ySpeed = 1;
	xSpeed = 1;

	xDelay = 0;
	yDelay = 0;

	northSprite = northSpr;
	southSprite = southSpr;
	eastSprite  = eastSpr;
	westSprite	= westSpr;

	frameDelay  = 50;
	//maxFrame    = 0;
	//animColumns = 1;
	direction   = STOP;


	squareRow	 = min_board_y / 2; //index 15
	squareCol    = min_board_x / 2; //index 11


	sprite = northSprite;

	movingToSquare = false;

	
	pixelsMoved    = 0;

  //////Enemy stuff////////////////////////
	homeSquareRow  =  homeRow;
	homeSquareCol  =  homeCol;

	isHome    = true; //so not chasing
	state     = CHASE; //chase, scatter, flee
	goHome    = false;

	curWait   = 0;
	totalHomeWait = homeWait;
	reverseDir = false;
  /////////////////////////////////////
	otherSprSet = false;
	restart();

	//TD////////////////////
	enemyType = GENERIC;
	damage = 10;
    HP = 50; //should be passed in
	goldAmount = 25; //change this later

}

int Enemy::getDamage()
{
	return damage;
}

//#include "Enemy.h"


Enemy::Enemy()
{
	
	
	Actor::xSpeed = 0;
	Actor::xSpeed = 0;

	//movementPath[moveCount] = STOP;
}

Enemy::~Enemy()
{

}



void Enemy::initEnemy(int row, int col)
{

	setSquarePos(row,col);
	/*startX = row;
	startY = col;*/

}

void  Enemy::draw(BITMAP* dest)
{
	if (!isHome)
	{
		drawFrame(dest);
		textprintf(dest, font, x+width, y +height/2, makecol(255,255,255), "HP: %d", HP);
	}
}


void Enemy::update(int gameBoard[board_width][board_height], int targetRow, int targetCol, bool playHasPowerUp, bool playerIsAlive)
{
	if (!playerIsAlive)
		alive = false;
	//else
		//goHome = true;
	if (playHasPowerUp && !isHome)
	{
		state = FLEE;
	}
	else 
	{
		state = CHASE;
	}

	if (!isHome)
	{
		switch (state)
		{
		case CHASE:
			if ( isIntersection(gameBoard, squareRow, squareCol)  || direction == STOP )
			{
				int r = squareRow;
				int c = squareCol;
				//getNextSquare(gameBoard, r,c);
				setPath( gameBoard, r, c, targetRow, targetCol );
			}
			break;
		case FLEE:
			flee(gameBoard);
			break;
		}
		if (!alive)
		{
			//state = CHASE;
			goHome = true;
		    if ( isIntersection(gameBoard, squareRow, squareCol)  || direction == STOP )
			{
				int r = ENEMY_START_ROW; //should be random later
				int c = ENEMY_START_COL;
				//getNextSquare(gameBoard, r,c);
				setPath( gameBoard, squareRow, squareCol, r, c );
			}
			goToHome();
		}
////////////////////////////////////////
		if (reverseDir)
		{
			if (pixelsMoved == 32)
			{
				reverseDirection();
				reverseDir = false;
					
			}
		}

	}
		warpSprite();
		checkGameBoardCollision(gameBoard, board_width, board_height);
		
		movement();
		changeSpriteStates();
		//animateMotion();
		goToField();

}

void Enemy::goToField()
{

	if (isHome)
	{
		if (++curWait > totalHomeWait)
		{

			curWait = 0;
			isHome = false;
			//squareRow = ENEMY_START_ROW;
			//squareCol = ENEMY_START_COL;
			setSquarePos(ENEMY_START_ROW, ENEMY_START_COL);
		}
	}
}
void Enemy::goToHome()
{

	if (squareRow == ENEMY_START_ROW  &&  squareCol == ENEMY_START_COL)
	{
		restart();
		/*setSquarePos(homeSquareRow, homeSquareCol);
		isHome = true;
		alive = true;*/
	}
}

void Enemy::flee(int gameBoard[board_width][board_height])
{
	
	if( !goHome )
	if ( isIntersection(gameBoard, squareRow, squareCol)  || direction == STOP )
			{
				int r = squareRow;
				int c = squareCol;
				getRandCorner(r, c);
				//getNextSquare(gameBoard, r,c);
				setPath( gameBoard, squareRow, squareCol, r, c );
			}
}

void Enemy::scatter(int gameBoard[board_width][board_height])
{

}

void Enemy::getRandCorner(int & row, int & col)
{
	srand(time(NULL));
	int randNum = 1 + rand() % (2);
	
	switch (randNum)
	{
	case 1: 
		row = E_CORNER_ROW;
		break;
	case 2:
		row = W_CORNER_ROW ;
		break;
	}

	randNum = 1 + rand() % (2);
	switch (randNum)
	{
	case 1: 
		col = S_CORNER_COL ;
		break;
	case 2:
		 col =  N_CORNER_COL;
		 break;
	}

}

void Enemy::restart()
{
	pixelsMoved    = 0;

  //////Enemy stuff////////////////////////
//	homeSquareRow  =  homeRow;
//	homeSquareCol  =  homeCol;

	isHome    = true; //so not chasing
	state     = CHASE; //chase, scatter, flee
	goHome    = false;
	alive     = true;
	curWait   = 0;
	//totalHomeWait = homeWait;
	setSquarePos(homeSquareRow, homeSquareCol);
		movingToSquare = false;

	

}

void Enemy::changeSpriteStates()
{
			if (goHome)
			{
				//if (!otherSprSet)
				//{
					maxFrame = 0;
					loadSprite("bmps/enemies/all/eyes1.bmp");
					otherSprSet = true;
				//}
			}
	//static bool set = false;
	/*if (state == FLEE)
	{*/
		//if (sprite != NULL)
		//	destroy_bitmap(sprite);

	//	if (!otherSprSet)
	//	{
	//		
	//		//else
	//		{
	//			maxFrame = 0;
	//			sprite   = fleeSprite;
	//			//loadSprite("bmps/enemies/all/eyes1.bmp");
	//			otherSprSet = true;
	//		}
	//	}
	//	
	//}
	//else if(isHome)
	//{
	//	if (curWait  >= totalHomeWait / 2)
	//	{
	//		sprite = rejuvSprite;
	//		maxFrame = 0;
	//
	//	}
	//}

	/*else if (goHome)
	{
		if (!otherSprSet)
		{
			maxFrame = 0;
			loadSprite("bmps/enemies/all/eyes1.bmp");
			otherSprSet = true;
		}
	}*/
	else
	{
		animateMotion();
		otherSprSet = false;
	}
}


void Enemy::enemyCollision(int gameBoard[board_width][board_height], Enemy enemy )
{
	if (!isHome  &&  !goHome)	
//	if ( isIntersection(gameBoard, squareRow, squareCol)  || direction == STOP )
	{
		//if ( collided(enemy.getX(), enemy.getY(), enemy.getWidth(), enemy.getHeight())  )
			if (squareRow == enemy.getSquareRow()   &&   squareCol == enemy.getSquareCol() ) 
			{
			
				//if (pixelsMoved == block_size)
				//{
				//	//reverseDirection();
				////	direction     = STOP;
				////	prevDirection = STOP;
				//	reverseDir = true;
				//	//setSquarePos( squareRow, squareCol);
				//}
				////int r = 0;
				//int c = 0;
				//getNextSquare(gameBoard, r, c);
			    //	setSquarePos(r, c);
		        //movingToSquare = false;
		

				
				//set target to the reverse dir
			//	setPath(gameBoard, squareRow, squareCol, r, c);
			//	setSquarePos(r, c);
					//totalHomeWait = homeWait;

			}
	}
}

int Enemy::getHP()
{
	return HP;
}

// Setters //////////////////////////
void Enemy::setHP(int newHP)
{
	HP = newHP;
}

void Enemy::subtractHP( int input)
{
	HP -= input;
}
void Enemy::addHP( int input)
{
	HP += input;
}

int Enemy::getGoldReward()
{
	//shold do randomization later
	return goldAmount;
}