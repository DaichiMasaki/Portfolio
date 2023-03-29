#include "InputComponent.h"
#include "HitBoxComponent.h"
#include "Actor.h"
#include "Player.h"
#include "Wall.h"
#include "Object.h"
#include "Crystal.h"
#include "VanishBlock.h"
#include "RevVanishBlock.h"
#include "Game.h"

InputComponent::InputComponent(class Actor* owner)
	:MoveComponent(owner)
	, mMaxSpeed(0.0f)
	, mRightKey(0)
	, mLeftKey(0)
	, mUpKey(0)
	, mDownKey(0)
{

}

void InputComponent::ProcessInput(const uint8_t* keyState)
{

	//スピードを管理
	float xSpeed = 0.0f;
	float ySpeed = 0.0f;
	if (keyState[mRightKey])
	{
		xSpeed += mMaxSpeed;
	}
	if (keyState[mLeftKey])
	{
		xSpeed -= mMaxSpeed;
	}
	if (keyState[mDownKey])
	{
		ySpeed += mMaxSpeed;
	}
	if (keyState[mUpKey])
	{
		ySpeed -= mMaxSpeed;
	}

	SetxSpeed(xSpeed);
	SetySpeed(ySpeed);
}

void InputComponent::Update(float deltaTime)
{
	//プレイヤーの当たり判定（x、yに分けて判定を行う）
	if (mOwner->GetDirection() != Actor::Direction::Stop)
	{
		Vector2 pos = mOwner->GetPosition();

		pos.x += GetxSpeed() * deltaTime;
		mOwner->SetPosition(pos);

		//プレイヤーとクレートの当たり判定
		for (auto crate : mOwner->GetGame()->GetObjects())
		{
			if (Intersect(*(mOwner->GetHitBox()), *(crate->GetHitBox())))
			{
				while (Intersect(*(mOwner->GetHitBox()), *(crate->GetHitBox())))
				{
					if (GetxSpeed() >= 0)
					{
						pos.x -= 1.0f;
						mOwner->SetPosition(pos);
					}
					else
					{
						pos.x += 1.0f;
						mOwner->SetPosition(pos);
					}
				}
			}
		}
		//プレイヤーと壁の当たり判定
		for (auto wall : mOwner->GetGame()->GetWalls())
		{
			if (Intersect(*(mOwner->GetHitBox()), *(wall->GetHitBox())))
			{
				while (Intersect(*(mOwner->GetHitBox()), *(wall->GetHitBox())))
				{
					if (GetxSpeed() >= 0)
					{
						pos.x -= 1.0f;
						mOwner->SetPosition(pos);
					}
					else
					{
						pos.x += 1.0f;
						mOwner->SetPosition(pos);
					}
				}
			}
		}
		//クリスタルの当たり判定
		for (auto crystal : mOwner->GetGame()->GetCrystal())
		{
			if (Intersect(*(mOwner->GetHitBox()), *(crystal->GetHitBox())))
			{
				while (Intersect(*(mOwner->GetHitBox()), *(crystal->GetHitBox())))
				{
					if (GetxSpeed() >= 0)
					{
						pos.x -= 1.0f;
						mOwner->SetPosition(pos);
					}
					else
					{
						pos.x += 1.0f;
						mOwner->SetPosition(pos);
					}
				}
			}
		}
		//クリスタルに対応したブロックが現れていれば当たり判定を判定
		if (mOwner->GetGame()->GetVBlocks().front()->GetVanish() == false)
		{
			for (auto block : mOwner->GetGame()->GetVBlocks())
			{
				if (Intersect(*(mOwner->GetHitBox()), *(block->GetHitBox())))
				{
					while (Intersect(*(mOwner->GetHitBox()), *(block->GetHitBox())))
					{
						if (GetxSpeed() >= 0)
						{
							pos.x -= 1.0f;
							mOwner->SetPosition(pos);
						}
						else
						{
							pos.x += 1.0f;
							mOwner->SetPosition(pos);
						}
					}
				}
			}
		}
		//上記の逆なら判定
		else
		{
			for (auto block : mOwner->GetGame()->GetRevVBlocks())
			{
				if (Intersect(*(mOwner->GetHitBox()), *(block->GetHitBox())))
				{
					while (Intersect(*(mOwner->GetHitBox()), *(block->GetHitBox())))
					{
						if (GetxSpeed() >= 0)
						{
							pos.x -= 1.0f;
							mOwner->SetPosition(pos);
						}
						else
						{
							pos.x += 1.0f;
							mOwner->SetPosition(pos);
						}
					}
				}
			}
		}

		//以下xと同じ工程
		pos.y += GetySpeed() * deltaTime;
		mOwner->SetPosition(pos);

		for (auto crate : mOwner->GetGame()->GetObjects())
		{
			if (Intersect(*(mOwner->GetHitBox()), *(crate->GetHitBox())))
			{
				while (Intersect(*(mOwner->GetHitBox()), *(crate->GetHitBox())))
				{
					if (GetySpeed() >= 0)
					{
						pos.y -= 1.0f;
						mOwner->SetPosition(pos);
					}
					else
					{
						pos.y += 1.0f;
						mOwner->SetPosition(pos);
					}
				}
			}
		}
		for (auto wall : mOwner->GetGame()->GetWalls())
		{
			if (Intersect(*(mOwner->GetHitBox()), *(wall->GetHitBox())))
			{
				while (Intersect(*(mOwner->GetHitBox()), *(wall->GetHitBox())))
				{
					if (GetySpeed() >= 0)
					{
						pos.y -= 1.0f;
						mOwner->SetPosition(pos);
					}
					else
					{
						pos.y += 1.0f;
						mOwner->SetPosition(pos);
					}
				}
			}
		}
		for (auto crystal : mOwner->GetGame()->GetCrystal())
		{
			if (Intersect(*(mOwner->GetHitBox()), *(crystal->GetHitBox())))
			{
				while (Intersect(*(mOwner->GetHitBox()), *(crystal->GetHitBox())))
				{
					if (GetySpeed() >= 0)
					{
						pos.y -= 1.0f;
						mOwner->SetPosition(pos);
					}
					else
					{
						pos.y += 1.0f;
						mOwner->SetPosition(pos);
					}
				}
			}
		}
		if (mOwner->GetGame()->GetVBlocks().front()->GetVanish() == false)
		{
			for (auto block : mOwner->GetGame()->GetVBlocks())
			{
				if (Intersect(*(mOwner->GetHitBox()), *(block->GetHitBox())))
				{
					while (Intersect(*(mOwner->GetHitBox()), *(block->GetHitBox())))
					{
						if (GetySpeed() >= 0)
						{
							pos.y -= 1.0f;
							mOwner->SetPosition(pos);
						}
						else
						{
							pos.y += 1.0f;
							mOwner->SetPosition(pos);
						}
					}
				}
			}
		}
		else
		{
			for (auto block : mOwner->GetGame()->GetRevVBlocks())
			{
				if (Intersect(*(mOwner->GetHitBox()), *(block->GetHitBox())))
				{
					while (Intersect(*(mOwner->GetHitBox()), *(block->GetHitBox())))
					{
						if (GetySpeed() >= 0)
						{
							pos.y -= 1.0f;
							mOwner->SetPosition(pos);
						}
						else
						{
							pos.y += 1.0f;
							mOwner->SetPosition(pos);
						}
					}
				}
			}
		}
	}
}