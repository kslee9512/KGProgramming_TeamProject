#pragma once
#include "Character.h"
class Ash :public Character
{
public:
	void Update();
	HRESULT Init(PPOS pPos);
	HRESULT Init();
};

