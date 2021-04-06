#pragma once
#include "Character.h"

class Ash :public Character
{
public:
	HRESULT Init();
	HRESULT Init(PPOS pPos);
	void Update();
	void Render(HDC hdc);
};