#pragma once
#include "Component.h"
#include "Math.h"

class HitBoxComponent : public Component
{
public:
	HitBoxComponent(class Actor* owner);
	//各種ゲッター及びセッター
	float Gethalfx() const;
	float Gethalfy() const;
	float GetShiftx() const { return mShiftx; }
	float GetShifty() const { return mShifty; }

	void Sethalfx(float x) { mhalfx = x; }
	void Sethalfy(float y) { mhalfy = y; }
	void SetShiftx(float x) { mShiftx = x; }
	void SetShifty(float y) { mShifty = y; }

	const Vector2& GetCenter() const;

private:
	//xとyの中央からの長さ
	float mhalfx;
	float mhalfy;
	//位置調整用のずらし幅
	float mShiftx;
	float mShifty;
};

//当たり判定
bool Intersect(const HitBoxComponent& a, const HitBoxComponent& b);