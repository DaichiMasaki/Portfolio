#include "HitBoxComponent.h"
#include "Actor.h"

HitBoxComponent::HitBoxComponent(Actor* owner)
	:Component(owner)
	, mhalfx(0.0f)
	, mhalfy(0.0f)
	,mShiftx(0.0f)
	,mShifty(0.0f)
{

}

float HitBoxComponent::Gethalfx() const
{
	return mOwner->GetScale() * mhalfx;
}

float HitBoxComponent::Gethalfy() const
{
	return mOwner->GetScale() * mhalfy;
}

const Vector2& HitBoxComponent::GetCenter() const
{
	return mOwner->GetPosition();
}

bool Intersect(const HitBoxComponent& a, const HitBoxComponent& b)
{
	//‹——£‚ð‘ª‚é
	float diffx = (a.GetCenter().x + a.GetShiftx()) - (b.GetCenter().x + b.GetShiftx());
	if (diffx < 0)
	{
		diffx = diffx * (-1);
	}
	float diffy = (a.GetCenter().y + a.GetShifty()) - (b.GetCenter().y + b.GetShifty());
	if (diffy < 0)
	{
		diffy = diffy * (-1);
	}

	//‚»‚ê‚¼‚ê‚ÌxAy‚Ì”¼•ª‚Ì’l‚ð‘«‚µ‡‚í‚¹‚é
	float sumhalfx = a.Gethalfx() + b.Gethalfx();
	float sumhalfy = a.Gethalfy() + b.Gethalfy();

	return (diffx < sumhalfx) && (diffy < sumhalfy);
}