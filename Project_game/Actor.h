#pragma once
#include <vector>
#include "Math.h"

class Actor
{
public:
	enum class State
	{
		EActive,
		EPaused,
		EDead
	};

	enum class Direction
	{
		Down,
		Up,
		Right,
		Left,
		Stop
	};

	//�R���X�g���N�^�ƃf�X�g���N�^
	Actor(class Game* game);
	virtual ~Actor();

	//�Q�[������Ăяo�����X�V�֐�(�I�[�o�[���C�h�s��)
	void Update(float deltaTime);
	//�A�N�^�[�����S�R���|�[�l���g���X�V(�I�[�o�[���C�h�s��)
	void UpdateComponents(float deltaTime);
	//�A�N�^�[�Ǝ��̍X�V����(�I�[�o�[���C�h��)
	virtual void UpdateActor(float deltaTime);
	//�L�[���͎�t(�Q�[������Ă΂��)
	void ProcessInput(const uint8_t* keyState);
	//�A�N�^�[���Ƃ̃L�[���͎�t(�I�[�o�[���C�h��)
	virtual void ActorInput(const uint8_t* keyState);

	//�Q�b�^�[�ƃZ�b�^�[
	const Vector2& GetPosition() const { return mPosition; }
	float GetScale() const { return mScale; }	
	float GetRotation() const { return mRotation; }
	State GetState() const { return mState; }
	Direction GetDirection() const { return mDirection; }
	class HitBoxComponent* GetHitBox() { return mHitBox; }
	class Game* GetGame() { return mGame; }

	void SetPosition(const Vector2& pos) { mPosition = pos; }
	void SetScale(float scale) { mScale = scale; }
	void SetRotation(float rotation) { mRotation = rotation; }
	void SetState(State state) { mState = state; }
	void SetDirection(Direction direction) { mDirection = direction; }
	void SetHitBox(HitBoxComponent* hb) { mHitBox = hb; }

	//�R���|�[�l���g�̒ǉ��ƍ폜
	void AddComponent(class Component* component);
	void RemoveComponent(class Component* component);

private:
	//�A�N�^�[�̏��
	State mState;
	//�L�����̌���
	Direction mDirection;
	
	//���W�֘A
	Vector2 mPosition; //�A�N�^�[�̒��S�ʒu
	float mScale; //�A�N�^�[�̑傫��(1.0f��100%)
	float mRotation; //��]�̊p�x
	//�����蔻��
	class HitBoxComponent* mHitBox;

	//�A�N�^�[�̎��R���|�[�l���g
	std::vector<class Component*> mComponents;
	class Game* mGame;
};