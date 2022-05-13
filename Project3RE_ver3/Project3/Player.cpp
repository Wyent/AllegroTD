#include "Player.h"


Player::Player(void)
{
}


Player::~Player(void)
{
}

void Player::init(int startGold, int hitPoints)
{
	HP = hitPoints;
	gold = startGold;
}

int Player::getGold()
{
	return gold;
}
int Player::getHP()
{
	return HP;
}

// Setters //////////////////////////
void Player::setHP(int newHP)
{
	HP = newHP;
}
void Player::setGold(int newGold)
{
	gold = newGold;
}

void Player::subtractHP( int input)
{
	HP -= input;
}
void Player::subtractGold( int input)
{
	gold -= input;
}
	
void Player::addHP( int input)
{
	HP += input;
}

void Player::addGold (int input)
{
	gold += input;
}
//////////////////////////////////////