#ifndef RUN_GAME_H
#define RUN_GAME_H 1

#include <vector>

#include <allegro.h>
#include "global.h"
#include "Level.h"
#include "Game.h"
#include "Tower.h"
#include "Hud.h"
#include "Enemy.h"
#include "Player.h"

using namespace std;

//////////////////////////////////////////////
//////// RunGame ////////////////////////////
// this class should handle all the things to make the game come
// together, it should have one update function
// that calls all of its members update functions
// and one instance of RunGame should be created in main


class RunGame
{
	
protected:

	BITMAP* background;
	int enemyWave1[WAVE1];
	int enemyWave2[WAVE2];
	int enemyWave3[WAVE3];

	int currentEnemy; //index to wave array
	vector <int> activeWave;
	int currentWave; // is this the first or...

	vector <Enemy> enemies;
	vector <Tower> towers;
	

	Hud hud;

	Game game;

	BITMAP* buffer;

	bool inHud;
	int cameraX, cameraY;

	Player player;

public:
	RunGame();
	~RunGame();

	///updates/////////////////
	void update();
	
	/////////////////////////

	//draws////////////////////
	void drawAll (BITMAP*dest);

	///////////////////////////
	
	//getters

	//setters

	//other functions////////////
	void towersTargetEnemies();
	void RunGame::cameraScroll(int playerX, int playerY, int worldW, int worldH);
	/////////////////////////////


};
#endif

