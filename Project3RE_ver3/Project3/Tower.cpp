#include "Tower.h"
//#include "Projectile.h"
volatile long coolTime = 0;
void incrementCoolTime()
{
	coolTime++;
}
END_OF_FUNCTION(incrementCoolTime);

/*Tower::Tower(int row, int col)
{
	
	/////////// Timer stuff ///////////////
	LOCK_FUNCTION(incrementCoolTime);
	LOCK_VARIABLE(coolTime);
	
	install_int_ex(incrementCoolTime, BPS_TO_TIMER(1));

	/////////////////////////////

	//coolTime = 0;
	squareRow = row; 
	squareCol = col;

	loadSprite("Turret1PH.bmp");
	 hasTarget = false;
	 projectileType = GENERIC; // what type of enemies it can target
	 targetX = 0;
	 targetY = 0;
	 range = 256; //do this in constructor for other towers --> they should know their range
	 setSquarePos(row, col);
	 speed = 1;
	 coolDownTime = 0;
	 prevCoolTime = 0;
}


Tower::~Tower()
{

}
void Tower::update()
{
	//if (!hasTarget)
//		coolDownTime++;
}

bool Tower:: getTarget( Enemy &enemy)
{	
	if ( hasTarget )
	{
		if (coolDownTime >= speed)
		{
			for (int i = 0;  i < projectiles.size() ; i++ )
			{
				//if proj' == outOfRange, then destroy it, OR if == in enemy, destroy it, and reset coolDownTime
				// check to see if need to destroy projectile ////////
				if (  enemy.inside( projectiles[i].getCenterX(), projectiles[i].getCenterY() )  )
				{
					enemy.subtractHP( projectiles[i].getDamage() );
					projectiles.erase(projectiles.begin() + i);
					//coolDownTime = 0;
					hasTarget = false;
					continue; //skip to next
				}
				if ( ! inRange( projectiles[i].getCenterX(), projectiles[i].getCenterY() )  || 
					              coolDownTime > speed*2)
				{
					hasTarget = false;
					projectiles.erase(projectiles.begin() + i);
					//coolDownTime = 0;
					continue; //skip to next

				}
				//////////////////////////////////////////////////////

				//projectiles[i].setTarget( enemy.getCenterX(), enemy.getCenterY() );
				//projectiles[i].lockOnTarget( enemy.getCenterX(), enemy.getCenterY() );
    			
				//projectiles[i].updateTarget(enemy.getCenterX(), enemy.getCenterY() );
				projectiles[i].update();
//				return true;
			}
		}
	}

	//static int prevCoolTime = 0;
	//one second passed
	if ( prevCoolTime < coolTime)
	{
		if ( !hasTarget )
			coolDownTime++;
		
	}

	prevCoolTime = coolTime;

	update();
//check to see if enemyType matches later
	//if hasTarget, do attack
	if (coolDownTime >= speed /* || coolTime % speed  == 0)
	{
		if (  inRange( enemy.getCenterX(), enemy.getCenterY() ) )
		{
			if (hasTarget == false)
			{
				coolDownTime = 0;
				//coolTime   = 0;
				hasTarget    = true;
				attack( enemy.getCenterX(), enemy.getCenterY() ); // should spawn appropriate projectiles
	
			}
		}
	}
	//if so...
	//if projectile.targetReached-->dist=0--
	//then damage enemy
	//destroy projectile



	//else just skip here...
	// return true if a target was found
	// or target was already given
	return false;
}

void Tower::attack(int targetX, int targetY)
{
	// according to towerType, spawn correct number and type of projectiles at the right position(s)
	
	//placeHolder BURST
	projectiles.push_back( *(new Projectile(x, y, 20, targetX, targetY)) );

}
void Tower::draw(BITMAP* dest)
{
	drawFrame(dest);
	if( speed - coolDownTime > 0)
		textprintf(dest, font, x+width/2, y +height/2, makecol(255,255,255), "%d", speed - coolDownTime);
	else
		textprintf(dest, font, x+width/2, y +height/2, makecol(255,255,255), "Ready");
	for (int i = 0; i < projectiles.size(); i++)
	{
		projectiles[i].drawFrameR(dest);
	}
}

bool Tower::inRange(int xPos, int yPos)
{
	return sqrt( pow(   (double)(xPos - getCenterX())    , 2)   +    pow(  (double)(yPos - getCenterY())   , 2) )     <    range;

}*/

//#include "Globals.h"
#include "Tower.h"
#include <cmath>

/*Tower::Tower(void)
{
	coolDown = 60;
	coolDownTimer = coolDown;
	range = 100;
	targetDistance = range+1;
}*/

Tower::Tower(int row, int col)
{

	squareRow = row; 
	squareCol = col;
	coolDown = 60;
	coolDownTimer = coolDown;
	distance = 0;

	loadSprite("Turret1PH.bmp");

	 range = 256; //do this in constructor for other towers --> they should know their range
	 targetDistance = range+1;
	 setSquarePos(row, col);
}
Tower::~Tower(void)
{
}

void Tower::draw(BITMAP* dest)
{
	drawFrame(dest);

	for(int i = 0; i < arrow.size(); i++){
		if(arrow[i].getState() != 0)
			arrow[i].advance();
		if(arrow[i].getState() == 0)
			arrow.erase(arrow.begin()+i);
	}

	for (int i = 0; i < arrow.size(); i++)
	{
		arrow[i].drawFrameR(dest);
	}
}

void Tower::attack(vector<Enemy>& target){ //this will have array of enemies
	if(--coolDownTimer < 0)
		coolDownTimer++;

	if(targetDistance > range)
	{
		findTarget(target); //this will pass back arrray of enemies
		return;
	}
	else
		updateTargetDistance(target);

	if(--coolDownTimer < 0){
		if ( this->target < target.size() ){
			arrow.push_back( *(new Projectile( target[this->target], 1, targetDistance, findAngle(), xDistance, yDistance, x, y)));
			coolDownTimer = coolDown;
		}
	}

}

void Tower::findTarget(vector<Enemy>& target){ //this will search array of enemies
	for(int i = 0; i < target.size(); i++)
	{
		if( findDistance(findXDistance(x, target[i].getX()), findYDistance(y, target[i].getY())) <= range){
			this->target = i;
			setTargetDistance(distance);
		}
	}
	if(target.size() == 0)
		setTargetDistance(range+1);
}

int Tower::getDirection(){
	return direction;
}
double Tower::getTargetDistance(){
	return targetDistance;
}

double Tower::findDistance(int xDistance, int yDistance){
	distance = sqrt(((xDistance)*(xDistance) + (yDistance)*(yDistance)) * 1.0);
	return sqrt(((xDistance)*(xDistance) + (yDistance)*(yDistance)) * 1.0);;
}
int Tower::findXDistance(int x1, int x2){
	xDistance = x2-x1;
	return xDistance;
}
int Tower::findYDistance(int y1, int y2){
	yDistance = y2-y1;
	return yDistance;
}

void Tower::updateTargetDistance(vector<Enemy>& target){
	targetDistance = findDistance(findXDistance(x, target[this->target].getX()), findYDistance(y, target[this->target].getY()));
	//xDistance = target[this->target].x - x;
	xDistance = target[this->target].getX() - x;
	//yDistance = target[this->target].y - y;
	yDistance = target[this->target].getY() - y;
}
void Tower::setTargetDistance(double targetDistance){
	this->targetDistance = targetDistance;
}
double Tower::findAngle(){
	return atan2(yDistance, xDistance)*180/3.14;
}