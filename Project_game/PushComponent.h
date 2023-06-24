#pragma once
#include "MoveComponent.h"

class PushComponent : public MoveComponent
{
public:
	PushComponent(class Actor* owner);

	//�A�b�v�f�[�g�̃I�[�o�[���C�h
	void Update(float deltaTime) override;
	
private:
};

bool Pushable(const int& power, const PushComponent& pc);