#pragma once
#include "Actor.h"
#include <string>

class Crystal : public Actor
{
public:
	Crystal(class Game* game);

	//UpdateActor�̃I�[�o�[���C�h
	void UpdateActor(float deltaTime)override;

	//�Q�b�^�[�y�уZ�b�^�[
	bool GetOn()const { return mOn; }
	class SpriteComponent* GetSprite()const { return mSprite; }

	void SetOn(bool b) { mOn = b; }
	void SetSprite(class SpriteComponent* sp) { mSprite = sp; }

private:
	//�X�C�b�`���I���ɂȂ��Ă邩�ǂ���
	bool mOn;

	//�X�v���C�g�R���|�[�l���g�ւ̃|�C���^
	class SpriteComponent* mSprite;
};

void CrystalCreate(class Game* game, const std::string& fileName);