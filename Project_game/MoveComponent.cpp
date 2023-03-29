#include "MoveComponent.h"
#include "Actor.h"

MoveComponent::MoveComponent(class Actor* owner, int updateOrder)
	:Component(owner, updateOrder)
	,mxSpeed(0.0f)
	,mySpeed(0.0f)
{

}

void MoveComponent::Update(float deltaTime)
{
	Vector2 pos = mOwner->GetPosition();
	pos.x += mxSpeed * deltaTime;
	pos.y += mySpeed * deltaTime;

	mOwner->SetPosition(pos);
}