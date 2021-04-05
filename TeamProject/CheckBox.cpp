#include "CheckBox.h"

HRESULT CheckBox::Init()
{
	pos.x = 0;
	pos.y = 0;
	radius = 0;
	isActivated = false;
	return S_OK;
}

void CheckBox::Release()
{

}

void CheckBox::Update()
{
	isActivated = !isActivated;
}

void CheckBox::Render(HDC hdc)
{
	Ellipse(hdc, pos.x - radius, pos.y - radius, pos.x + radius, pos.y + radius);
}
