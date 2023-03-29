#include "Crate.h"
#include "PushComponent.h"
#include "SpriteComponent.h"
#include "Game.h"

Crate::Crate(Game* game)
	:Object(game)
	,mItem(0)
{
	//�`�悷��X�v���C�g
	SpriteComponent* sc = new SpriteComponent(this);
	sc->SetTexture(game->GetTexture("Assets/Objects.png"));
	sc->SetTexWidth(32);
	sc->SetTexHeight(64);
	sc->SetTexx(0);
	sc->SetTexy(0);
}