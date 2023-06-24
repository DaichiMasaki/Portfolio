#include "RevVanishBlock.h"
#include "SpriteComponent.h"
#include "HitBoxComponent.h"
#include "Crystal.h"
#include "Player.h"
#include "Game.h"

RevVanishBlock::RevVanishBlock(Game* game)
	:Actor(game)
	, mVanish(false)
{
	//当たり判定
	HitBoxComponent* hb = new HitBoxComponent(this);
	hb->Sethalfx(32);
	hb->Sethalfy(32);
	hb->SetShifty(32);
	SetHitBox(hb);

	//描画するスプライト
	mSprite = new SpriteComponent(this);
	mSprite->SetTexture(GetGame()->GetTexture("Assets/VanishBlock.png"));
	mSprite->SetTexWidth(32);
	mSprite->SetTexHeight(64);
	mSprite->SetTexx(64);
	mSprite->SetTexy(0);
}

void RevVanishBlock::UpdateActor(float deltaTime)
{
	//スイッチの判定用
	bool on = true;

	for (auto crystal : GetGame()->GetCrystal())
	{
		//一つでもオフがあればfalseにする
		if (crystal->GetOn() == false)
		{
			on = false;
			break;
		}
	}

	if (mVanish == true && on == false)
	{
		//フラグの切り替え
		mVanish = false;

		//スプライトの変更
		SpriteComponent* sp = new SpriteComponent(this);
		sp->SetTexture(GetGame()->GetTexture("Assets/VanishBlock.png"));
		sp->SetTexWidth(32);
		sp->SetTexHeight(64);
		sp->SetTexx(64);
		sp->SetTexy(0);
		delete mSprite;
		mSprite = sp;

		//当たり判定
		HitBoxComponent* hb = new HitBoxComponent(this);
		hb->Sethalfx(32);
		hb->Sethalfy(32);
		hb->SetShifty(32);
		SetHitBox(hb);

		if (Intersect(*(GetGame()->GetPlayer()->GetHitBox()), *hb))
		{
			GetGame()->GetPlayer()->SetState(Actor::State::EDead);
		}
	}
	else if (mVanish == false && on == true)
	{
		//フラグの切り替え
		mVanish = true;

		//スプライトの変更
		SpriteComponent* sp = new SpriteComponent(this);
		sp->SetTexture(GetGame()->GetTexture("Assets/VanishBlock.png"));
		sp->SetTexWidth(32);
		sp->SetTexHeight(64);
		sp->SetTexx(96);
		sp->SetTexy(0);
		delete mSprite;
		mSprite = sp;

		//当たり判定消滅
		delete GetHitBox();
	}
}