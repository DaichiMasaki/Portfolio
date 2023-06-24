#pragma once
#include "SpriteComponent.h"
#include <vector>

//回転などが必要なアニメーション
class AnimSpriteComponent : public SpriteComponent
{
public:
	AnimSpriteComponent(class Actor* owner, int drawOrder = 100, int number = 4);
	//フレームごとにアニメーションを更新する(componentからオーバーライドする)
	void Update(float deltaTime) override;
	//SpriteComponentからDrawをオーバーライド
	void Draw(SDL_Renderer* renderer);

	//各種ゲッター及びセッター
	float GetAnimFPS() const { return mAnimFPS; }
	int GetNumber() const { return mNumber; }

	void SetAnimFPS(float fps) { mAnimFPS = fps; }
	void SetNumber(int number) { mNumber = number; }
	void SetRotate(bool b) { mRotate = b; }

private:
	//現在表示しているフレーム
	float mCurrentFrame;
	//アニメーションのフレームレート
	float mAnimFPS;
	//アニメーションの枚数
	int mNumber;
	//取り込みたいエリアがタイルマップの何段目にあるか
	int mTiley;
	//回転するかどうか
	bool mRotate;
	//方向ごとの処理のためのもの
	double mDirection;
};