
#include "Character.h"
#include "Image.h"

HRESULT Character::Init(PPOS pPos)
{
	this->pPos = pPos;
	image = new Image[12];
	frameX = 0;
	frameY = 0;
	status = STATUS::STANCE;
	if (pPos == PPOS::P1)
	{
		pos.x = (WINSIZE_X / 2) - 300;
		pos.y = (GROUND_Y);
	}
	else if (pPos == PPOS::P2)
	{
		pos.x = (WINSIZE_X / 2) + 300;
		pos.y = (GROUND_Y);
	}

	if (FAILED(image[0].Init("Image/K'Image/k'_stance1p.bmp", 1344, 122, 16, 1, PPOS::P1, true, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, "Image/Iori_walk.bmp 로드 실패", "Warning", MB_OK);
		return E_FAIL;
	}
	return S_OK;
}

void Character::Release()
{
	if (image)
	{
		for (int i = 0; i < 11; i++)
		{
			image[i].Release();
		}
		delete[] image;
		image = nullptr;
	}
}

void Character::Update()
{
	elapsedTime++;
	if (elapsedTime >= 5 && status == STATUS::STANCE)
	{
		frameX++;
		if (frameX >= 16)
		{
			frameX = 0;
		}
		elapsedTime = 0;
	}
	else if (elapsedTime >= 5 && status == STATUS::WALK)
	{
		//앞으로 이동 시 이미지 출력되도록 UPDATE 작성
	}
	else if (elapsedTime >= 5 && status == STATUS::BACK)
	{
		// 뒤로 이동 시 이미지 출력되도록 UDPATER 작성
	}
	if (pPos == PPOS::P1)
	{
		if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LEFT))
		{
			SetStatus(STATUS::BACK);
		}
		else if (KeyManager::GetSingleton()->IsStayKeyDown(VK_RIGHT))
		{
			SetStatus(STATUS::WALK);
		}
		else
		{
			SetStatus(STATUS::STANCE);
		}
	}
	else if (pPos == PPOS::P2)
	{
		if (KeyManager::GetSingleton()->IsStayKeyDown(VK_RIGHT))
		{
			SetStatus(STATUS::BACK);
		}
		else if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LEFT))
		{
			SetStatus(STATUS::WALK);
		}
		else
		{
			SetStatus(STATUS::STANCE);
		}
	}
}

void Character::Render(HDC hdc)
{
	if (image) {
		if (status == STATUS::SKILL)
		{
			if (pPos == PPOS::P1)
				image[status].RenderReverse(hdc, pos.x, pos.y, 679, 689);
			else if (pPos == PPOS::P2)
				image[status].Render(hdc, pos.x, pos.y, 679, 689);

		}
		else {
			if (pPos == PPOS::P1)
				image[status].RenderReverse(hdc, pos.x, pos.y, 679, 689);
			else if (pPos == PPOS::P2)
				image[status].Render(hdc, pos.x, pos.y, 679, 689);
		}
	}
}

void Character::Move()
{
	if (pPos == PPOS::P1 && status == STATUS::WALK)
	{
		this->pos.x += moveSpeed;
	}
	else if (pPos == PPOS::P1 && status == STATUS::BACK)
	{
		this->pos.x -= moveSpeed;
	}
	else if (pPos == PPOS::P2 && status == STATUS::WALK)
	{
		this->pos.x -= moveSpeed;
	}
	else if (pPos == PPOS::P2 && status == STATUS::BACK)
	{
		this->pos.x += moveSpeed;
	}
}

void Character::Attack(STATUS status)
{

}