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

	//コンストラクタとデストラクタ
	Actor(class Game* game);
	virtual ~Actor();

	//ゲームから呼び出される更新関数(オーバーライド不可)
	void Update(float deltaTime);
	//アクターが持つ全コンポーネントを更新(オーバーライド不可)
	void UpdateComponents(float deltaTime);
	//アクター独自の更新処理(オーバーライド可)
	virtual void UpdateActor(float deltaTime);
	//キー入力受付(ゲームから呼ばれる)
	void ProcessInput(const uint8_t* keyState);
	//アクターごとのキー入力受付(オーバーライド可)
	virtual void ActorInput(const uint8_t* keyState);

	//ゲッターとセッター
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

	//コンポーネントの追加と削除
	void AddComponent(class Component* component);
	void RemoveComponent(class Component* component);

private:
	//アクターの状態
	State mState;
	//キャラの向き
	Direction mDirection;
	
	//座標関連
	Vector2 mPosition; //アクターの中心位置
	float mScale; //アクターの大きさ(1.0fで100%)
	float mRotation; //回転の角度
	//当たり判定
	class HitBoxComponent* mHitBox;

	//アクターの持つコンポーネント
	std::vector<class Component*> mComponents;
	class Game* mGame;
};