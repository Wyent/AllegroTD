#ifndef ENEMY_H
#define ENEMY_H 1

#include "Actor.h"
#include <allegro.h>
//#include "Player.h"

class Enemy : public Actor
{
public:

	static void loadEnemySpr();

	//static BITMAP* goblinSprN;
	//static BITMAP* goblinSprE;
	//static BITMAP* goblinSprW;
	//static BITMAP* goblinSprS;

	//static BITMAP* trollSprN;
	//static BITMAP* trollSprE;
	//static BITMAP* trollSprW;
	//static BITMAP* trollSprS;

	//static BITMAP* balrogSprN;
	//static BITMAP* balrogSprE;
	//static BITMAP* balrogSprW;
	//static BITMAP* balrogSprS;

	//static BITMAP* nazgulSprN;
	//static BITMAP* nazgulSprE;
	//static BITMAP* nazgulSprW;
	//static BITMAP* nazgulSprS;

	//static BITMAP* spiderSprN;
	//static BITMAP* spiderSprE;
	//static BITMAP* spiderSprW;
	//static BITMAP* spiderSprS;


	protected:
		// 
		int enemyType; //what can attack it
		/*BITMAP* fleeSprite;
		BITMAP* rejuvSprite;*/
		bool reverseDir;
		int homeSquareRow;
		int homeSquareCol;

		bool isHome; //so not chasing
		int state;   //chase, scatter, flee
		bool goHome;
		
		bool otherSprSet;
		//bool rejuvSpr; //just before returning to the field change

		int curWait;
		int totalHomeWait;
		
		// TD stuff ////////////////////
		int damage; //what damage enemy does upon exit
		int HP;
		int goldAmount;

		///////////////////////////////
	public:
		int getGoldReward();
		int getDamage();
		void Enemy::initEnemy(BITMAP* northSpr, BITMAP* southSpr, BITMAP* eastSpr, BITMAP* westSpr, int homeRow, int homeCol, int homeWait);
		
		// easy constructor //
		Enemy::Enemy( int enemyVersion );
		Enemy();
		~Enemy();

		void draw(BITMAP* dest);

		/*initalize the enemy with array positions*/
		void initEnemy(int row, int col);

		
		void goToField();
		void goToHome();


		void Enemy::update(int gameBoard[board_width][board_height], int targetRow, int targetCol, bool playHasPowerUp, bool playerIsAlive);
		void flee(int gameBoard[board_width][board_height]);
		void scatter(int gameBoard[board_width][board_height]);
		void Enemy::getRandCorner(int & row, int & col);
		
		void restart();

		void changeSpriteStates();

		void Enemy::enemyCollision(int gameBoard[board_width][board_height], Enemy enemy);



		/// HP stuff ////////////
		int Enemy::getHP();
		void Enemy::setHP(int newHP);
		void Enemy::subtractHP( int input);
		void Enemy::addHP( int input);

};

#endif