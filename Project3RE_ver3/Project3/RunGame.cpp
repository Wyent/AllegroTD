#include "RunGame.h"


volatile long runTimer = 0;
volatile long wavePauseTimer = 0;

void incrementWavePause()
{
	wavePauseTimer++;
}

void incrementTimer()
{
	runTimer++;
}

RunGame::RunGame()
{
	// for enemy spawning //
	
	LOCK_VARIABLE( wavePauseTimer );
	LOCK_FUNCTION( incrementWavePause );

	LOCK_VARIABLE( runTimer );
	LOCK_FUNCTION( incrementTimer );

	//for pausing in between waves
	install_int_ex( incrementWavePause, BPS_TO_TIMER(1));

	install_int_ex( incrementTimer, BPS_TO_TIMER(1));
	
	////////////////////////

	//back stuff
	background = load_bitmap("TDBACK.bmp", NULL);

	// setup wave stuff //////////////////////////////
	//set testing data


	for (int i = 0; i < WAVE3; i++)
	{
		if (i < WAVE1)
			enemyWave1[i] = 1;
		if ( i < WAVE2)
			enemyWave2[i] = 2;

		enemyWave3[i]	  = 3;
	}


	currentEnemy = 0; //index to wave array
	currentWave  = 1;


	for (int i = 0; i < WAVE1; i++)
	{

		activeWave.push_back(  enemyWave1[i] );

	}

	/////////////////////////////////////////////
	
	
	// setup buffer ////////////////////////////////////
	buffer = create_bitmap((board_width+2) * block_size, board_height * block_size);
	////////////////////////////////////////////////////

	/// setup game member ////////////////////////

		int TD_map0[12][30] = {
		{ BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, 
		BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE },
		{ BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, 
		EMPTY, EMPTY, EMPTY, EMPTY, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE },
		{ BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, EMPTY, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, 
		BUILDABLE, BUILDABLE, BUILDABLE, EMPTY, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE },
		{ BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, EMPTY, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, 
		BUILDABLE, BUILDABLE, BUILDABLE, EMPTY, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE },
		{ BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, EMPTY, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, EMPTY, EMPTY, EMPTY, 
		EMPTY, EMPTY, EMPTY, EMPTY, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE },
		{ BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, EMPTY, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, EMPTY, BUILDABLE, BUILDABLE, 
		BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
		{ BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, EMPTY, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, EMPTY, BUILDABLE, BUILDABLE, 
		BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, EMPTY, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE },
		{ EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, EMPTY, BUILDABLE, BUILDABLE, 
		BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, EMPTY, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE },
		{ BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, EMPTY, EMPTY, EMPTY, 
		EMPTY, EMPTY, EMPTY, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, EMPTY, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE },
		{ BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, 
		BUILDABLE, BUILDABLE, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE },
		{ BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, 
		BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE },
		{ BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, 
		BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE, BUILDABLE }
		};
		int proj3_testMap_map[12][30] = {
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
		1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 
		1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 
		1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 
		0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1 },
		{ 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 
		1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0 },
		{ 0, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 
		1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 
		1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1 },
		{ 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 
		0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 
		1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
		};

		Level levels(1, 3, 400-79 - 20-1,  "block.bmp", "block.bmp",
			                               "block.bmp", "block.bmp", 
										   "block.bmp", "block.bmp", 
										   "block.bmp", TD_map0, true); 
	   game.init(1, levels, false);
	   game.setLevel(levels, 1);

  ////////////////////////////////////////////////////////////////////////////////
  
  // Setup Tower Stuff //////////////////////////////////////////////////////////

  ///////////////////////////////////////////////////////////////////////////////

  // Setup enemy Stuff //////////////////////////////////////////////////////////
	BITMAP* EN = load_bitmap("Enemy1_n.bmp", NULL);
	BITMAP* EE = load_bitmap("Enemy1_e.bmp", NULL);
	BITMAP* ES = load_bitmap("Enemy1_s.bmp", NULL);
	BITMAP* EW = load_bitmap("Enemy1_w.bmp", NULL);

	Enemy enemy[4];

	enemy[0].setSquarePos(15, 10);
    enemy[0].init(500, 500, 64, 64, "Enemy1_n.bmp", 1, 0);
	enemy[0].initEnemy(EN, ES, EE, EW, 15, 10, 4000);

	enemy[1].setSquarePos(14, 10);
	enemy[1].init(500, 500, 64, 64, "Enemy1_n.bmp", 1, 0);
	enemy[1].initEnemy(EN, ES, EE, EW, 14, 10, 2000);

	enemy[2].setSquarePos(13, 10);
    enemy[2].init(500, 500, 64, 64, "Enemy1_n.bmp", 1, 0);
	enemy[2].initEnemy(EN, ES, EE, EW, 13, 10, 1000);	
	
	enemy[3].setSquarePos(ENEMY_START_ROW, ENEMY_START_COL);
	enemy[3].init(500, 500, 64, 64, "Enemy1_n.bmp", 1, 0);
	enemy[3].initEnemy(EN, ES, EE, EW, ENEMY_START_ROW, ENEMY_START_COL, 0);
	

	Enemy::loadEnemySpr();
	//set vector
	//enemies.push_back(enemy[0]);//pushback is like add in java
	//enemies.push_back(enemy[1]);
	//enemies.push_back(enemy[2]);
	//enemies.push_back(enemy[3]);
	
	
	//enemies.push_back(  *(new Enemy ( activeWave[ currentEnemy++ ]) )  );//pushback is like add in java
	
	
	/*enemies.push_back(*(new Enemy(TROLL)) );
	enemies.push_back(*(new Enemy(TROLL)) );
	enemies.push_back(*(new Enemy(TROLL)) );*/

	/////////////////////////////
  ///////////////////////////////////////////////////////////////////////////////
	game.update();

	inHud = false;
	cameraX = 0;
	cameraY = 0;

	player.init(PLAYER_START_GOLD, PLAYER_HP);
}


RunGame::~RunGame()
{
	destroy_bitmap(buffer);
	towers.clear();
	enemies.clear();
	//towers.clear();

}
///updates/////////////////
void RunGame::update()
{//should call all of its member's updates
	clear_bitmap(buffer);
	towersTargetEnemies();
	game.update();
	//hud update
	hud.update(inHud, game.activeLevel.gameBoard);
	game.activeLevel.drawBoard(buffer);

	if ( runTimer >= SPAWN_SPEED   &&  wavePauseTimer > WAVE_PAUSE_TIME )
	{
		runTimer = 0;
		switch ( currentWave )
		{
		case 1:	
			if ( currentEnemy < WAVE1)
			{
				
				enemies.push_back(  *(new Enemy ( activeWave[ currentEnemy++ ]) )  );
			}
			else if ( wavePauseTimer > WAVE_PAUSE_TIME )
				{ 
					wavePauseTimer = 0;
				}
			else
			{
				
				currentWave = 2;
				activeWave.clear();
				currentEnemy = 0;
				for (int i = 0; i < WAVE2; i++)
				{
					activeWave.push_back( enemyWave2[ i ] );
				}
			}
			break;

		case 2:
			if ( currentEnemy < WAVE2)
			{
				wavePauseTimer = 0;
				enemies.push_back(  *(new Enemy ( activeWave[ currentEnemy++ ]) )  );
			}
			else if ( wavePauseTimer > WAVE_PAUSE_TIME )
			{ 
				wavePauseTimer = 0;
			}
			else
			{
				
				currentWave = 3;
				activeWave.clear();
				currentEnemy = 0;
				for (int i = 0; i < WAVE3; i++)
				{
					activeWave.push_back( enemyWave3[ i ] );
				}

			}
			break;

		case 3:
			if ( currentEnemy < WAVE3)
			{
				enemies.push_back(  *(new Enemy ( activeWave[ currentEnemy++ ]) )  );
			}
			else
			{
				;
				//set end condition here
				//currentWave = 3;
			}
			break;
		}
	}
	///scrolling
	if (!inHud  &&   key[KEY_LCONTROL] || key[KEY_RCONTROL]  /*&& !hud.isHoldingTower()*/)
	{
		cameraScroll(mouse_x, mouse_y, buffer->w, buffer->h);
	}

	if ( hud.isHoldingTower() )
	{
		if (mouse_b & 1)
		{
			int mouseX = mouse_x + cameraX;
			int mouseY = mouse_y + cameraY;


			if (mouseX / 64 < board_width && mouseY / 64 < board_height-1)
			{
				if ( game.activeLevel.gameBoard[mouseX / 64 - 1 ] [ mouseY / 64] == BUILDABLE)
				{
					hud.setIsHoldingTower(false);
				//Tower temp = 
					towers.push_back( *(new Tower(mouseX / 64 -1, mouseY / 64)) );//create tower in correct square
				}
			}
		}
	}

//TOWERS
		//for (int i = 0 ; i < towers.size(); i++)
		//{
		//	towers.at(i).update();
		//	//if (i < enemies.size() )
		//	//{
		//	//		enemies.at(i).update( game.activeLevel.gameBoard, BASE_ROW, BASE_COL, false, true);
		//	//		enemies.at(i).updateImg();//enemies[i].updateImg();				
		//	//}

		//}
//ENEMIES
		for (int i = 0 ; i < enemies.size(); i++)
		{
			//	killing enemies //////////////////////	
			if (enemies[i].getHP() <= 0)
			{
				//	killing enemies  //////////
				//also get gold here...
				player.addGold( enemies[i].getGoldReward() );
				enemies.erase(enemies.begin() + i);
				
				
				continue;
			}

			enemies.at(i).update( game.activeLevel.gameBoard, BASE_ROW, BASE_COL, false, true);
			enemies.at(i).updateImg();//enemies[i].updateImg();
			if (enemies.at(i).hasReachedTarget() )
			{
				
				player.subtractHP(enemies.at(i).getDamage() );
				enemies.erase(enemies.begin() + i);

			}
		}
}
	
/////////////////////////

//draws////////////////////
void RunGame::drawAll (BITMAP*dest)
{
	//call all member's draws on dest




	for (int i = 0; i < towers.size(); i++)
	{
		towers.at(i).draw(buffer);
	}
	for (int i = 0; i < enemies.size(); i++)
	{
			enemies.at(i).draw(buffer);
			//enemies[i].drawFrame(buffer);
	}


	BITMAP* temp = create_bitmap(SCREEN_W, SCREEN_H);
	clear_to_color(temp, makecol(255,0,255));
	hud.draw(buffer, temp);

	blit(buffer, dest, cameraX, cameraY, 0, 0, SCREEN_W, SCREEN_H);
	
	draw_sprite(dest, temp, 0, 0);

	destroy_bitmap(temp);
	//display stats/////////
	textprintf(dest, font, 10, 725, makecol(255,255,255), "Gold: %d", player.getGold());
	textprintf(dest, font, 10, 755, makecol(255,255,255), "HP: %d", player.getHP());

	///		wave start time  /////////////	
	if ( wavePauseTimer < WAVE_PAUSE_TIME )
	{
		textprintf(dest, font, 500, 755, makecol(255,255,255), "Wave Start: %d", ( WAVE_PAUSE_TIME - wavePauseTimer ));
	}

	textprintf(dest, font, 500, 745, makecol(255,255,255), "Left in Wave: %d", ( activeWave.size() -  enemies.size() ));	
		///////////////////////
	//draw_sprite(dest, buffer, 0, 0);
	//draw towers too
}
///////////////////////////
	
//getters

//setters

//other functions////////////
void RunGame::towersTargetEnemies()
{
	for (int i = 0; i < towers.size(); i++)
	{
		if (enemies.size() > 0)
		towers[i].attack(enemies);
		//for (int j = 0; j < enemies.size(); j++)
		//{
		//	if (  towers.at(i).getTarget( enemies.at(j) )  )
		//		break;//break; //that tower found a target so move on to next tower
		//}
	}
}



void RunGame::cameraScroll(int playerX, int playerY, int worldW, int worldH)
{
	cameraX = playerX; //- (SCREEN_W / 2);
	cameraY = playerY; //- (SCREEN_H / 2);

	if (cameraX < 0 )
		cameraX = 0;
	if (cameraX > worldW - SCREEN_W)
		cameraX  =  worldW - SCREEN_W;              

	if (cameraY < 0)
		cameraY = 0;

	if (cameraY > worldH - SCREEN_H)
	{
		cameraY = worldH - SCREEN_H;
	}

}
/////////////////////////////