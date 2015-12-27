#include "tsurface.h"

TSurface::TSurface() {
	surface = NULL;
	rect.x = 0;
	rect.y = 0;
	rect.w = 0;
	rect.h = 0;
	dir = UP;
}

TSurface::TSurface(SDL_Surface* ts, SDL_Rect tr, int _dir) {
	surface = ts;
	rect = tr;
	dir = _dir;
}

TSurface::~TSurface() {
	SDL_FreeSurface(surface);
}