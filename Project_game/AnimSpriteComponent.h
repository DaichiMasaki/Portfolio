#pragma once
#include "SpriteComponent.h"
#include <vector>

//��]�Ȃǂ��K�v�ȃA�j���[�V����
class AnimSpriteComponent : public SpriteComponent
{
public:
	AnimSpriteComponent(class Actor* owner, int drawOrder = 100, int number = 4);
	//�t���[�����ƂɃA�j���[�V�������X�V����(component����I�[�o�[���C�h����)
	void Update(float deltaTime) override;
	//SpriteComponent����Draw���I�[�o�[���C�h
	void Draw(SDL_Renderer* renderer);

	//�e��Q�b�^�[�y�уZ�b�^�[
	float GetAnimFPS() const { return mAnimFPS; }
	int GetNumber() const { return mNumber; }

	void SetAnimFPS(float fps) { mAnimFPS = fps; }
	void SetNumber(int number) { mNumber = number; }
	void SetRotate(bool b) { mRotate = b; }

private:
	//���ݕ\�����Ă���t���[��
	float mCurrentFrame;
	//�A�j���[�V�����̃t���[�����[�g
	float mAnimFPS;
	//�A�j���[�V�����̖���
	int mNumber;
	//��荞�݂����G���A���^�C���}�b�v�̉��i�ڂɂ��邩
	int mTiley;
	//��]���邩�ǂ���
	bool mRotate;
	//�������Ƃ̏����̂��߂̂���
	double mDirection;
};