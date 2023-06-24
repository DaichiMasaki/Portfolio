#pragma once

#include "SDL.h"
#include <string>
#include <vector>
#include <unordered_map>

class Game
{
public:
	Game();
	//�Q�[���̏�����
	bool Initialize();
	//�Q�[���I�[�o�[�܂ł̃Q�[�����[�v
	void RunLoop();
	//�Q�[���̃V���b�g�_�E��
	void Shutdown();

	//�A�N�^�[�̒ǉ�
	void AddActor(class Actor* actor);
	//�A�N�^�[�̍폜
	void RemoveActor(class Actor* actor);

	//�X�v���C�g�̒ǉ�
	void AddSprite(class SpriteComponent* sprite);
	void RemoveSprite(class SpriteComponent* sprite);
	//�e�N�X�`���̎擾
	SDL_Texture* GetTexture(const std::string& fileName);

	//�ǂ̓����蔻��̒ǉ�
	void AddWall(class Wall* wall);
	//�ǂ̃��X�g�̃Q�b�^�[
	std::vector<class Wall*> GetWalls() const { return mWalls; }

	//�I�u�W�F�N�g�̒ǉ�
	void AddObject(class Object* object);
	//�I�u�W�F�N�g�̍폜
	void RemoveObject(class Object* object);
	//�N���[�g�̃��X�g�̃Q�b�^�[
	std::vector<class Object*> GetObjects() const { return mObjects; }

	//�N���X�^���X�C�b�`�̒ǉ�
	void AddCrystal(class Crystal* object);
	//�N���X�^���X�C�b�`�̃��X�g�̃Q�b�^�[
	std::vector<class Crystal*>GetCrystal() const { return mCrystals; }

	//�N���X�^���ɑΉ������u���b�N�̒ǉ�
	void AddVBlock(class VanishBlock* block);
	void AddRevVBlock(class RevVanishBlock* block);
	//�N���X�^���ɑΉ������u���b�N�̃Q�b�^�[
	std::vector<class VanishBlock*>GetVBlocks() const { return mVBlocks; }
	std::vector<class RevVanishBlock*>GetRevVBlocks() const { return mRevVBlocks; }

	//�v���C���[�̃Q�b�^�[
	class Player* GetPlayer()const { return mPlayer; }

private:
	//�Q�[�����[�v�̂��߂̃w���p�[�֐��Q
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();
	void LoadData();
	void UnloadData();
	
	//�ǂݍ��ݍς݂̃e�N�X�`���Q
	std::unordered_map<std::string, SDL_Texture*> mTextures;
	//�A�N�V�u�ȃA�N�^�[�Q
	std::vector<class Actor*> mActors;
	//�҂���Ԃ̃A�N�^�[�Q
	std::vector<class Actor*> mPendingActors;
	//�`�悳���X�v���C�g�Q
	std::vector<class SpriteComponent*> mSprites;


	//SDL�����E�B���h�E�̃|�C���^
	SDL_Window* mWindow;
	//2D�`��̂��߂̃����_���[�̃|�C���^
	SDL_Renderer* mRenderer;
	//�f���^�^�C���g�p�̂��߂̐錾(�f���^�^�C���͑O�t���[������̌o�ߎ��Ԃ�b�ɒ���������)
	Uint32 mTicksCount;
	//�Q�[�����s�̎w��
	bool mIsRunning;
	//mActors���X�V�����ǂ���
	bool mUpdatingActors;

	//���ׂȂǂ̓����蔻��
	std::vector<class Wall*> mWalls;
	//�N���[�g
	std::vector<class Object*> mObjects;
	//�N���X�^���X�C�b�`
	std::vector<class Crystal*> mCrystals;
	//�N���X�^�������ׂăI���̎��Ɍ����u���b�N
	std::vector<class VanishBlock*> mVBlocks;
	//�N���X�^���Ɉ�ł��I�t������ꍇ�o��u���b�N
	std::vector<class RevVanishBlock*> mRevVBlocks;

	//�v���C���[
	class Player* mPlayer;
};