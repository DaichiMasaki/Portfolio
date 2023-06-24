#include "Crystal.h"
#include "VanishBlock.h"
#include "RevVanishBlock.h"
#include "HitBoxComponent.h"
#include "SpriteComponent.h"
#include "Game.h"
#include "TileMapCreate.h"
#include <fstream>
#include <sstream>

Crystal::Crystal(Game* game)
	:Actor(game)
	, mOn(false)
{
	//描画するスプライト
	mSprite = new SpriteComponent(this);
	mSprite->SetTexture(game->GetTexture("Assets/Crystal.png"));
	mSprite->SetTexWidth(32);
	mSprite->SetTexHeight(32);
	mSprite->SetTexx(0);
	mSprite->SetTexy(0);

	//当たり判定
	HitBoxComponent* hb = new HitBoxComponent(this);
	hb->Sethalfx(20);
	hb->Sethalfy(20);
	SetHitBox(hb);
}

void Crystal::UpdateActor(float deltaTime)
{

}

void CrystalCreate(class Game* game, const std::string& fileName)
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
				//1にはクリスタルを置く(何も置かないところには0を入れてある)
				if (re == 1)
				{
					Crystal* crystal = new Crystal(game);
					Vector2 position(32 * (2 * count2 + 1), 32 * (2 * count1 + 1));
					crystal->SetPosition(position);
					game->AddCrystal(crystal);
				}
				//2にはVanishBlockを置く
				else if (re == 2)
				{
					VanishBlock* vblock = new VanishBlock(game);
					Vector2 position(32 * (2 * count2 + 1), vblock->GetHitBox()->Gethalfy() * (2 * count1 + 1) - 32);
					vblock->SetPosition(position);
					game->AddVBlock(vblock);
				}
				//3にはRevVanishBlockを置く
				else if (re == 3)
				{
					RevVanishBlock* rvblock = new RevVanishBlock(game);
					Vector2 position(rvblock->GetHitBox()->Gethalfx() * (2 * count2 + 1), rvblock->GetHitBox()->Gethalfy() * (2 * count1 + 1) - 32);
					rvblock->SetPosition(position);
					game->AddRevVBlock(rvblock);
				}
				count2++;

			}
			count1++;
		}
	}
}