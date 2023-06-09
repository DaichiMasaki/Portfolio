#pragma once
#include "Actor.h"
#include "SDL.h"
#include <string>

class WallCreate 
{
public:
	WallCreate(class Game* game);

	//当たり判定の取得
	class Wall* GetHitBox() { return mWall; }

	//当たり判定の生成
	void MakeWallData(const std::string& fileName, const int& x, const int& y);

private:
	class Wall* mWall;
};