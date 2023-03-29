#include "AnimSpriteComponent.h"
#include "Actor.h"
#include "Math.h"

AnimSpriteComponent::AnimSpriteComponent(Actor* owner, int drawOrder, int number)
	:SpriteComponent(owner, drawOrder)
	,mCurrentFrame(0.0f)
	,mAnimFPS(10.0f)
	,mNumber(number)
	,mTiley(0)
	,mRotate(false)
	,mDirection(0)
{

}

void AnimSpriteComponent::Update(float deltaTime)
{
	SpriteComponent::Update(deltaTime);

	//フレーム更新
	mCurrentFrame += mAnimFPS * deltaTime;

	//必要に応じてフレームの巻き戻し
	while (mCurrentFrame >= mNumber)
	{
		mCurrentFrame -= mNumber;
	}

	//方向ごとに画像を分ける処理
	if (mOwner->GetDirection() == Actor::Direction::Down)
	{
		mDirection = 0.0f;
	}
	else if (mOwner->GetDirection() == Actor::Direction::Up)
	{
		mDirection = 2.0f;
	}
	else if (mOwner->GetDirection() == Actor::Direction::Right)
	{
		mDirection = 3.0f;
	}
	else if (mOwner->GetDirection() == Actor::Direction::Left)
	{
		mDirection = 1.0f;
	}
}

void AnimSpriteComponent::Draw(SDL_Renderer* renderer)
{
	//タイルマップから画像を持ってくる
	SDL_Rect picRect;
	//横にmNumber個の画像がつながってる
	picRect.w = GetTexWidth();
	picRect.h = GetTexHeight();
	picRect.x = picRect.x = (GetTexWidth()) * (static_cast<int>(mCurrentFrame));
	picRect.y = picRect.h * mTiley;

	//出力する規格
	SDL_Rect drawRect;
	drawRect.w = picRect.w * 2;
	drawRect.h = picRect.h * 2;
	drawRect.x = static_cast<int>(mOwner->GetPosition().x - drawRect.w / 2);
	drawRect.y = static_cast<int>(mOwner->GetPosition().y - drawRect.h / 2);
	//回転するかどうか
	if (mRotate)
	{
		SDL_RenderCopyEx(
			renderer,
			mTexture,
			&picRect,
			&drawRect,
			90 * mDirection,
			nullptr,
			SDL_FLIP_NONE
		);
	}
	else
	{
		SDL_RenderCopyEx(
			renderer,
			mTexture,
			&picRect,
			&drawRect,
			0,
			nullptr,
			SDL_FLIP_NONE
		);
	}
}