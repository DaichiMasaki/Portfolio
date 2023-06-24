#pragma once
#include "Actor.h"

class VanishBlock : public Actor
{
public:
	VanishBlock(class Game* game);
	
	void UpdateActor(float deltaTime) override;

	//�����Ă��邩�ǂ����̃Q�b�^�[
	bool GetVanish()const { return mVanish; }

private:
	//�u���b�N�������Ă邩�ǂ���
	bool mVanish;
	//�X�v���C�g�̃|�C���^
	class SpriteComponent* mSprite;
};