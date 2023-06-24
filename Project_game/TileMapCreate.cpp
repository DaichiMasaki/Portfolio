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
				renderer, //�����_���[
				mTexture, //�}�b�v�`�b�v
				&TileMapDatas[i][j], //�^�C���̔z�u(�v�f��SDL_Rect)
				&r, //�R�s�[���SDL_Rect
				0, //�摜�̊p�x
				nullptr, //��]�̒��S
				SDL_FLIP_NONE //�㉺���E���]
			);
		}
	}
}

//������̕����p
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
		//���[�h�̎��s�p
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
				//0�ɂ͉����ݒu���Ȃ�
				if (re == 0)
				{
					rec.x = -1 * mTileWidth;
					rec.y = -1 * mTileWidth;
				}
				//����ȊO��������Ή�
				else
				{
					rec.x = static_cast<int>(((re - 1) % 8) * mTileWidth);
					rec.y = static_cast<int>(((re - 1) / 8) * mTileHeight);
				}
				rec.w = mTileWidth;
				rec.h = mTileHeight;

				indata.emplace_back(rec);
			}
			//�f�[�^�����Ă���
			TileMapDatas.emplace_back(indata);
		}
	}
}


