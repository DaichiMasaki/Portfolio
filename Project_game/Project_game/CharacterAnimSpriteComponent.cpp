#include "CharacterAnimSpriteComponent.h"
#include "Actor.h"
#include "Math.h"

CharacterAnimSpriteComponent::CharacterAnimSpriteComponent(Actor* owner, int drawOrder)
	:SpriteComponent(owner, drawOrder)
	,mCurrentFrame(0.0f)
	,mAnimFPS(10.0f)
	,mNumber(4)
	,mdirection(0)
{

}

void CharacterAnimSpriteComponent::Update(float deltaTime)
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
		mdirection = 0;
	}
	else if (mOwner->GetDirection() == Actor::Direction::Up)
	{
		mdirection = 1;
	}
	else if (mOwner->GetDirection() == Actor::Direction::Right)
	{
		mdirection = 2;
	}
	else if (mOwner->GetDirection() == Actor::Direction::Left)
	{
		mdirection = 3;
	}
}

void CharacterAnimSpriteComponent::Draw(SDL_Renderer* renderer)
{
	//タイルマップから画像を持ってくる
	SDL_Rect picRect;
	//横に４つ画像がつながってる
	picRect.w = GetTexWidth() / mNumber;
	picRect.h = GetTexWidth() / mNumber;
	if (mOwner->GetDirection() == Actor::Direction::Stop)
	{
		picRect.x = 0;
	}
	else
	{
		picRect.x = (GetTexWidth() / mNumber) * (static_cast<int>(mCurrentFrame));
	}
	picRect.y = (GetTexWidth() / mNumber) * mdirection;
	//出力する規格
	SDL_Rect drawRect;
	drawRect.w = picRect.w * 2;
	drawRect.h = picRect.h * 2;
	drawRect.x = static_cast<int>(mOwner->GetPosition().x - drawRect.w / 2);
	drawRect.y = static_cast<int>(mOwner->GetPosition().y - drawRect.h / 2);

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