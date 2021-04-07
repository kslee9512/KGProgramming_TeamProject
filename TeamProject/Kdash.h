#pragma once
#include "Character.h"

class Kdash : public Character
{
public:
	HRESULT Init();
	HRESULT Init(PPOS pPos);
	void Render(HDC hdc);
	//void Update();
};

