#pragma once

#include "SDL.h"
#include <string>
#include <vector>
#include <unordered_map>

class Game
{
public:
	Game();
	//ゲームの初期化
	bool Initialize();
	//ゲームオーバーまでのゲームループ
	void RunLoop();
	//ゲームのシャットダウン
	void Shutdown();

	//アクターの追加
	void AddActor(class Actor* actor);
	//アクターの削除
	void RemoveActor(class Actor* actor);

	//スプライトの追加
	void AddSprite(class SpriteComponent* sprite);
	void RemoveSprite(class SpriteComponent* sprite);
	//テクスチャの取得
	SDL_Texture* GetTexture(const std::string& fileName);

	//壁の当たり判定の追加
	void AddWall(class Wall* wall);
	//壁のリストのゲッター
	std::vector<class Wall*> GetWalls() const { return mWalls; }

	//オブジェクトの追加
	void AddObject(class Object* object);
	//オブジェクトの削除
	void RemoveObject(class Object* object);
	//クレートのリストのゲッター
	std::vector<class Object*> GetObjects() const { return mObjects; }

	//クリスタルスイッチの追加
	void AddCrystal(class Crystal* object);
	//クリスタルスイッチのリストのゲッター
	std::vector<class Crystal*>GetCrystal() const { return mCrystals; }

	//クリスタルに対応したブロックの追加
	void AddVBlock(class VanishBlock* block);
	void AddRevVBlock(class RevVanishBlock* block);
	//クリスタルに対応したブロックのゲッター
	std::vector<class VanishBlock*>GetVBlocks() const { return mVBlocks; }
	std::vector<class RevVanishBlock*>GetRevVBlocks() const { return mRevVBlocks; }

	//プレイヤーのゲッター
	class Player* GetPlayer()const { return mPlayer; }

private:
	//ゲームループのためのヘルパー関数群
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();
	void LoadData();
	void UnloadData();
	
	//読み込み済みのテクスチャ群
	std::unordered_map<std::string, SDL_Texture*> mTextures;
	//アクシブなアクター群
	std::vector<class Actor*> mActors;
	//待ち状態のアクター群
	std::vector<class Actor*> mPendingActors;
	//描画されるスプライト群
	std::vector<class SpriteComponent*> mSprites;


	//SDLが作るウィンドウのポインタ
	SDL_Window* mWindow;
	//2D描画のためのレンダラーのポインタ
	SDL_Renderer* mRenderer;
	//デルタタイム使用のための宣言(デルタタイムは前フレームからの経過時間を秒に直したもの)
	Uint32 mTicksCount;
	//ゲーム続行の指示
	bool mIsRunning;
	//mActorsが更新中かどうか
	bool mUpdatingActors;

	//かべなどの当たり判定
	std::vector<class Wall*> mWalls;
	//クレート
	std::vector<class Object*> mObjects;
	//クリスタルスイッチ
	std::vector<class Crystal*> mCrystals;
	//クリスタルがすべてオンの時に現れるブロック
	std::vector<class VanishBlock*> mVBlocks;
	//クリスタルに一つでもオフがある場合出るブロック
	std::vector<class RevVanishBlock*> mRevVBlocks;

	//プレイヤー
	class Player* mPlayer;
};