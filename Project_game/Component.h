#pragma once
#include <cstdint>

class Component
{
public:
	//�R���X�g���N�^
	//mUpdateOrder�ɂ��X�V�����͊Ǘ������B
	Component(class Actor* owner, int updateOrder = 100);
	//�f�X�g���N�^
	virtual ~Component();
	//���̃R���|�[�l���g���f���^�^�C���ōX�V
	virtual void Update(float deltaTime);
	//�L�[���͂̏���
	virtual void ProcessInput(const uint8_t* keyState) {};
	//mUpdateOrder�̃Q�b�^�[
	int GetUpdateOrder() const { return mUpdateOrder; }

protected:
	//�������Ă���A�N�^�[
	class Actor* mOwner;
	//�X�V����
	int mUpdateOrder;
};