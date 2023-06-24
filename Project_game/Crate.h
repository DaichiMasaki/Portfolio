#pragma once
#include "Object.h"


class Crate : public Object
{
public:
	Crate(class Game* game);

	int GetItem() { return mItem; }
	void SetItem(int item) { mItem = item; }

private:
	int mItem;
};

