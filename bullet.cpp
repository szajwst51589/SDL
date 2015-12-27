#include "game.h"

Bullet::Bullet(Game* tgame,int tx,int ty,int tdirection,int ttype){
	posX = tx;
	posY = ty;
	direction = tdirection;
	game = tgame;
	type = ttype;
}

std::pair<int,int> Bullet::update(){
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

	newPos.x = posX + mov[direction][0] * BSPEED;
	newPos.y = posY + mov[direction][1] * BSPEED;

	if(outSide(newPos)){
		move = false;
		return std::make_pair(-2,-2);
	}

	if(move){
		// Bullets Óë walls µÄÅö×²¼ì²â
		for(it = walls.begin(); it != walls.end(); it++){
			if(toCollision((*it),newPos)){
				move = false;
				return std::make_pair((*it).x,(*it).y);
			}
		}

		// Bullets Óë home µÄÅö×²¼ì²â
		SDL_Rect tHome = game->getHome();
		if(toCollision(newPos.x,newPos.y,tHome.x,tHome.y)){
			return std::make_pair(-3,-3);
		}
	}

	if(move){
		posX += mov[direction][0] * BSPEED;
		posY += mov[direction][1] * BSPEED;
		return std::make_pair(-1,-1);
	}
}

Bullet::~Bullet() {


}

SDL_Rect Bullet::getRect() {
	SDL_Rect rect;
	rect.x = posX;
	rect.y = posY;
	rect.w = 50;
	rect.h = 50;
	return rect;
}