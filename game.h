#include <iostream>
#include <vector>
#include "SDL.h"
#include "tsurface.h"
#include "utility.h"
#include "player.h"
#include "enemy.h"
#include "bullet.h"


class Game {
	bool isRunning;
	SDL_Rect home;
	std::vector<SDL_Rect> wallRects;
	Player* player;
	std::vector<Enemy> enemies;
	std::vector<Bullet> bullets;
	SDL_Window *window;
	SDL_Renderer *render;
	SDL_Event _event;
	int lastTime, currTime, diffTime;
	std::vector<TSurface*> tSurface;

public:
	Game();
	~Game();
	void paint();
	void paintItem(int type, SDL_Rect rect, int dir);
	void addWall(int x, int y);
	void update();
	bool win;
	SDL_Rect getHome(){ return home; }
	std::vector<SDL_Rect>& getWalls(){ return wallRects; }
	std::vector<Enemy> getEnemies() { return enemies; }
	Player* getPlayer() { return player; }
};
