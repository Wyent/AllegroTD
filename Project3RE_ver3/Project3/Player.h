#ifndef PLAYER_H
#define PLAYER_H 1

class Player
{
	protected: 
		int HP;
		int gold;
		
public:
	
	Player();
	~Player();
	void Player::init(int startGold, int hitPoints);

	int getGold();
	int getHP();
	
	void setHP(int newHP);
	void setGold(int newHP);

	void subtractHP( int input);
	void subtractGold( int input);
	
	void addHP( int input);
	void addGold (int input);
};
#endif
