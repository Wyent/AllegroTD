#include  <vector>

#define MOUSE_L mouse_b & 1

//DIRECTIONS/////

#define STOP  0
#define NORTH 1
#define SOUTH 2
#define EAST  3
#define WEST  4

/////////////////
//BOARD STUFF////

#define block_size   64

/*#define board_height 24
#define board_width  32*/

#define board_height 12 //x rows
#define board_width 30  // y columns

#define BOARD_COLUMNS 30
#define BOARD_ROWS 22  //

#define min_board_x  30
#define min_board_y  22 //actually stores  left and right

///////////////////////

//ARRAY CONSTANTS//////

#define EMPTY 0
#define BUILDABLE 1
#define TOWER 2

#define WALL_1 1
#define WALL_2 2
#define WALL_3 3

#define BONUS_1 4
#define BONUS_2 5
#define DOTS 6
#define POWER_UP 7

#define PLAYER 8
#define ENEMY  9

//base position
#define BASE_ROW 0
#define BASE_COL 6


///////////////////////
// TOWER CONSTANTS for the board array --> used in Hud to determine what stats to display
#define T1_1 1
#define T1_2 2
#define T1_3 3

#define T2_1 4
#define T2_2 5
#define T2_3 6

#define T3_1 7
#define T3_2 8
#define T3_3 9

#define T4_1 10
#define T4_2 11
#define T4_3 12
/////////////////////////////
///Enemy states
//chase, scatter, flee
#define CHASE   1
#define SCATTER 2
#define FLEE    3

#define ENEMY_START_ROW 29
#define ENEMY_START_COL  5

#define PLAYER_START_ROW 14
#define PLAYER_START_COL  14


#define E_CORNER_ROW  board_width-1
#define W_CORNER_ROW  0 + 1
#define S_CORNER_COL  board_height-1
#define N_CORNER_COL  0+1

#define ENEMY_NUM 4

// enemy attack types //////////
#define GENERIC 1

//easy start-up values//////////

#define PLAYER_START_GOLD 500
#define PLAYER_HP 1000

///enemyTypes I.	Uruk'khai
#define GOBLIN  1
#define TROLL   2
#define BALROG  3
#define NAZGUL  4
#define SPIDER 5


	//Goblin
	//Troll
	//Balrog
	//Nazgul
	//Wolf riders
// waves //////////////
#define WAVE1 5
#define WAVE2 8
#define WAVE3 10

#define SPAWN_SPEED 5
#define WAVE_PAUSE_TIME 10