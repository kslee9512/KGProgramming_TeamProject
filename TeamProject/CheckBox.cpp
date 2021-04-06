#include "CheckBox.h"
#include "CommonFunction.h"

HRESULT CheckBox::Init()
{
	return Init(FPOINT{ 0, 0}, 0 , 0);
}

HRESULT CheckBox::Init(FPOINT pos, int width, int height)
{
	pos = pos; // 박스의 중심좌표
	this->width = width;
	this->height = height;
	rect = GetRectToCenter(pos.x, pos.y, width, height);
	isActivated = false;

	return S_OK;
}

void CheckBox::Release()
{

}

void CheckBox::Update() {
	Update(pos);
}

void CheckBox::Update(FPOINT pos)
{
	rect.left = pos.x - width / 2;
	rect.right = pos.x + width / 2;
	rect.top = pos.y - height / 2;
	rect.bottom = pos.y + height / 2;
}

void CheckBox::Update(PPOS pPos, STATUS status)
{
	if (pPos == PPOS::P1) {
		rect.left = pos.x - width / 2;
		rect.right = pos.x + width / 2 + status * 30;
		rect.top = pos.y - height / 2;
		rect.bottom = pos.y + height / 2;
	}
	else {
		rect.left = pos.x - width / 2 - status * 30;
		rect.right = pos.x + width / 2;
		rect.top = pos.y - height / 2;
		rect.bottom = pos.y + height / 2;
	}
}

void CheckBox::Render(HDC hdc)
{
	HPEN hPen = CreatePen(PS_SOLID, 5, RGB(255, 255, 255));
	HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);
	
	MoveToEx(hdc, rect.left, rect.top, NULL);
	LineTo(hdc, rect.right, rect.top);
	LineTo(hdc, rect.right, rect.bottom);
	LineTo(hdc, rect.left, rect.bottom);
	LineTo(hdc, rect.left, rect.top);

	SelectObject(hdc, hOldPen);
	DeleteObject(hPen);
}
