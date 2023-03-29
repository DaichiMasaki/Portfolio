#pragma once
#include "Component.h"
#include "SDL.h"

class SpriteComponent : public Component
{
public:
	//mDrawOrderが低いほど遠くに描画
	SpriteComponent(class Actor* owner, int drawOrder = 100);
	~SpriteComponent();

	virtual void Draw(SDL_Renderer* renderer);
	virtual void SetTexture(SDL_Texture* texture);

	void Update(float deltaTime) override;

	//各種ゲッターとセッター
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
	//描画するテクスチャ
	SDL_Texture* mTexture;
	//描画順序
	int mDrawOrder;
	//テクスチャの幅と高さ
	int mTexWidth;
	int mTexHeight;
	//テクスチャの座標
	int mTexx;
	int mTexy;
};