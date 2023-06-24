#include "WallCreate.h"
#include "Wall.h"
#include "Game.h"
#include "Actor.h"
#include "HitBoxComponent.h"
#include "TileMapCreate.h"
#include "Math.h"
#include <fstream>
#include <sstream>

WallCreate::WallCreate(Game* game)
	:Actor(game)
	, mWall(nullptr)
{

}

void WallCreate::MakeWallData(const std::string& fileName, const int& x, const int& y)
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
		int count1 = 0;
		while (std::getline(ifs, line))
		{
			int count2 = 0;
			std::vector<std::string> strdata = split(line, ',');
			for (auto&& s : strdata)
			{
				int re = std::stoi(s);
				//-1以外に設置
				if (re != -1)
				{
					mWall = new Wall()
				}
				count2++;

			}
			count1++;
		}
	}
}