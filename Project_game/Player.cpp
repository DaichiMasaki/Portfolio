#include "Player.h"
#include "CharacterAnimSpriteComponent.h"
#include "HitBoxComponent.h"
#include "InputComponent.h"
#include "Game.h"
#include "Punch.h"
#include "Wand.h"
#include "Magic.h"

Player::Player(Game* game)
	:Actor(game)
	,mWeapon(Weapon::Wand)
	,mAttackCooldown(0.0f)
	,mDirection(0.0f)
	,mRigor(0.0f)
	,mAttack(false)
{
	//�`�悷��X�v���C�g�R���|�[�l���g(�A�j���[�V����)
	CharacterAnimSpriteComponent* csc = new CharacterAnimSpriteComponent(this, 150);
	csc->SetTexture(game->GetTexture("Assets/Player.png"));
	
	//�����蔻��
	HitBoxComponent* hb = new HitBoxComponent(this);
	hb->Sethalfx(16);
	hb->Sethalfy(16);
	hb->SetShiftx(0);
	hb->SetShifty(16);
	SetHitBox(hb);

	//�L�[�����t
	InputComponent* ic = new InputComponent(this);
	ic->SetUpKey(SDL_SCANCODE_W);
	ic->SetDownKey(SDL_SCANCODE_S);
	ic->SetRightKey(SDL_SCANCODE_D);
	ic->SetLeftKey(SDL_SCANCODE_A);
	ic->SetMaxSpeed(300.0f);
}

void Player::UpdateActor(float deltaTime)
{
	if (mAttackCooldown > 0)
	{
		mAttackCooldown -= deltaTime;
	}
	if (mRigor > 0)
	{
		mRigor -= deltaTime;
		if (mRigor <= 0)
		{
			mAttack = false;
		}
	}
}

void Player::ActorInput(const uint8_t* KeyState)
{
	if (!mAttack) {
		//�e��L�[���������Ƃ��̃L�����������������w��
		if (KeyState[SDL_SCANCODE_W] && KeyState[SDL_SCANCODE_S] && KeyState[SDL_SCANCODE_D] && KeyState[SDL_SCANCODE_A])
		{
			SetDirection(Direction::Stop);
		}
		else if (KeyState[SDL_SCANCODE_S] && KeyState[SDL_SCANCODE_D] && KeyState[SDL_SCANCODE_A])
		{
			SetDirection(Direction::Down);
			mDirection = 0;
		}
		else if (KeyState[SDL_SCANCODE_W] && KeyState[SDL_SCANCODE_D] && KeyState[SDL_SCANCODE_A])
		{
			SetDirection(Direction::Up);
			mDirection = 1;
		}
		else if (KeyState[SDL_SCANCODE_D] && KeyState[SDL_SCANCODE_W] && KeyState[SDL_SCANCODE_S])
		{
			SetDirection(Direction::Right);
			mDirection = 2;
		}
		else if (KeyState[SDL_SCANCODE_A] && KeyState[SDL_SCANCODE_W] && KeyState[SDL_SCANCODE_S])
		{
			SetDirection(Direction::Left);
			mDirection = 3;
		}
		else if (KeyState[SDL_SCANCODE_W] && KeyState[SDL_SCANCODE_S])
		{
			SetDirection(Direction::Stop);
		}
		else if (KeyState[SDL_SCANCODE_D] && KeyState[SDL_SCANCODE_A])
		{
			SetDirection(Direction::Stop);
		}
		else if (KeyState[SDL_SCANCODE_S])
		{
			SetDirection(Direction::Down);
			mDirection = 0;
		}
		else if (KeyState[SDL_SCANCODE_W])
		{
			SetDirection(Direction::Up);
			mDirection = 1;
		}
		else if (KeyState[SDL_SCANCODE_D])
		{
			SetDirection(Direction::Right);
			mDirection = 2;
		}
		else if (KeyState[SDL_SCANCODE_A])
		{
			SetDirection(Direction::Left);
			mDirection = 3;
		}
		else
		{
			SetDirection(Direction::Stop);
		}

		//�U���̃L�[
		if (KeyState[SDL_SCANCODE_SPACE] && mAttackCooldown <= 0 && mWeapon == Weapon::Punchi)
		{
			//�U��������
			Punch* punch = new Punch(GetGame(), mDirection);
			if (mDirection == 0)
			{
				Vector2 pos(GetPosition().x + GetHitBox()->GetShiftx(), GetPosition().y + GetHitBox()->GetShifty() + 10);
				punch->SetPosition(pos);
			}
			else if (mDirection == 1)
			{
				Vector2 pos(GetPosition().x + GetHitBox()->GetShiftx(), GetPosition().y - GetHitBox()->GetShifty() - 10);
				punch->SetPosition(pos);
			}
			else if (mDirection == 2)
			{
				Vector2 pos(GetPosition().x + GetHitBox()->GetShiftx() + 30, GetPosition().y + GetHitBox()->GetShifty());
				punch->SetPosition(pos);
			}
			else
			{
				Vector2 pos(GetPosition().x - GetHitBox()->GetShiftx() - 30, GetPosition().y + GetHitBox()->GetShifty());
				punch->SetPosition(pos);
			}
			//�U���̃N�[���_�E���̏���
			mAttackCooldown = 0.3f;
			//�d������
			mRigor = 0.075;
			mAttack = true;
		}
		else if (KeyState[SDL_SCANCODE_SPACE] && mAttackCooldown <= 0 && mWeapon == Weapon::Wand)
		{
			//�U��������
			Wand* wand = new Wand(GetGame(), mDirection);
			Magic* magic = new Magic(GetGame(), mDirection);
			if (mDirection == 0)
			{
				Vector2 pos(GetPosition().x + GetHitBox()->GetShiftx(), GetPosition().y + GetHitBox()->GetShifty() + 32);
				wand->SetPosition(pos);
				wand->SetDirection(Actor::Direction::Down);
				magic->SetPosition(pos);
			}
			else if (mDirection == 1)
			{
				Vector2 pos(GetPosition().x + GetHitBox()->GetShiftx(), GetPosition().y + GetHitBox()->GetShifty() - 32);
				wand->SetPosition(pos);
				wand->SetDirection(Actor::Direction::Up);
				magic->SetPosition(pos);
			}
			else if (mDirection == 2)
			{
				Vector2 pos(GetPosition().x + GetHitBox()->GetShiftx() + 32, GetPosition().y + GetHitBox()->GetShifty());
				wand->SetPosition(pos);
				wand->SetDirection(Actor::Direction::Right);
				magic->SetPosition(pos);
			}
			else
			{
				Vector2 pos(GetPosition().x + GetHitBox()->GetShiftx() - 32, GetPosition().y + GetHitBox()->GetShifty());
				wand->SetPosition(pos);
				wand->SetDirection(Actor::Direction::Left);
				magic->SetPosition(pos);
			}
			//�U���̃N�[���_�E���̏���
			mAttackCooldown = 0.3f;
			//�d������
			mRigor = 0.12;
			mAttack = true;
		}
	}
	else
	{
		SetDirection(Direction::Stop);
	}
}