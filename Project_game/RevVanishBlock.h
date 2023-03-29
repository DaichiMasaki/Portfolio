#pragma once
#include "Actor.h"

class RevVanishBlock : public Actor
{
public:
	RevVanishBlock(class Game* game);

	void UpdateActor(float deltatime) override;

	//�����Ă��邩�ǂ����̃Q�b�^�[
	bool GetVanish()const { return mVanish; }

private:
	//�u���b�N�������Ă邩�ǂ���
	bool mVanish;
	//�X�v���C�g�̃|�C���^
	class SpriteComponent* mSprite;
};