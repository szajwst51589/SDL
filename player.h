//#include "game.h"
#include "utility.h"
#include <vector>

class Game;
class Enemy;
class Bullet;

class Player{
	int posX,posY;
	int direction;
	Game* game;
	
public:
	Player(Game* tgame,int tx,int ty,int tdirection);
	~Player();

	void update(int tdirection);
	Bullet fire();

	int getPosX(){ return posX; }
	int getPosY(){ return posY; }
	int getDir(){ return direction; }
	SDL_Rect getRect();

	void setPosX(int tx){ posX = tx; }
	void setPosY(int ty){ posY = ty; }
	void setDirection(int tdirection){ direction = tdirection; }
};

