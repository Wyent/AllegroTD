#include "Projectile.h"
#include "Actor.h"
#include <allegro.h>
#include <cmath>

Projectile::Projectile(Enemy& target, int state, int targetDistance, double angle, double xDistance, double yDistance, int x, int y){
	setState(1);
	setTarget(target);
	setTargetDistance(targetDistance);
	setAngle(angle);
	speed = 5;
	this->xDistance = xDistance;
	this->yDistance = yDistance;
	setXAdvance(xDistance);
	setYAdvance(yDistance);
	setX(x);
	setY(y);
	damage = 5;
	distanceTraveled = 0;
	arrowArt = load_bitmap("arrowPH3.bmp", 0);
		//Arrow = load_bitmap("Graphics\\arrow_left.bmp", 0);

}
Projectile::~Projectile(void)
{
}

void Projectile::drawFrameR(BITMAP* dest)
{
		//rotate_sprite(dest, sprite, x, y, ftofix(faceAngle*.7111));
		//	rotate_sprite(dest, sprite, x, y, 
         //   itofix((int)(faceAngle / 0.7f / 2.0f)));
		 rotate_sprite(dest, arrowArt, x, y, ftofix((angle*.7111)));
}
void Projectile::advance(){
	if(state == 0){
		//setState(-1);
		return;
	}

	updateTargetDistance();
	setXAdvance(xDistance);
	setYAdvance(yDistance);
	setAngle(findAngle());
	x += xAdvance;
	y += yAdvance;
	distanceTraveled = 0;
	distanceTraveled += speed;

	if(targetDistance <= 0){
		/*for(; distanceTraveled > targetDistance; distanceTraveled -= speed){
			x-=xAdvance;
			y-=yAdvance;
		}*/

		if (target->getHP() > 0)
			target->subtractHP(damage);

		setState(0);
	} 
}
void Projectile::setTarget(Enemy& target){
	this->target = &target;
}
void Projectile::updateTargetDistance(){
	setTargetDistance(findDistance(findXDistance(x, target->getX()), findYDistance(y, target->getY())));
	xDistance = target->getX() - x;
	yDistance = target->getY() - y;
}
double Projectile::findDistance(int xDistance, int yDistance){
	return sqrt(((xDistance)*(xDistance) + (yDistance)*(yDistance)) * 1.0);;
}
int Projectile::findXDistance(int x1, int x2){
	xDistance = x2-x1;
	return xDistance;
}
int Projectile::findYDistance(int y1, int y2){
	yDistance = y2-y1;
	return yDistance;
}
void Projectile::setTargetDistance(double targetDistance){
	this->targetDistance = abs(targetDistance);
}
void Projectile::setXAdvance(int xDistance){
	xAdvance = (xDistance/targetDistance)*speed;
}
void Projectile::setYAdvance(int yDistance){
	yAdvance = (yDistance/targetDistance)*speed;
}

double Projectile::findAngle(){
	return atan2(yDistance, xDistance)*180/3.14;
}

void Projectile::setDirection(int direction){
	this->direction = direction;
}

void Projectile::setAngle(double angle){
	this->angle = angle;
}