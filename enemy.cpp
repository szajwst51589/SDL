#include"game.h"

SDL_Rect Enemy::getRect() {
	SDL_Rect rect;
	rect.x = posX;
	rect.y = posY;
	rect.w = 50;
	rect.h = 50;
	return rect;
}

Enemy::~Enemy() {

}

Enemy::Enemy(Game* tgame, int x, int y, int tdirection){
	if (!tgame)
		return;
	posX = x;
	posY = y;
	game = tgame;
	direction = tdirection;
	lastTime = SDL_GetTicks();
	isDead = false;
}
void Enemy::trymove(){
	if (!update()){
		direction = rand() % 4;
	}
}
bool Enemy::update(){
	//方向赋值

	SDL_Rect newPos, player ,enemy;

	newPos.w = 50;
	newPos.h = 50;
	player.w = 50;
	player.h = 50;
	enemy.w = 50;
	enemy.h = 50;

	std::vector<SDL_Rect> walls = game->getWalls();
	std::vector<Enemy> enemies = game->getEnemies();

	std::vector<SDL_Rect>::iterator it;
	std::vector<Enemy>::iterator e_it;

	bool move = true;
	newPos.x = posX + mov[direction][0] * ESPEED;
	newPos.y = posY + mov[direction][1] * ESPEED;

	if (outSide(newPos)){
		move = false;
	}
	if (move){
		//enemy 与 walls 的碰撞检测
		for (it = walls.begin(); it != walls.end(); it++){
			if (toCollision((*it), newPos)){
				move = false;
				break;
			}
		}
		// enemy  与 enemy 的碰撞检测
		for (e_it = enemies.begin(); e_it != enemies.end(); e_it++){
			enemy.x = (*e_it).posX;
			enemy.y = (*e_it).posY;
			if(enemy.x == posX && enemy.y == posY) continue;
			if (toCollision(enemy, newPos)){
				move = false;
				break;
			}
		}
		// enemy 与 player 的碰撞检测
		player.x = game->getPlayer()->getPosX();
		player.y = game->getPlayer()->getPosY();
		if (toCollision(player, newPos)){
			move = false;
		}

		// enemy 与 home 的碰撞检测
		SDL_Rect tHome = game->getHome();
		if(toCollision(newPos.x,newPos.y,tHome.x,tHome.y)){
			move = false;
		}
	}
	if (move){
		posX += mov[direction][0] * ESPEED;
		posY += mov[direction][1] * ESPEED;
	}
	return move;
}
Bullet Enemy::fire(){
	int newPosX = posX + mov[direction][0] * GRID_W;
	int newPosY = posY + mov[direction][1] * GRID_H;
	return Bullet(game, newPosX, newPosY, direction, 1);
}