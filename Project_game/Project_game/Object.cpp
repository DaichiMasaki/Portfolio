#include "Object.h"
#include "Crate.h"
#include "Game.h"
#include "HitBoxComponent.h"
#include "TileMapCreate.h"
#include <fstream>
#include <sstream>

Object::Object(Game* game)
	:Actor(game)
	,mWeight(1)
{
	//当たり判定
	HitBoxComponent* hb = new HitBoxComponent(this);
	hb->Sethalfx(32);
	hb->Sethalfy(32);
	hb->SetShifty(32);
	SetHitBox(hb);
}

Object::~Object()
{
	GetGame()->RemoveObject(this);
}

void ObjectCreate(class Game* game, const std::string& fileName)
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
				//1にはクレートを置く(何も置かないところには0を入れてある)
				if (re == 1)
				{
					Crate* crate = new Crate(game);
					Vector2 position(crate->GetHitBox()->Gethalfx() * (2 * count2 + 1), crate->GetHitBox()->Gethalfy() * (2 * count1 + 1)-32);
					crate->SetPosition(position);
					game->AddObject(crate);
				}
				count2++;

			}
			count1++;
		}
	}
}