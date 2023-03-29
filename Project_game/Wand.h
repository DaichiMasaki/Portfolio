#pragma once
#include "Actor.h"

class Wand : public Actor
{
public:
	Wand(class Game* game, int direction = 0);

	void UpdateActor(float deltaTime) override;

private:
	//Žc—¯‚·‚éŽžŠÔ
	float mEraseTimer;
};