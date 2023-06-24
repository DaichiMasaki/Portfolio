#pragma once
#include "Component.h"
#include "SDL.h"

class SpriteComponent : public Component
{
public:
	//mDrawOrder���Ⴂ�قǉ����ɕ`��
	SpriteComponent(class Actor* owner, int drawOrder = 100);
	~SpriteComponent();

	virtual void Draw(SDL_Renderer* renderer);
	virtual void SetTexture(SDL_Texture* texture);

	void Update(float deltaTime) override;

	//�e��Q�b�^�[�ƃZ�b�^�[
	int GetDrawOrder()const { return mDrawOrder; }
	int GetTexWidth()const { return mTexWidth; }
	int GetTexHeight()const { return mTexHeight; }
	int GetTexx()const { return mTexx; }
	int GetTexy()const { return mTexy; }
	
	void SetDrawOrder(int draworder) { mDrawOrder = draworder; }
	void SetTexWidth(int w) { mTexWidth = w; }
	void SetTexHeight(int h) { mTexHeight = h; }
	void SetTexx(int x) { mTexx = x; }
	void SetTexy(int y) { mTexy = y; }

protected:
	//�`�悷��e�N�X�`��
	SDL_Texture* mTexture;
	//�`�揇��
	int mDrawOrder;
	//�e�N�X�`���̕��ƍ���
	int mTexWidth;
	int mTexHeight;
	//�e�N�X�`���̍��W
	int mTexx;
	int mTexy;
};