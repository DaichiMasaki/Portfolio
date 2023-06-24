#include "Wand.h"
#include "AnimSpriteComponent.h"
#include "HitBoxComponent.h"
#include "Object.h"
#include "Game.h"

Wand::Wand(Game* game, int direction)
	:Actor(game)
	, mEraseTimer(0.12f)
{
	//描画するスプライト
	AnimSpriteComponent* asc = new AnimSpriteComponent(this);
	asc->SetTexture(game->GetTexture("Assets/Weapon.png"));
	asc->SetTexWidth(64);
	asc->SetTexHeight(32);
	asc->SetTexx(0);
	asc->SetTexy(0);
	asc->SetRotate(true);
	asc->SetAnimFPS(16);

	//当たり判定
	HitBoxComponent* hb = new HitBoxComponent(this);
	if (direction == 0 || direction == 1)
	{
		hb->Sethalfx(60);
		hb->Sethalfy(28);
	}
	else
	{
		hb->Sethalfx(28);
		hb->Sethalfy(60);
	}
	SetHitBox(hb);
}

void Wand::UpdateActor(float deltaTime)
{
	mEraseTimer -= deltaTime;
	//杖消滅判定
	if (mEraseTimer <= 0.0f)
	{
		SetState(Actor::State::EDead);
	}
}