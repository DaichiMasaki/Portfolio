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
	//�o��
	void Draw(SDL_Renderer* renderer) override;
	//csv����ǂݍ��݁ARect�`���ɕϊ����ēK�p���鏈��
	void MakeTileMapData(const std::string& fileName);
	//�e��Q�b�^�[�y�уZ�b�^�[
	int GetMapWidth()const { return mMapWidth; }
	int GetMapHeight()const { return mMapHeight; }

	void SetMapWidth(int x) { mMapWidth = x; }
	void SetMapHeight(int y) { mMapHeight = y; }
	void SetDatas(std::vector<std::vector<SDL_Rect>> datas) { TileMapDatas = datas; }

private:
	//���摜�Əo�͂���摜�̕��⍂��
	int mTileWidth;
	int mTileHeight;
	int mMapWidth;
	int mMapHeight;
	std::vector<std::vector<SDL_Rect>> TileMapDatas;
};

inline std::vector<std::string> split(const std::string& str, const char c);