#pragma once
#include "Actor.h"
#include <string>


class Object : public Actor
{
public:
	Object(class Game* game);
	~Object();

	//�Q�b�^�[�ƃZ�b�^�[
	int GetWeight() { return mWeight; }
	void SetWeight(int weight) { mWeight = weight; }

private:
	int mWeight;
};

void ObjectCreate(class Game* game, const std::string& fileName);