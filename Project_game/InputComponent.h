#pragma once
#include "MoveComponent.h"
#include <cstdint>

class InputComponent : public MoveComponent
{
public:
	InputComponent(class Actor* owner);

	void ProcessInput(const uint8_t* keyState)override;
	void Update(float deltaTime) override;

	//�e��Q�b�^�[�y�уZ�b�^�[
	int GetMaxSpeed()const { return mMaxSpeed; }
	int GetRightKey()const { return mRightKey; }
	int GetLeftKey()const { return mLeftKey; }
	int GetUpKey()const { return mUpKey; }
	int GetDownKey()const { return mDownKey; }

	void SetMaxSpeed(float speed) { mMaxSpeed = speed; }
	void SetRightKey(int key) { mRightKey = key; }
	void SetLeftKey(int key) { mLeftKey = key; }
	void SetUpKey(int key) { mUpKey = key; }
	void SetDownKey(int key) { mDownKey = key; }

private:
	//���x�̐ݒ�
	float mMaxSpeed;
	//x�����ɐi�ރL�[
	int mRightKey;
	int mLeftKey;
	//y�����ɐi�ރL�[
	int mUpKey;
	int mDownKey;
};