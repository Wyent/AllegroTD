#include "Actor.h"
#include "Enemy.h"
#include <math.h>

#ifndef PROJECTILE_H 
#define PROJECTILE_H 1

#define PI 3.1415926535
#define ANGLE_STEP 1

/*class Projectile : public Actor
{
public:
	Projectile(void);
	~Projectile(void);


	int direction;
	double angle;
	double targetDistance;
	double xAdvance, yAdvance;
	double distanceTraveled;
	int xDistance, yDistance;

	//Player target;
	double xPos, yPos;

	int speed;
	int damage;
	int targetX; 
	int targetY;
	int faceAngle;
	int getDamage();



	Projectile::Projectile( int row, int col, int damageAmount, int tarX, int tarY);
	void setSlopeXAndY();

	//setTarget(int tarX, int tarY);
	void updateTarget (int tarX, int tarY);

	void setTarget( int x, int y );
	void Projectile::drawFrameR(BITMAP* dest);
//	void setTarget(Player&);
	void setTargetDistance(double);
	void findDirection();
	void setDirection(int);
	void setAngle(double);
	void setXAdvance(int);
	void setYAdvance(int);
	void update();
	void advance();
	double Projectile::findAngle();

};

//class  Projectile :public Actor
//{
//
//protected:
//	double xPos, yPos;
//	double velx, vely;
//    int faceAngle;
//	int moveAngle;
//	int damage;
//
//	int disTravelled;
//	int disToTravel;
//
//	bool targetSet;
//	int targetXPos;
//	int targetYPos;
//
//public:
//	Projectile::Projectile( int row, int col, int damageAmount);
//	~Projectile(void);
//

//	void Projectile::drawFrame(BITMAP* dest);
//	void update();
//	void lockOnTarget(int targetX, int targetY);
//	
//	int Projectile::getCenterXPos();
//	int Projectile::getCenterYPos();
//
//};*/

class Projectile : public Actor
{
public:
	//Projectile(void);
	Projectile(Enemy &target, int state, int targetDistance, double angle, double xDistance, double yDistance, int x, int y);
	~Projectile(void);
	int direction;
	double angle;
	double targetDistance;
	double xAdvance, yAdvance;
	double distanceTraveled;
	double xDistance, yDistance;
	//int target; //index of target in enemy array
	Enemy* target;
	int damage;
	BITMAP* arrowArt;

	void setTarget(Enemy&);
	//void setTarget(int);
	void setTargetDistance(double);
	//void findDirection();
	void setDirection(int);
	void setAngle(double);
	void setXAdvance(int);
	void setYAdvance(int);
	void drawFrameR(BITMAP* dest);
	void updateTargetDistance();
	double findDistance(int, int);
	int findXDistance(int, int);
	int findYDistance(int, int);
	void advance();
	double findAngle();
};

#endif

