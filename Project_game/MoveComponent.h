#pragma once
#include "Component.h"

class MoveComponent : public Component
{
public:
	MoveComponent(class Actor* owner, int updateOrder = 10);

	void Update(float deltaTime) override;

	float GetxSpeed() const { return mxSpeed; }
	float GetySpeed() const { return mySpeed; }
	void SetxSpeed(float speed) { mxSpeed = speed; }
	void SetySpeed(float speed) { mySpeed = speed; }

private:
	//�L�����𓮂������x(���Əc)
	float mxSpeed;
	float mySpeed;
};