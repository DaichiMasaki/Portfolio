#pragma once
#include "Actor.h"

class Player : public Actor
{
public:
	//持っている武器
	enum class Weapon
	{
		Punchi,
		Wand
	};

	Player(class Game* game);
	//各種オーバーライド
	void UpdateActor(float delaTime) override;
	void ActorInput(const uint8_t* keyState) override;

	//各種ゲッター及びセッター

private:
	//持っている武器
	Weapon mWeapon;
	//向いてる向き
	int mDirection;
	//攻撃のクールタイム
	float mAttackCooldown;
	//攻撃などの硬直
	float mRigor;
	//攻撃中かどうか
	bool mAttack;
};