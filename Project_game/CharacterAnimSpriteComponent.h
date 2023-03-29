#pragma once
#include "SpriteComponent.h"
#include <vector>

//向きが重要なアニメーション
class CharacterAnimSpriteComponent : public SpriteComponent
{
public:
	CharacterAnimSpriteComponent(class Actor* owner, int drawOrder = 100);
	//フレームごとにアニメーションを更新する(componentからオーバーライドする)
	void Update(float deltaTime) override;
	//SpriteComponentからDrawをオーバーライド
	void Draw(SDL_Renderer* renderer);
	//アニメーションのFPSについてのゲッターとセッター
	float GetAnimFPS() const { return mAnimFPS; }
	void SetAnimFPS(float fps) { mAnimFPS = fps; }
	//アニメーション枚数のゲッターとセッター
	float GetNumber() const { return mNumber; }
	void SetNumber(float number) { mNumber = number; }

private:
	//現在表示しているフレーム
	float mCurrentFrame;
	//アニメーションのフレームレート
	float mAnimFPS;
	//アニメーションの枚数
	int mNumber;
	//方向ごとの処理のためのもの
	int mdirection;
};