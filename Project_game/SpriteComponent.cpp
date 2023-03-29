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

		//�o�͂��钷���`�̒�`
		SDL_Rect drawRect;
		//���ƍ��������L�A�N�^�[�̃X�P�[���Ŋg�k����
		drawRect.w = picRect.w * 2;
		drawRect.h = picRect.h * 2;
		//�����`�̒��S�����L�A�N�^�[�̈ʒu�ɍ��킹��
		drawRect.x = static_cast<int>(mOwner->GetPosition().x - drawRect.w / 2);
		drawRect.y = static_cast<int>(mOwner->GetPosition().y - drawRect.h / 2);

		//�`�悷��
		SDL_RenderCopyEx(
			renderer,
			mTexture, //�`�悷��e�N�X�`��
			&picRect, //�`�悵�����e�N�X�`���͈̔�
			&drawRect, //�o�͐�̋�`
			0, //��]���ꂽ��]�p
			nullptr,//��]�̒��S
			SDL_FLIP_NONE//���]���@
		); 
	}
}

void SpriteComponent::SetTexture(SDL_Texture* texture)
{
	mTexture = texture;
	//�e�N�X�`���̕��ƍ��������߂�
	SDL_QueryTexture(texture, nullptr, nullptr, &mTexWidth, &mTexHeight);
}