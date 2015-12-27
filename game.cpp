#include "game.h"
#include "ctime"

Game::Game() {
	srand((unsigned)time(NULL));
	lastTime = currTime = diffTime = 0;
	win = false;
	window = SDL_CreateWindow("Battle City", 200, 200, WINDOW_W, WINDOW_H, SDL_WINDOW_SHOWN);
	render = SDL_CreateRenderer(window, -1, 0);
	home.x = (WINDOW_W/GRID_W)/2 * GRID_W;
	home.y = (WINDOW_H/GRID_H-1) * GRID_H;
	home.w = GRID_W;
	home.h = GRID_H;

	addWall(50, 50);	addWall(150, 50);	addWall(250, 50);	addWall(350,50);	addWall(450,50);	addWall(550,50);
	addWall(50, 100);	addWall(150, 100);	addWall(250, 100);	addWall(350,100);	addWall(450,100);	addWall(550,100);
	addWall(50, 150);	addWall(150, 150);	addWall(250, 150);	addWall(300,150);	addWall(350,150);	addWall(450,150);	addWall(550,150);
	addWall(50, 200);	addWall(150, 200);	addWall(250, 200);	addWall(350,200);	addWall(450,200);	addWall(550,200);
	addWall(50, 250);	addWall(150, 250);	addWall(450, 250);	addWall(550,250);
	addWall(250, 300);	addWall(350, 300);
	addWall(0, 350);	addWall(100, 350);	addWall(150, 350);	addWall(450, 350);	addWall(500, 350);	addWall(600, 350);
	addWall(250, 400);	addWall(350, 400);
	addWall(50, 450);	addWall(150, 450);	addWall(250, 450);	addWall(300, 450);	addWall(350, 450);	addWall(450, 450);	addWall(550, 450);
	addWall(50, 500);	addWall(150, 500);	addWall(250, 500);	addWall(350, 500);	addWall(450, 500);	addWall(550, 500);
	addWall(50, 550);	addWall(150, 550);	addWall(450, 550);	addWall(550, 550);
	addWall(50, 600);	addWall(150, 600);	addWall(450, 600);	addWall(550, 600);
	addWall(50, 650);	addWall(150, 650);	addWall(250, 650);	addWall(300, 650);	addWall(350, 650);	addWall(450, 650);	addWall(550, 650);
	addWall(250, 700);	addWall(350, 700);

	player = new Player(this, 400, 700, UP);
	enemies.push_back(*(new Enemy(this, 0, 0, rand()%4)));
	enemies.push_back(*(new Enemy(this, 300, 0, rand()%4)));
	enemies.push_back(*(new Enemy(this, 600, 0, rand()%4)));
	paint();

}

Game::~Game() {
	SDL_DestroyRenderer(render);
	SDL_DestroyWindow(window);
}

void Game::paintItem(int type, SDL_Rect rect, int dir) {
	// background
	if(type == 0) {
		SDL_Surface* sur = SDL_LoadBMP("background.bmp");
		TSurface* ts = new TSurface(sur, rect, dir);
		tSurface.push_back(ts);
		return;
	}

	// wall
	if(type == 1) {
		SDL_Surface* sur = SDL_LoadBMP("wall.bmp");
		TSurface* ts = new TSurface(sur, rect, dir);
		tSurface.push_back(ts);
		return;
	}

	// home
	if(type == 2) {
		SDL_Surface* sur = SDL_LoadBMP("home.bmp");
		TSurface* ts = new TSurface(sur, rect, dir);
		tSurface.push_back(ts);
		return;
	}

	// player
	if(type == 3) {
		SDL_Surface* sur = SDL_LoadBMP("player.bmp");
		TSurface* ts = new TSurface(sur, rect, dir);
		tSurface.push_back(ts);
		return;
	}

	// bullet
	if(type == 4) {
		SDL_Surface* sur = SDL_LoadBMP("bullet.bmp");
		TSurface* ts = new TSurface(sur, rect, dir);
		tSurface.push_back(ts);
		return;
	}

	// enemy
	if(type == 5) {
		SDL_Surface* sur = SDL_LoadBMP("enemy.bmp");
		TSurface* ts = new TSurface(sur, rect, dir);
		tSurface.push_back(ts);
		return;
	}

}

void Game::paint() {
	SDL_RenderClear(render);
	
	// background
	SDL_Rect windowRect;
	windowRect.x = 0;
	windowRect.y = 0;
	windowRect.w = WINDOW_W;
	windowRect.h = WINDOW_H;

	paintItem(0, windowRect, UP);

	// wall
	for(int i = 0; i < wallRects.size(); ++i) {
		paintItem(1, wallRects[i], UP);
	}

	
	// home
	paintItem(2, home, UP);

	// player
	paintItem(3, player->getRect(), player->getDir());

	// bullet
	for(int i = 0; i < bullets.size(); ++i) {
		paintItem(4, bullets[i].getRect(), bullets[i].getDir());
	}

	// enemy
	for(int i = 0; i < enemies.size(); ++i) {
		paintItem(5, enemies[i].getRect(), enemies[i].getDir());
	}

	// paint surfaces;
	for(int i = 0; i < tSurface.size(); ++i) {
		SDL_Texture* tt = SDL_CreateTextureFromSurface(render, tSurface[i]->surface);
		SDL_RenderCopyEx(render, tt, NULL, &tSurface[i]->rect, tSurface[i]->dir*90, NULL, SDL_FLIP_NONE);
		delete tSurface[i];
		SDL_DestroyTexture(tt);
	}

	tSurface.clear();

	SDL_RenderPresent(render);
}

void Game::addWall(int x, int y) {
	SDL_Rect t;
	t.x = x;
	t.y = y;
	t.w = GRID_W;
	t.h = GRID_H;
	wallRects.push_back(t);
}

void Game::update() {
	isRunning = true;

	int startTime = 0;
	while(isRunning && player) {
		startTime = SDL_GetTicks();

		while(SDL_PollEvent(&_event)) {
			switch (_event.type) {
				case SDL_QUIT:
					isRunning = false;
					break;
				case SDL_KEYDOWN:
					if(_event.key.keysym.sym == SDLK_SPACE) {
						currTime = SDL_GetTicks();
						diffTime = currTime - lastTime;
						//std::cout << currTime << std::endl;
						//std::cout << diffTime << std::endl;
						if(diffTime >= 500) {
							bullets.push_back(player->fire());
							lastTime = currTime;
						}
					}
				case SDL_KEYUP: {
					switch (_event.key.keysym.sym) {
						case SDLK_UP:
							player->update(UP);
							break;
						case SDLK_LEFT:
							player->update(LEFT);
							break;
						case SDLK_DOWN:
							player->update(DOWN);
							break;
						case SDLK_RIGHT:
							player->update(RIGHT);
							break;
						default:
							break;
					}
						
				}
				default:
					break;
			}
		}

		if(!isRunning)
			break;

		// 子弹击中子弹
		std::vector<Bullet> tBullets;
		for(int i = 0; i < bullets.size(); ++i){
			bool collision = false;
			for(int j = 0; j < bullets.size(); ++j) if(i != j){
				if(toCollision(bullets[i].getPosX(),bullets[i].getPosY(),bullets[j].getPosX(),bullets[j].getPosY())){
					collision = true;
					break;
				}
			}
			if(!collision) tBullets.push_back(bullets[i]);
		}
		bullets = tBullets;
		tBullets.clear();

		// 子弹击中 enemy
		std::vector<Enemy> tEnemies;
		for(int i = 0; i < enemies.size(); ++i){
			bool collision = false;
			for(int j = 0; j < bullets.size(); ++j) if(bullets[j].getType() == 0){
				if(toCollision(bullets[j].getPosX(),bullets[j].getPosY(),enemies[i].getPosX(),enemies[i].getPosY())){
					collision = true;
					bullets[j].setType(-1);
					break;
				}
			}
			if(!collision) tEnemies.push_back(enemies[i]);
		}
		enemies = tEnemies;

		// 子弹击中 enemy 后的消失
		for(int i = 0; i < bullets.size(); ++i) if(bullets[i].getType() != -1){
			tBullets.push_back(bullets[i]);
		}
		bullets = tBullets;
		tBullets.clear();

		// 子弹击中 player
		bool playShot = false;
		for(int i = 0; i < bullets.size(); ++i) if(bullets[i].getType() == 1){
			if(toCollision(bullets[i].getPosX(),bullets[i].getPosY(),player->getPosX(),player->getPosY())){
				playShot = true;
				break;
			}
		}
		if(playShot){
			isRunning = false;
			SDL_Delay(1000);
			continue;
		}

		// enemy 发子弹
		currTime = SDL_GetTicks();
		for(int i = 0; i < enemies.size(); ++i) {
			enemies[i].trymove();
			if(rand() % 8 == 0 && currTime - enemies[i].lastTime >= 500){
				bullets.push_back(enemies[i].fire());
				enemies[i].lastTime = SDL_GetTicks();
			}
		}
		
		// 子弹是否能继续走
		std::pair<int,int> collisionWall;

		for(int i = 0; i < bullets.size(); ++i) {
			collisionWall = bullets[i].update();
			if(collisionWall.first == -1){
				tBullets.push_back(bullets[i]);
			}
			else if(collisionWall.first == -3){ // lose
				isRunning = false;
				SDL_Delay(1000);
				break;
			}
			else if(collisionWall.first != -2){ // 撞墙
				std::vector<SDL_Rect> tWalls;
				for(int j = 0; j < wallRects.size(); ++j){
					if(wallRects[j].x == collisionWall.first && wallRects[j].y == collisionWall.second) continue;
					tWalls.push_back(wallRects[j]);
				}
				wallRects = tWalls;
			}
		}

		bullets = tBullets;
		
		if(enemies.size() == 0) {
			win = true;
			isRunning = false;
			SDL_Delay(1000);
		}

		paint();


	}

	if(win) {
		SDL_RenderClear(render);
		SDL_Surface* res = SDL_LoadBMP("win.bmp");
		SDL_Texture* tRes = SDL_CreateTextureFromSurface(render, res);
		SDL_RenderCopy(render, tRes, NULL, NULL);
		SDL_RenderPresent(render);
		SDL_Delay(3000);
	}

	else {
		SDL_RenderClear(render);
		SDL_Surface* res = SDL_LoadBMP("lose.bmp");
		SDL_Texture* tRes = SDL_CreateTextureFromSurface(render, res);
		SDL_RenderCopy(render, tRes, NULL, NULL);
		SDL_RenderPresent(render);
		SDL_Delay(3000);
	}

}