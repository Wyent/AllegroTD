#ifndef BASE_CLASS_H
#define BASE_CLASS_H 1

#include <allegro.h>

class BaseClass
{
public:
	BITMAP* sprite;
protected:
	int x;
	int y;

	int width, height;

	//animation/ draw Stuff

	int animStartX, animStartY;
	int animColumns; // number of collumns in the sprite sheet
	int frameCount;
	int frameDelay;
	int animateDir;
	int curFrame;
	int maxFrame;   // max frame of the sprite, frames start at 0


	int scoreValue;

	

public:
	BaseClass(void);
	~BaseClass(void);

	bool BaseClass::collided(int otherX, int otherY, int otherW, int otherH); //others == what your colliding with

//SETTERS PROTOTYPES
	//sprites
	void loadSprite(const char* filename);
	void loadSprite (const char* filename, int newW, int newH, int newMaxFrame, int newAnimColumns);
	void setSprite(BITMAP* newSprite);
	
	void setScoreValue(int newScoreVal);

	void setX(int newX);
	void setY(int newY);
	void setWidth(int newW);
	void setHeight(int newH);
	

	//animation setters
	void setAnimStartX(int newAnimStartX);
	void setAnimStartY(int newAnimStartY);
	void setAnimColumns(int newAnimColumns);
	void setFrameCount(int newFrameCount);
	void setFrameDelay(int newFrameDelay);
	void setAnimateDir(int newAnimateDir);
	void setCurframe(int newCurFrame);
	void setMaxFrame(int newMaxFrame);


	//GETTER PROTOTYPES
	int getScoreValue();

    int getX();
	int getY();
	int getWidth();
	int getHeight();
	int getCenterX();
	int getCenterY();
	BITMAP* getSprite();
	int getAnimStartX();

	int getAnimStartY();
	int getAnimColumns();
	int getFrameCount();
	int getFrameDelay();
	int getAnimateDir();
	int getCurframe();
	int getMaxFrame();	
	//functions
	void init(int newX, int newY, int newW, int newH, BITMAP* newSprite);
	void init(int newX, int newY, int newW, int newH, BITMAP* newSprite, int newAnimColumns, int newMaxFrame);
	void BaseClass::init(int newX, int newY, int newW, int newH, const char* newSprite, int newAnimColumns, int newMaxFrame);

	void draw(BITMAP* dest);
	void updateImg();

	void drawFrame(BITMAP* dest);
	void drawFrame(BITMAP* dest, int drawX,int drawY);
	void drawFrameFlip(BITMAP* dest);

	void BaseClass::playSound(const char* wavFile);


	void playSound(SAMPLE* sound);
	void loadSound(const char* file, SAMPLE* sound);

	bool inside(int queryX, int queryY );


};

#endif