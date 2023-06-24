#include "PushComponent.h"
#include "Actor.h"
#include "Game.h"
#include "Math.h"

PushComponent::PushComponent(class Actor* owner)
	:MoveComponent(owner)
{

}

void PushComponent::Update(float deltaTime)
{
	Vector2 pos = mOwner->GetPosition();
}

bool Pushable(const int& power, const PushComponent& pc)
{
	return true;
}