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
	//SDLライブラリの初期化
	int sdlResult = SDL_Init(SDL_INIT_VIDEO);
	//初期化できたかチェック(0なら大丈夫)
	if (sdlResult != 0)
	{
		SDL_Log("SDL cannot initialize : %s", SDL_GetError());
		return false;
	}

	//SDL_Createでウィンドウの作成
	mWindow = SDL_CreateWindow("Project_game", 100, 100, 1024, 768, SDL_WINDOW_FULLSCREEN);
	//ウィンドウの作成に成功したかチェック
	if (!mWindow)
	{
		SDL_Log("failed to create window : %s", SDL_GetError());
	}

	//レンダラーの作成
	mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	//レンダラー作製に成功したかチェック
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
	//SDL_DestroyWindowによりウィンドウを消す
	SDL_DestroyWindow(mWindow);
	//SDL_DestroyRendererによりウィンドウを消す
	SDL_DestroyRenderer(mRenderer);
	SDL_Quit();
}

void Game::AddActor(Actor* actor)
{
	//アクターが更新中ならば待ち状態に追加
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
	//保留中のアクターの中にあるかどうか
	auto iter = std::find(mPendingActors.begin(), mPendingActors.end(), actor);
	if (iter != mPendingActors.end())
	{
		//最後と入れ替えて削除
		std::iter_swap(iter, mPendingActors.end() - 1);
		mPendingActors.pop_back();
	}

	//アクターの中にあるかどうか
	iter = std::find(mActors.begin(), mActors.end(), actor);
	if (iter != mActors.end())
	{
		//最後と入れ替えて削除
		std::iter_swap(iter, mActors.end() - 1);
		mActors.pop_back();
	}
}

void Game::AddSprite(SpriteComponent* sprite)
{
	//ソート済みの配列でmDrawOrder()順になるように挿入
	int myDrawOrder = sprite->GetDrawOrder();
	auto iter = mSprites.begin();
	for (; iter != mSprites.end(); ++iter)
	{
		if (myDrawOrder < (*iter)->GetDrawOrder())
		{
			break;
		}
	}

	//イテレータの直前に要素を挿入
	mSprites.insert(iter, sprite);
}

void Game::RemoveSprite(SpriteComponent* sprite)
{
	//オーダーを破滅させないためにswapはしない
	auto iter = std::find(mSprites.begin(), mSprites.end(), sprite);
	mSprites.erase(iter);
}

SDL_Texture* Game::GetTexture(const std::string& fileName)
{
	SDL_Texture* tex = nullptr;
	//マップの中にすでにこのテクスチャがあるか
	auto iter = mTextures.find(fileName);
	if (iter != mTextures.end())
	{
		tex = iter->second;
	}
	else
	{
		//なければファイルから読み込み
		SDL_Surface* surf = IMG_Load(fileName.c_str());
		if (!surf)
		{
			SDL_Log("Failed to load texture file %s", fileName.c_str());
			return nullptr;
		}

		//サーフェイスからテクスチャを作る
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
	//キューの中にイベントがあれば実行
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			//各種イベントの処理
		case SDL_QUIT:
			mIsRunning = false;
		}
	}
	//キーボードの状態を取得
	const Uint8* keystate = SDL_GetKeyboardState(NULL);
	//ESCキーが押されるとループ終了
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
	//最低でも16ms待たせる
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16));

	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
	//デルタタイムの制限(最大値)
	if (deltaTime > 0.05f)
	{
		deltaTime = 0.05f;
	}
	//時刻の更新
	mTicksCount = SDL_GetTicks();

	//すべてのアクターの更新
	mUpdatingActors = true;
	for (auto actor : mActors)
	{
		actor->Update(deltaTime);
	}
	mUpdatingActors = false;

	//待ち状態のアクターをmActorsに移動
	for (auto pending : mPendingActors)
	{
		mActors.emplace_back(pending);
	}
	mPendingActors.clear();

	//死んだアクターを一時配列に追加
	std::vector<Actor*> deadActors;

	for (auto actor : mActors)
	{
		if (actor->GetState() == Actor::State::EDead)
		{
			deadActors.emplace_back(actor);
		}
	}

	//死んだアクターを消す
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
	//レンダーの塗りつぶし
	SDL_RenderClear(mRenderer);

	//すべてのスプライトを描くよ
	for (auto sprite : mSprites)
	{
		sprite->Draw(mRenderer);
	}


	//最後にフロントバッファとバックバッファを交換
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
	//アクターを消すが、アクターのデストラクタはRemoveActorを呼び出すため違う形でループ処理をする。
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