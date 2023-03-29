#include "Wall.h"
#include "Game.h"
#include "Actor.h"
#include "HitBoxComponent.h"
#include "TileMapCreate.h"
#include "Math.h"
#include <fstream>
#include <sstream>

Wall::Wall(class Game* game, const int& x, const int& y)
	:Actor(game)
{
	HitBoxComponent* hb = new HitBoxComponent(this);
	hb->Sethalfx(x);
	hb->Sethalfy(y);
	SetHitBox(hb);
}

void WallCreate(Game* game, const std::string& fileName)
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
				//0以外に設置
				if (re != 0)
				{
					Wall* wall = new Wall(game);
					Vector2 position(wall->GetHitBox()->Gethalfx() * (2 * count2 + 1), wall->GetHitBox()->Gethalfy() * (2 * count1 + 1));
					wall->SetPosition(position);
					game->AddWall(wall);
				}
				count2++;

			}
			count1++;
		}
	}
}