class Game;
class Enemy{
public:
	Enemy(Game *tgame, int x, int y, int tdirection);
	~Enemy();
	int posX;
	int posY;
	int direction;
	int lastTime;
	Game* game;
	bool isDead;
	bool Enemy::update();
	void Enemy::trymove();

	int getPosX(){ return posX; }
	int getPosY(){ return posY; }
	int getDir(){ return direction; }

	SDL_Rect getRect();

	void setPosX(int tx){ posX = tx; }
	void setPosY(int ty){ posY = ty; }
	void setDirection(int tdirection){ direction = tdirection; }
	Bullet fire();
};