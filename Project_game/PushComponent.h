#pragma once
#include "MoveComponent.h"

class PushComponent : public MoveComponent
{
public:
	PushComponent(class Actor* owner);

	//アップデートのオーバーライド
	void Update(float deltaTime) override;
	
private:
};

bool Pushable(const int& power, const PushComponent& pc);