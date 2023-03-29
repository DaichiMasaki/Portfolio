#pragma once
#include "Actor.h"

class Player : public Actor
{
public:
	//�����Ă��镐��
	enum class Weapon
	{
		Punchi,
		Wand
	};

	Player(class Game* game);
	//�e��I�[�o�[���C�h
	void UpdateActor(float delaTime) override;
	void ActorInput(const uint8_t* keyState) override;

	//�e��Q�b�^�[�y�уZ�b�^�[

private:
	//�����Ă��镐��
	Weapon mWeapon;
	//�����Ă����
	int mDirection;
	//�U���̃N�[���^�C��
	float mAttackCooldown;
	//�U���Ȃǂ̍d��
	float mRigor;
	//�U�������ǂ���
	bool mAttack;
};