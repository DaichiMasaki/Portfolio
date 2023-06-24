#include "SpriteComponent.h"
#include "Actor.h"
#include "Game.h"

SpriteComponent::SpriteComponent(Actor* owner, int drawOrder)
	:Component(owner)
	,mDrawOrder(drawOrder)
	, mTexWidth(0)
	, mTexHeight(0)
	,mTexx(0)
	,mTexy(0)
{
	mOwner->GetGame()->AddSprite(this);
	Vector2 pos = mOwner->GetPosition();
}

SpriteComponent::~SpriteComponent()
{
	mOwner->GetGame()->RemoveSprite(this);
}

void SpriteComponent::Update(float deltaTime)
{
	//
	int dorder = GetDrawOrder();
	mDrawOrder = 100 + mOwner->GetPosition().y;
	if (dorder != mDrawOrder)
	{
		mOwner->GetGame()->RemoveSprite(this);
		mOwner->GetGame()->AddSprite(this);
	}
}

void SpriteComponent::Draw(SDL_Renderer* renderer)
{
	if (mTexture)
	{
		SDL_Rect picRect;
		picRect.w = mTexWidth;
		picRect.h = mTexHeight;
		picRect.x = mTexx;
		picRect.y = mTexy;

		//出力する長方形の定義
		SDL_Rect drawRect;
		//幅と高さを所有アクターのスケールで拡縮する
		drawRect.w = picRect.w * 2;
		drawRect.h = picRect.h * 2;
		//長方形の中心を所有アクターの位置に合わせる
		drawRect.x = static_cast<int>(mOwner->GetPosition().x - drawRect.w / 2);
		drawRect.y = static_cast<int>(mOwner->GetPosition().y - drawRect.h / 2);

		//描画する
		SDL_RenderCopyEx(
			renderer,
			mTexture, //描画するテクスチャ
			&picRect, //描画したいテクスチャの範囲
			&drawRect, //出力先の矩形
			0, //回転された回転角
			nullptr,//回転の中心
			SDL_FLIP_NONE//反転方法
		); 
	}
}

void SpriteComponent::SetTexture(SDL_Texture* texture)
{
	mTexture = texture;
	//テクスチャの幅と高さを決める
	SDL_QueryTexture(texture, nullptr, nullptr, &mTexWidth, &mTexHeight);
}