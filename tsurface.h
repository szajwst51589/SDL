#ifndef TSURFACE_H
#define TSURFACE_H

#include "SDL.h"
#include "utility.h"


class TSurface {
public:
	SDL_Surface *surface;
	SDL_Rect rect;
	int dir;
	TSurface();
	TSurface(SDL_Surface* ts, SDL_Rect tr, int _dir);
	~TSurface();
};

#endif