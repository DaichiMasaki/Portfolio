#pragma once
#include "SpriteComponent.h"
#include "SDL.h"
#include "Math.h"
#include <vector>
#include <string>


class TileMapCreate : public SpriteComponent
{
public:
	TileMapCreate(class Actor* owner, int picx, int drawOrder = 50);
	//出力
	void Draw(SDL_Renderer* renderer) override;
	//csvから読み込み、Rect形式に変換して適用する処理
	void MakeTileMapData(const std::string& fileName);
	//各種ゲッター及びセッター
	int GetMapWidth()const { return mMapWidth; }
	int GetMapHeight()const { return mMapHeight; }

	void SetMapWidth(int x) { mMapWidth = x; }
	void SetMapHeight(int y) { mMapHeight = y; }
	void SetDatas(std::vector<std::vector<SDL_Rect>> datas) { TileMapDatas = datas; }

private:
	//元画像と出力する画像の幅や高さ
	int mTileWidth;
	int mTileHeight;
	int mMapWidth;
	int mMapHeight;
	std::vector<std::vector<SDL_Rect>> TileMapDatas;
};

inline std::vector<std::string> split(const std::string& str, const char c);