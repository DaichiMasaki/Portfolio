#pragma once
#include "Actor.h"

class RevVanishBlock : public Actor
{
public:
	RevVanishBlock(class Game* game);

	void UpdateActor(float deltatime) override;

	//消えているかどうかのゲッター
	bool GetVanish()const { return mVanish; }

private:
	//ブロックが消えてるかどうか
	bool mVanish;
	//スプライトのポインタ
	class SpriteComponent* mSprite;
};