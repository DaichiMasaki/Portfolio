#pragma once
#include "Actor.h"
#include "SDL.h"
#include <string>

class WallCreate 
{
public:
	WallCreate(class Game* game);

	//“–‚½‚è”»’è‚Ìæ“¾
	class Wall* GetHitBox() { return mWall; }

	//“–‚½‚è”»’è‚Ì¶¬
	void MakeWallData(const std::string& fileName, const int& x, const int& y);

private:
	class Wall* mWall;
};