#include "TileMapCreate.h"
#include <fstream>
#include <sstream>

TileMapCreate::TileMapCreate(class Actor* owner, int picx, int drawOrder)
	:SpriteComponent(owner, drawOrder)
	, mTileWidth(picx)
	, mTileHeight(picx)
	, mMapWidth(picx*2)
	, mMapHeight(picx*2)
{

}


void TileMapCreate::Draw(SDL_Renderer* renderer)
{
	SDL_Rect r;
	//
	for (int i = 0; i < TileMapDatas.size(); i++)
	{
		for (int j = 0; j < TileMapDatas[i].size(); j++)
		{
			r.w = mMapWidth;
			r.h = mMapHeight;

			r.x = j * mMapWidth;
			r.y = i * mMapHeight;

			SDL_RenderCopyEx(
				renderer, //レンダラー
				mTexture, //マップチップ
				&TileMapDatas[i][j], //タイルの配置(要素はSDL_Rect)
				&r, //コピー先のSDL_Rect
				0, //画像の角度
				nullptr, //回転の中心
				SDL_FLIP_NONE //上下左右反転
			);
		}
	}
}

//文字列の分割用
inline std::vector<std::string> split(const std::string& str, const char c)
{
	std::vector < std::string > restr;
	std::stringstream ss(str);
	std::string item;
	while (std::getline(ss, item, c))
	{
		if (!item.empty())
		{
			restr.push_back(item);
		}
	}

	return restr;
}

void TileMapCreate::MakeTileMapData(const std::string& fileName)
{
	std::ifstream ifs(fileName);
	if (!ifs)
	{
		//ロードの失敗用
		SDL_Log("Failed to load CSV file %s", fileName.c_str());
	}
	else
	{
		std::string line;
		while (std::getline(ifs, line))
		{
			std::vector<SDL_Rect> indata;
			std::vector<std::string> strdata = split(line, ',');
			for (auto&& s : strdata)
			{
				SDL_Rect rec;
				int re = std::stoi(s);
				//0には何も設置しない
				if (re == 0)
				{
					rec.x = -1 * mTileWidth;
					rec.y = -1 * mTileWidth;
				}
				//それ以外が来たら対応
				else
				{
					rec.x = static_cast<int>(((re - 1) % 8) * mTileWidth);
					rec.y = static_cast<int>(((re - 1) / 8) * mTileHeight);
				}
				rec.w = mTileWidth;
				rec.h = mTileHeight;

				indata.emplace_back(rec);
			}
			//データを入れていく
			TileMapDatas.emplace_back(indata);
		}
	}
}


