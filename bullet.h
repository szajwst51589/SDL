//#include "game.h"

#include "utility.h"

class Game;

class Bullet{
public:
	Bullet(Game* tgame,int tx,int ty,int tdir,int ttype);
	~Bullet();
	
	bool shot();
	std::pair<int,int> update();

	int getPosX(){ return posX; }
	int getPosY(){ return posY; }
	int getDir(){ return direction; }
	int getType(){ return type; }

	SDL_Rect getRect();
	void setPosX(int tx){ posX = tx; }
	void setPosY(int ty){ posY = ty; }
	void setDir(int tdir){ direction = tdir; }
	void setType(int ttype){ type = ttype; }

private:
	int posX,posY;
	int direction;
	int type;
	Game* game;
};