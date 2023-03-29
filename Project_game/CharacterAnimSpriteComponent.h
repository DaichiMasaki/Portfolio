#pragma once
#include "SpriteComponent.h"
#include <vector>

//�������d�v�ȃA�j���[�V����
class CharacterAnimSpriteComponent : public SpriteComponent
{
public:
	CharacterAnimSpriteComponent(class Actor* owner, int drawOrder = 100);
	//�t���[�����ƂɃA�j���[�V�������X�V����(component����I�[�o�[���C�h����)
	void Update(float deltaTime) override;
	//SpriteComponent����Draw���I�[�o�[���C�h
	void Draw(SDL_Renderer* renderer);
	//�A�j���[�V������FPS�ɂ��ẴQ�b�^�[�ƃZ�b�^�[
	float GetAnimFPS() const { return mAnimFPS; }
	void SetAnimFPS(float fps) { mAnimFPS = fps; }
	//�A�j���[�V���������̃Q�b�^�[�ƃZ�b�^�[
	float GetNumber() const { return mNumber; }
	void SetNumber(float number) { mNumber = number; }

private:
	//���ݕ\�����Ă���t���[��
	float mCurrentFrame;
	//�A�j���[�V�����̃t���[�����[�g
	float mAnimFPS;
	//�A�j���[�V�����̖���
	int mNumber;
	//�������Ƃ̏����̂��߂̂���
	int mdirection;
};