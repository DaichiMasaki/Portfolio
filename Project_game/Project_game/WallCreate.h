#pragma once
#include "Actor.h"
#include "SDL.h"
#include <string>

class WallCreate 
{
public:
	WallCreate(class Game* game);

	//�����蔻��̎擾
	class Wall* GetHitBox() { return mWall; }

	//�����蔻��̐���
	void MakeWallData(const std::string& fileName, const int& x, const int& y);

private:
	class Wall* mWall;
};