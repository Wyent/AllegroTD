#ifndef TOWER_H
#define TOWER_H 1
#include "Enemy.h"
#include "Projectile.h"
//#include "Actor.h"
#include <vector>
using namespace std;

/*class Tower : public Actor
{

protected:
	int prevCoolTime;
	bool hasTarget;
	int  towerType; 
	int  speed;
	int coolDownTime;
	int  range;

	///////////////////////
	//t attackType;
	//arraylist of projectiles; with a size = to range, projectiles should be created and destroyed
	//dynamically(spawned if attacking)

	vector <Projectile> projectiles;

public:	


	int projectileType; // what type of enemies it can target
	int targetX, targetY;

	Tower::Tower(int row, int col);
	~Tower();
	bool getTarget( Enemy &enemy);  //if hasTarget, do attack
	void update();
	void attack(int targetX, int targetY);

	void draw(BITMAP* dest);

	bool inRange(int xPos, int yPos);
};*/

#pragma once

#include "Actor.h"
#include "Projectile.h"
#include "Player.h"

class Tower : public Actor
{
public:
	//Tower(void);
	Tower(int row, int col);
	~Tower(void);
	int range;
	int coolDown, coolDownTimer;
	int target; //index of target in array of enemies
	//Projectile arrow[4];
	vector<Projectile> arrow;
	double distance, targetDistance, xDistance, yDistance;
	int direction;

	void findTarget(vector<Enemy>&);
	void attack(vector<Enemy>&);
	double findDistance(int, int);
	int findXDistance(int, int);
	int findYDistance(int, int);
	double findAngle();
	void updateTargetDistance(vector<Enemy>&);
	void setTargetDistance(double);
	int getDirection();
	double getTargetDistance();
	void draw(BITMAP* dest);
};
#endif
