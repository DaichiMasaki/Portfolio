#include "Actor.h"
#include "Game.h"
#include "Component.h"
#include "HitBoxComponent.h"
#include <algorithm>

Actor::Actor(Game* game)
	:mState(State::EActive)
	, mDirection(Direction::Stop)
	, mPosition(Vector2::Zero)
	, mScale(1.0f)
	, mRotation(0.0f)
	, mHitBox(nullptr)
	, mGame(game)
{
	mGame->AddActor(this);
}

Actor::~Actor()
{
	mGame->RemoveActor(this);
	//�R���|�[�l���g�������K�v������
	//������~Component��RemoveComponent���ĂԂ��߈Ⴄ��@�Ń��[�v������K�v������
	while (!mComponents.empty())
	{
		delete mComponents.back();
	}
}

void Actor::Update(float deltaTime)
{
	if (mState == State::EActive)
	{
		UpdateComponents(deltaTime);
		UpdateActor(deltaTime);
	}
}

void Actor::UpdateComponents(float deltaTime)
{
	for (auto comp : mComponents)
	{
		comp->Update(deltaTime);
	}
}

void Actor::UpdateActor(float deltaTime)
{

}

void Actor::ProcessInput(const uint8_t* keyState)
{
	if (mState == State::EActive)
	{
		//���ׂẴR���|�[�l���g�ɑ΂��ăL�[���͂�K�p
		for (auto compo : mComponents)
		{
			compo->ProcessInput(keyState);
		}

		ActorInput(keyState);
	}
}

void Actor::ActorInput(const uint8_t* keyState)
{

}

void Actor::AddComponent(Component* component)
{
	//mUpdateOrder�ɂ�萮�񂳂ꂽ�R���|�[�l���g�Q�ɔԍ���������Ȃ��悤�ɑ}��
	int myOrder = component->GetUpdateOrder();
	auto iter = mComponents.begin();
	for (; iter != mComponents.end(); ++iter)
	{
		if (myOrder < (*iter)->GetUpdateOrder())
		{
			break;
		}
	}

	//�v�f��iter�̒��O�ɑ}��
	mComponents.insert(iter, component);
}

void Actor::RemoveComponent(Component* component)
{
	auto iter = std::find(mComponents.begin(), mComponents.end(), component);
	if (iter != mComponents.end())
	{
		mComponents.erase(iter);
	}
}