#include "BaseClass.h"



BaseClass::BaseClass()
{

    animStartX  = 0; 
	animStartY  = 0;
	animColumns = 1;
	frameCount  = 0;
	frameDelay  = 5;
	animateDir  = 1;
	curFrame	= 0;
    maxFrame	= 0;

	x = 0;
	y = 0;

	width  = 0; 
	height = 0;
	scoreValue = 0;
}


BaseClass::~BaseClass()
{
	//delete sprite;
}







//SETTERS FUNCTIONS////////////////////////////
void BaseClass::setScoreValue(int newScoreVal)
{
	scoreValue = newScoreVal;
}

void BaseClass::setX(int newX) {
	x = newX;
}
   
void BaseClass::setY(int newY)   {
	y = newY;
}

void BaseClass::setWidth(int newW)   {
	width =newW;
}

void BaseClass::setHeight(int newH) {
	height = newH;
}


/*Sprite setters*********************************/
void BaseClass::setSprite(BITMAP* newSprite)
{
	if (newSprite != NULL)
	{
		if (sprite != NULL)
		{
			destroy_bitmap(sprite);
		}
		sprite = newSprite;
	}
	else
		allegro_message("Error loading image");
}
void BaseClass::loadSprite(const char* filename)
{

		sprite = load_bitmap(filename, 0);

		if (sprite != 0)
		{

			width  = sprite->w;
			height = sprite->h;

		}

		//set to glitch sprite
		else
			allegro_message("eRRROR loading sprite");

}

void BaseClass::loadSprite (const char* filename, int newW, int newH, int newMaxFrame, int newAnimColumns)
{
	
		sprite = load_bitmap(filename, 0);

		if (sprite != 0)
		{

			width  = newW;
			height = newH;
			if (maxFrame != -1)
				maxFrame = newMaxFrame;
			if (animColumns != -1)
				animColumns = newAnimColumns;

		}

		//set to glitch sprite
		else
			allegro_message("eRRROR loading sprite");
}
/********************************************************/

/*animation Setters*************************************/
void BaseClass::setAnimStartX(int newAnimStartX) {
	animStartX = newAnimStartX;
}

void BaseClass::setAnimStartY(int newAnimStartY){
	animStartY = newAnimStartY;

}
void BaseClass::setAnimColumns(int newAnimColumns){
	animColumns = newAnimColumns;
}
void BaseClass::setFrameCount(int newFrameCount){
	frameCount = newFrameCount;
}
void BaseClass::setFrameDelay(int newFrameDelay){
	frameDelay = newFrameDelay;
}
void BaseClass::setAnimateDir(int newAnimateDir){
	animateDir = newAnimateDir;
}
void BaseClass::setCurframe(int newCurFrame){
	curFrame = newCurFrame;
}
void BaseClass::setMaxFrame(int newMaxFrame){
	maxFrame = newMaxFrame;
}
/////////////////////////////////////////////

//GETTER FUNTIONS/////////
int BaseClass::getScoreValue()
{
	return scoreValue;
}

//position getters///////
int BaseClass::getX(){
	return x;
}

int BaseClass::getY(){
	return y;
}

int BaseClass::getWidth(){

	return width;
}

int BaseClass::getHeight(){
	return height;
}
int BaseClass::getCenterX()
{
	return x + (width / 2);
}
int BaseClass::getCenterY()
{
	return y + (height / 2);
}
/////////////////////////////


int BaseClass::getAnimStartX()
{
	return animStartX;
}
int BaseClass::getAnimStartY(){
	return animStartY;
}
int BaseClass::getAnimColumns(){
	return animColumns;
}
int BaseClass::getFrameCount(){
	return frameCount;
}
int BaseClass::getFrameDelay(){
	return frameDelay;
}
int BaseClass::getAnimateDir(){
	return animateDir;

}
int BaseClass::getCurframe(){
	return curFrame;
}
int BaseClass::getMaxFrame(){
	return maxFrame;
}

BITMAP* BaseClass::getSprite()
{
	return sprite;
}
///////////////////////////////

bool BaseClass::collided(int otherX, int otherY, int otherW, int otherH) //others == what your colliding with
{
	//bottom to other's top
if (otherX > x && otherX < x + width)
	return true;//there is a collision

}


//****functions****//
///init/////////////////////////////////////
void BaseClass::init(int newX, int newY, int newW, int newH, BITMAP* newSprite)
{
	x = newX;
	y = newY;
	width = newW;
	height = newH;
	setSprite(newSprite);
	frameDelay  = 50;
}

void BaseClass::init(int newX, int newY, int newW, int newH, BITMAP* newSprite, int newAnimColumns, int newMaxFrame)
{
	frameDelay  = 50;
	x = newX;
	y = newY;
	width = newW;
	height = newH;
	setSprite(newSprite);

	animColumns = newAnimColumns;
	maxFrame = newMaxFrame;

}

void BaseClass::init(int newX, int newY, int newW, int newH, const char* newSprite, int newAnimColumns, int newMaxFrame)
{
	loadSprite(newSprite);
	x = newX;
	y = newY;
	width = newW;
	height = newH;
    frameDelay  = 50;
	//setSprite(newSprite);
	

	animColumns = newAnimColumns;
	maxFrame = newMaxFrame;

	
}

//draws////////////////////////////////////////
void BaseClass::draw(BITMAP* dest)
{
 	draw_sprite(dest, sprite, x, y);
}

void BaseClass::drawFrame(BITMAP* dest)
{

     int fX = animStartX + (curFrame % animColumns) * width;
     int fY = animStartY + (curFrame / animColumns) * height;

	 masked_blit( sprite, dest, fX, fY, x, 
                 y, width, height);


}
void BaseClass::drawFrame(BITMAP* dest, int drawX,int drawY)
{

     int fX = animStartX + (curFrame % animColumns) * width;
     int fY = animStartY + (curFrame / animColumns) * height;

	 masked_blit( sprite, dest, fX, fY, drawX, 
                 drawY, width, height);

}

void BaseClass::drawFrameFlip(BITMAP* dest)
{
	 int fX = animStartX + (curFrame % animColumns) * width;
     int fY = animStartY + (curFrame / animColumns) * height;
	
	 BITMAP* temp = create_bitmap(width, height) ;
	 clear_to_color(temp, makecol(255, 0, 255));
	 blit( sprite,  temp, fX, fY, 0, 
					0, width, height);   
	 draw_sprite_h_flip(dest, temp, x, y);

	 destroy_bitmap(temp);

}


////////////////////////////////////////////////

//updates//////////////////////////////////////
void BaseClass::updateImg()
{
           //update frame based on animation direction
      if(++frameCount > frameDelay)
      {
            frameCount = 0;
            if (animateDir == -1)
            {
                 if(--curFrame < 0)
                      curFrame = maxFrame;
            }
            else if (animateDir == 1)
            {
            if (++curFrame > maxFrame)
            curFrame = 0;
            }
      }    
}
////////////////////////////////////////////////

void BaseClass::playSound(const char* wavFile)
{
	//voice_set_playMode(int voice
	SAMPLE* sound;
		sound = load_sample(wavFile);
	if (sound == NULL)
	{

		allegro_message("error loading sound!");
		exit(-1);

	}

	play_sample(sound, 255, 128, 1000, FALSE);
//	destroy_sample(sound);
}

void BaseClass::loadSound(const char* file, SAMPLE* sound)
{
	sound = load_sample(file);
	if (sound == NULL)
	{

		allegro_message("error loading sound!");
		exit(-1);

	}
	playSound(sound);
}

void BaseClass::playSound(SAMPLE* sound)
{
	stop_sample(sound);
	play_sample(sound, 100, 128, 1000, FALSE);
}

bool  BaseClass::inside(  int queryX, int queryY  )             
{
     if (queryX > x   &&   queryX < x + width   &&   queryY > y   &&   queryY < y + height)
        return true;
     else
         return false;                         
}
