#include "Punch.h"
#include "SpriteComponent.h"
#include "HitBoxComponent.h"
#include "MoveComponent.h"
#include "Object.h"
#include "Game.h"

Punch::Punch(Game* game, int direction)
	:Actor(game)
	,mEraseTimer(0.05f)
{
	//�`�悷��X�v���C�g
	SpriteComponent* sc = new SpriteComponent(this);
	sc->SetTexture(game->GetTexture("Assets/Punchi.png"));
	sc->SetTexWidth(32);
	sc->SetTexHeight(32);
	sc->SetTexx(sc->GetTexWidth() * direction);
	sc->SetTexy(0);
	//�����蔻��
	HitBoxComponent* hb = new HitBoxComponent(this);
	hb->Sethalfx(20);
	hb->Sethalfy(20);
	SetHitBox(hb);

	//�����ɂ���đł�����
	MoveComponent* mc = new MoveComponent(this);
	if (direction == 0)
	{
		mc->SetySpeed(100);
	}
	else if (direction == 1)
	{
		mc->SetySpeed(-100);
	}
	else if (direction == 2)
	{
		mc->SetxSpeed(100);
	}
	else
	{
		mc->SetxSpeed(-100);
	}
}

void Punch::UpdateActor(float deltaTime)
{
	mEraseTimer -= deltaTime;
	//�p���`���Ŕ���
	if (mEraseTimer <= 0.0f)
	{
		SetState(Actor::State::EDead);
	}
	else
	{
		//���ׂẴN���[�g�ɑ΂��ē����蔻��𒲂ׂ�
		for (auto crate : GetGame()->GetObjects())
		{
			if (Intersect(*GetHitBox(), *(crate->GetHitBox())))
			{
				//�p���`������������N���[�g����
				crate->SetState(Actor::State::EDead);
			}
		}
	}
}