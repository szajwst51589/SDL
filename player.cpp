#include "game.h"

Player::Player(Game* tgame,int tx,int ty,int tdirection){
	posX = tx;
	posY = ty;
	direction = tdirection;
	game = tgame;
}

void Player::update(int tdirection){
	//方向赋值
	direction = tdirection;

	SDL_Rect newPos,enemy;

	newPos.w = 50;
	newPos.h = 50;
	enemy.w = 50;
	enemy.h = 50;

	std::vector<SDL_Rect> walls = game->getWalls();
	std::vector<Enemy> enemies = game->getEnemies();

	std::vector<SDL_Rect>::iterator it;
	std::vector<Enemy>::iterator e_it;
	
	bool move = true;

	newPos.x = posX + mov[direction][0] * SPEED;
	newPos.y = posY + mov[direction][1] * SPEED;

	if(outSide(newPos)){
		move = false;
	}
	
	if(move){
		// Player 与 walls 的碰撞检测
		for(it = walls.begin(); it != walls.end(); it++){
			if(toCollision((*it),newPos)){
				//std::cout << "c" << std::endl;
				move = false;
				break;
			}
		}
		// Player 与 enemies 的碰撞检测
		for(e_it = enemies.begin(); e_it != enemies.end(); e_it++){
			enemy.x = (*e_it).getPosX();
			enemy.y = (*e_it).getPosY();
			if(toCollision(enemy,newPos)){
				move = false;
				break;
			}
		}
		// player 与 home 的碰撞检测
		SDL_Rect tHome = game->getHome();
		if(toCollision(newPos.x,newPos.y,tHome.x,tHome.y)){
			move = false;
		}
	}

	if(move){
		posX += mov[direction][0] * SPEED;
		posY += mov[direction][1] * SPEED;
	}
}

SDL_Rect Player::getRect() {
	SDL_Rect rect;
	rect.x = posX;
	rect.y = posY;
	rect.w = 50;
	rect.h = 50;
	return rect;
}

Bullet Player::fire(){
	
	int newPosX = posX + mov[direction][0]*50;
	int newPosY = posY + mov[direction][1]*50;
	return Bullet(game,newPosX,newPosY,direction,0);
}