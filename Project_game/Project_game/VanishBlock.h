#pragma once
#include "Actor.h"

class VanishBlock : public Actor
{
public:
	VanishBlock(class Game* game);
	
	void UpdateActor(float deltaTime) override;

	//消えているかどうかのゲッター
	bool GetVanish()const { return mVanish; }

private:
	//ブロックが消えてるかどうか
	bool mVanish;
	//スプライトのポインタ
	class SpriteComponent* mSprite;
};