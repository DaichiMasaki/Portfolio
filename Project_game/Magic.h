#pragma once
#include "Actor.h"

class Magic : public Actor
{
public:
	Magic(class Game* game, int direction = 0);

	void UpdateActor(float deltaTime) override;

private:
	//残留する時間
	float mEraseTimer;
};