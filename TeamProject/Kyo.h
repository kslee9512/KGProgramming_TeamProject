#pragma once
#include "Character.h"

class Kyo : public Character
{
public:
	HRESULT Init();
	HRESULT Init(PPOS pPos);
	void Update();
	void Move();
	void Render(HDC hdc);
};

