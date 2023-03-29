#pragma once
#include <cstdint>

class Component
{
public:
	//コンストラクタ
	//mUpdateOrderにより更新順序は管理される。
	Component(class Actor* owner, int updateOrder = 100);
	//デストラクタ
	virtual ~Component();
	//このコンポーネントをデルタタイムで更新
	virtual void Update(float deltaTime);
	//キー入力の処理
	virtual void ProcessInput(const uint8_t* keyState) {};
	//mUpdateOrderのゲッター
	int GetUpdateOrder() const { return mUpdateOrder; }

protected:
	//所持しているアクター
	class Actor* mOwner;
	//更新順序
	int mUpdateOrder;
};