#pragma once
#include "Actor.h"

class Punch : public Actor
{
public:
	Punch(class Game* game, int direction);
	//�I�[�o�[���C�h
	void UpdateActor(float deltaTime) override;
private:
	//�c�����鎞��
	float mEraseTimer;
};