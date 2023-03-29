#pragma once
#include "Actor.h"

class Punch : public Actor
{
public:
	Punch(class Game* game, int direction);
	//オーバーライド
	void UpdateActor(float deltaTime) override;
private:
	//残留する時間
	float mEraseTimer;
};