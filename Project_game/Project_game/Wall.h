#pragma once
#include "Actor.h"
#include "SDL.h"
#include <string>

class Wall : public Actor
{
public:
	Wall(class Game* game, const int& x = 32, const int& y = 32);

private:
};

void WallCreate(class Game* game, const std::string& fileName);
