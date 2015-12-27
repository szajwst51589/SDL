#ifndef _UTILITY_H
#define _UTILITY_H

#include "SDL.h"


const int WINDOW_W = 650;
const int WINDOW_H = 750;

const int GRID_W = 50;
const int GRID_H = 50;

const int UP = 0;
const int RIGHT = 1;
const int DOWN = 2;
const int LEFT = 3;

const int SPEED = 25;
const int BSPEED = 12;
const int ESPEED = 5;
const int mov[4][2] = {{0,-1},{1,0},{0,1},{-1,0}};

inline bool toCollision(SDL_Rect &rect1,SDL_Rect &rect2){
	return !(rect1.y >= rect2.y + rect2.h || rect1.x >= rect2.x + rect2.w ||
		rect1.y + rect1.h <= rect2.y || rect1.x + rect1.w <= rect2.x);
}

inline bool toCollision(int a1,int b1,int a2,int b2){
	return !(b1 >= b2 + GRID_H || a1 >= a2 + GRID_W ||
		b1 + GRID_H <= b2 || a1 + GRID_W <= a2);
}

inline bool getShot(SDL_Rect &rect1,SDL_Rect &rect2){
	return !(rect1.y > rect2.y + rect2.h || rect1.x > rect2.x + rect2.w ||
		rect1.y + rect1.h < rect2.h || rect1.x + rect1.w < rect2.x);
}

inline bool outSide(SDL_Rect &rect){
	if(rect.x < 0 || rect.x + rect.w > WINDOW_W ||
	   rect.y < 0 || rect.y + rect.h > WINDOW_H) return true;
	return false;
}


#endif