#pragma once
#include "Actor.h"

class Wand : public Actor
{
public:
	Wand(class Game* game, int direction = 0);

	void UpdateActor(float deltaTime) override;

private:
	//残留する時間
	float mEraseTimer;
};