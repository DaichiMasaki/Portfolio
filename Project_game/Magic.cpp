#include "Magic.h"
#include "AnimSpriteComponent.h"
#include "HitBoxComponent.h"
#include "MoveComponent.h"
#include "Object.h"
#include "Wall.h"
#include "Crystal.h"
#include "Game.h"

Magic::Magic(Game* game, int direction)
	:Actor(game)
	,mEraseTimer(5.0f)
{
	//�`�悷��X�v���C�g
	AnimSpriteComponent* asc = new AnimSpriteComponent(this);
	asc->SetTexture(game->GetTexture("Assets/Magic.png"));
	asc->SetTexWidth(32);
	asc->SetTexHeight(32);
	asc->SetTexx(0);
	asc->SetTexy(0);
	asc->SetRotate(true);
	asc->SetAnimFPS(20.0f);

	//�����蔻��
	HitBoxComponent* hb = new HitBoxComponent(this);
	hb->Sethalfx(10);
	hb->Sethalfy(10);
	SetHitBox(hb);

	//����
	MoveComponent* mc = new MoveComponent(this);
	if (direction == 0)
	{
		mc->SetySpeed(500);
	}
	else if (direction == 1)
	{
		mc->SetySpeed(-500);
	}
	else if (direction == 2)
	{
		mc->SetxSpeed(500);
	}
	else
	{
		mc->SetxSpeed(-500);
	}
}

void Magic::UpdateActor(float deltaTime)
{
	mEraseTimer -= deltaTime;
	//���@�e���Ŕ���
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
				//���@�e�����������疂�@�e�ƃN���[�g����
				crate->SetState(Actor::State::EDead);
				SetState(Actor::State::EDead);
				break;
			}
		}
		//���ׂẴX�C�b�`�ɑ΂��ē����蔻��𒲂ׂ�
		for (auto crystal : GetGame()->GetCrystal())
		{
			if (Intersect(*GetHitBox(), *(crystal->GetHitBox())))
			{
				//���@�e�����������疂�@�e���łƂƂ��ɃX�C�b�`�؂�ւ�
				if (crystal->GetOn() == false)
				{
					crystal->SetOn(true);

					SpriteComponent* sp = new SpriteComponent(crystal);
					sp->SetTexture(GetGame()->GetTexture("Assets/Crystal.png"));
					sp->SetTexWidth(32);
					sp->SetTexHeight(32);
					sp->SetTexx(32);
					sp->SetTexy(0);

					delete crystal->GetSprite();
					crystal->SetSprite(sp);

					SetState(Actor::State::EDead);
					break;
				}
				else
				{
					crystal->SetOn(false);

					SpriteComponent* sp = new SpriteComponent(crystal);
					sp->SetTexture(GetGame()->GetTexture("Assets/Crystal.png"));
					sp->SetTexWidth(32);
					sp->SetTexHeight(32);
					sp->SetTexx(0);
					sp->SetTexy(0);

					delete crystal->GetSprite();
					crystal->SetSprite(sp);

					SetState(Actor::State::EDead);
					break;
				}
			}
		}
		//���ׂĂ̕ǂɑ΂��ē����蔻��𒲂ׂ�
		for (auto wall : GetGame()->GetWalls())
		{
			if (Intersect(*GetHitBox(), *(wall->GetHitBox())))
			{
				//�ǂɓ��������疂�@�e����
				SetState(Actor::State::EDead);
				break;
			}
		}
	}
}