#include "Game.h"
#include "Actor.h"
#include "SpriteComponent.h"
#include "TileMapCreate.h"
#include "Player.h"
#include "Wall.h"
#include "Crate.h"
#include "Crystal.h"
#include "VanishBlock.h"
#include "RevVanishBlock.h"
#include "SDL.h"
#include "SDL_image.h"
#include <algorithm>
#include <vector>

Game::Game()
	:mWindow(nullptr)
	,mRenderer(nullptr)
	,mPlayer(nullptr)
	,mIsRunning(true)
{

}

bool Game::Initialize()
{
	//SDL���C�u�����̏�����
	int sdlResult = SDL_Init(SDL_INIT_VIDEO);
	//�������ł������`�F�b�N(0�Ȃ���v)
	if (sdlResult != 0)
	{
		SDL_Log("SDL cannot initialize : %s", SDL_GetError());
		return false;
	}

	//SDL_Create�ŃE�B���h�E�̍쐬
	mWindow = SDL_CreateWindow("Project_game", 100, 100, 1024, 768, SDL_WINDOW_FULLSCREEN);
	//�E�B���h�E�̍쐬�ɐ����������`�F�b�N
	if (!mWindow)
	{
		SDL_Log("failed to create window : %s", SDL_GetError());
	}

	//�����_���[�̍쐬
	mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	//�����_���[�쐻�ɐ����������`�F�b�N
	if (!mRenderer)
	{
		SDL_Log("failed to create renderer : %s", SDL_GetError());
		return false;
	}

	LoadData();

	mTicksCount = SDL_GetTicks();

	return true;
}

void Game::RunLoop()
{
	while (mIsRunning)
	{
		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}
}

void Game::Shutdown()
{
	UnloadData();
	IMG_Quit();
	//SDL_DestroyWindow�ɂ��E�B���h�E������
	SDL_DestroyWindow(mWindow);
	//SDL_DestroyRenderer�ɂ��E�B���h�E������
	SDL_DestroyRenderer(mRenderer);
	SDL_Quit();
}

void Game::AddActor(Actor* actor)
{
	//�A�N�^�[���X�V���Ȃ�Α҂���Ԃɒǉ�
	if (mUpdatingActors)
	{
		mPendingActors.emplace_back(actor);
	}
	else
	{
		mActors.emplace_back(actor);
	}
}

void Game::RemoveActor(Actor* actor)
{
	//�ۗ����̃A�N�^�[�̒��ɂ��邩�ǂ���
	auto iter = std::find(mPendingActors.begin(), mPendingActors.end(), actor);
	if (iter != mPendingActors.end())
	{
		//�Ō�Ɠ���ւ��č폜
		std::iter_swap(iter, mPendingActors.end() - 1);
		mPendingActors.pop_back();
	}

	//�A�N�^�[�̒��ɂ��邩�ǂ���
	iter = std::find(mActors.begin(), mActors.end(), actor);
	if (iter != mActors.end())
	{
		//�Ō�Ɠ���ւ��č폜
		std::iter_swap(iter, mActors.end() - 1);
		mActors.pop_back();
	}
}

void Game::AddSprite(SpriteComponent* sprite)
{
	//�\�[�g�ς݂̔z���mDrawOrder()���ɂȂ�悤�ɑ}��
	int myDrawOrder = sprite->GetDrawOrder();
	auto iter = mSprites.begin();
	for (; iter != mSprites.end(); ++iter)
	{
		if (myDrawOrder < (*iter)->GetDrawOrder())
		{
			break;
		}
	}

	//�C�e���[�^�̒��O�ɗv�f��}��
	mSprites.insert(iter, sprite);
}

void Game::RemoveSprite(SpriteComponent* sprite)
{
	//�I�[�_�[��j�ł����Ȃ����߂�swap�͂��Ȃ�
	auto iter = std::find(mSprites.begin(), mSprites.end(), sprite);
	mSprites.erase(iter);
}

SDL_Texture* Game::GetTexture(const std::string& fileName)
{
	SDL_Texture* tex = nullptr;
	//�}�b�v�̒��ɂ��łɂ��̃e�N�X�`�������邩
	auto iter = mTextures.find(fileName);
	if (iter != mTextures.end())
	{
		tex = iter->second;
	}
	else
	{
		//�Ȃ���΃t�@�C������ǂݍ���
		SDL_Surface* surf = IMG_Load(fileName.c_str());
		if (!surf)
		{
			SDL_Log("Failed to load texture file %s", fileName.c_str());
			return nullptr;
		}

		//�T�[�t�F�C�X����e�N�X�`�������
		tex = SDL_CreateTextureFromSurface(mRenderer, surf);
		SDL_FreeSurface(surf);
		if (!tex)
		{
			SDL_Log("Failed to convert surface to texture for %s", fileName.c_str());
			return nullptr;
		}

		mTextures.emplace(fileName.c_str(), tex);
	}
	return tex;
}

void Game::AddWall(Wall* wall)
{
	mWalls.emplace_back(wall);
}

void Game::AddObject(Object* object)
{
	mObjects.emplace_back(object);
}

void Game::RemoveObject(Object* object)
{
	auto iter = std::find(mObjects.begin(), mObjects.end(), object);
	if (iter != mObjects.end())
	{
		mObjects.erase(iter);
	}
}

void Game::AddCrystal(Crystal* crystal)
{
	mCrystals.emplace_back(crystal);
}

void Game::AddVBlock(VanishBlock* block)
{
	mVBlocks.emplace_back(block);
}

void Game::AddRevVBlock(RevVanishBlock* block)
{
	mRevVBlocks.emplace_back(block);
}

void Game::ProcessInput()
{
	SDL_Event event;
	//�L���[�̒��ɃC�x���g������Ύ��s
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			//�e��C�x���g�̏���
		case SDL_QUIT:
			mIsRunning = false;
		}
	}
	//�L�[�{�[�h�̏�Ԃ��擾
	const Uint8* keystate = SDL_GetKeyboardState(NULL);
	//ESC�L�[���������ƃ��[�v�I��
	if (keystate[SDL_SCANCODE_ESCAPE])
	{
		mIsRunning = false;
	}

	mUpdatingActors = true;
	for (auto actor : mActors)
	{
		actor->ProcessInput(keystate);
	}
	mUpdatingActors = false;
}

void Game::UpdateGame()
{
	//�Œ�ł�16ms�҂�����
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16));

	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
	//�f���^�^�C���̐���(�ő�l)
	if (deltaTime > 0.05f)
	{
		deltaTime = 0.05f;
	}
	//�����̍X�V
	mTicksCount = SDL_GetTicks();

	//���ׂẴA�N�^�[�̍X�V
	mUpdatingActors = true;
	for (auto actor : mActors)
	{
		actor->Update(deltaTime);
	}
	mUpdatingActors = false;

	//�҂���Ԃ̃A�N�^�[��mActors�Ɉړ�
	for (auto pending : mPendingActors)
	{
		mActors.emplace_back(pending);
	}
	mPendingActors.clear();

	//���񂾃A�N�^�[���ꎞ�z��ɒǉ�
	std::vector<Actor*> deadActors;

	for (auto actor : mActors)
	{
		if (actor->GetState() == Actor::State::EDead)
		{
			deadActors.emplace_back(actor);
		}
	}

	//���񂾃A�N�^�[������
	for (auto actor : deadActors)
	{
		delete actor;
	}
}

void Game::GenerateOutput()
{
	SDL_SetRenderDrawColor(
		mRenderer,
		100,//R
		200,//G
		100,//B
		0 //A
	);
	//�����_�[�̓h��Ԃ�
	SDL_RenderClear(mRenderer);

	//���ׂẴX�v���C�g��`����
	for (auto sprite : mSprites)
	{
		sprite->Draw(mRenderer);
	}


	//�Ō�Ƀt�����g�o�b�t�@�ƃo�b�N�o�b�t�@������
	SDL_RenderPresent(mRenderer);
}

void Game::LoadData()
{
	Actor* temp = new Actor(this);
	temp->SetPosition(Vector2::Zero);
	TileMapCreate* tc = new TileMapCreate(temp, 32, 50);
	SDL_Texture* pic = GetTexture("Assets/Tilemap1.png");
	tc->SetTexture(pic);
	tc->MakeTileMapData("Assets/Map1.csv");

	WallCreate(this, "Assets/Map1.csv");

	ObjectCreate(this, "Assets/Objects.csv");

	CrystalCreate(this, "Assets/Crystals.csv");

	mPlayer = new Player(this);
	mPlayer->SetPosition(Vector2(512.0f, 384.0f));
}

void Game::UnloadData()
{
	//�A�N�^�[���������A�A�N�^�[�̃f�X�g���N�^��RemoveActor���Ăяo�����߈Ⴄ�`�Ń��[�v����������B
	while (!mActors.empty())
	{
		delete mActors.back();
	}

	// Destroy textures
	for (auto i : mTextures)
	{
		SDL_DestroyTexture(i.second);
	}
	mTextures.clear();
}