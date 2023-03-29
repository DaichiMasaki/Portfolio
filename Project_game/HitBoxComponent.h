#pragma once
#include "Component.h"
#include "Math.h"

class HitBoxComponent : public Component
{
public:
	HitBoxComponent(class Actor* owner);
	//�e��Q�b�^�[�y�уZ�b�^�[
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
	//x��y�̒�������̒���
	float mhalfx;
	float mhalfy;
	//�ʒu�����p�̂��炵��
	float mShiftx;
	float mShifty;
};

//�����蔻��
bool Intersect(const HitBoxComponent& a, const HitBoxComponent& b);