#pragma once
#include "Actor.h"
#include <string>

class Crystal : public Actor
{
public:
	Crystal(class Game* game);

	//UpdateActorのオーバーライド
	void UpdateActor(float deltaTime)override;

	//ゲッター及びセッター
	bool GetOn()const { return mOn; }
	class SpriteComponent* GetSprite()const { return mSprite; }

	void SetOn(bool b) { mOn = b; }
	void SetSprite(class SpriteComponent* sp) { mSprite = sp; }

private:
	//スイッチがオンになってるかどうか
	bool mOn;

	//スプライトコンポーネントへのポインタ
	class SpriteComponent* mSprite;
};

void CrystalCreate(class Game* game, const std::string& fileName);