#include "Character.h"
#include "Image.h"

HRESULT Character::Init(PPOS pPos)
{
	this->pPos = pPos;
	image = new Image[12];
	frame = 0;
	maxFrame[12];
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

	if (FAILED(image[0].Init("Image/Ash_Image/stance.bmp", 801, 124, 9, 1, true, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, "Image/stance.bmp 로드 실패", "Warning", MB_OK);
		return E_FAIL;
	}
	return S_OK;
}

void Character::Release()
{
	if (image)
	{
		for (int i = 0; i < 12; i++)
		{
			image[i].Release();
		}
		delete[] image;
		image = nullptr;
	}
}

void Character::Update(STATUS status)
{
	elapsedTime++;
	if (elapsedTime >= 5 && status == STATUS::STANCE)
	{
		frame++;
		if (frame >= maxFrame[0])
		{
			frame = 0;
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
	if (image)
	{
		if (status == STATUS::STANCE)
		{
			image[0].Render(hdc, pos.x, pos.y, imageWidth / maxFrame[0],683, imageWidth / maxFrame[0],0, imageWidth / maxFrame[0],683, frame);
		}
		if (status == STATUS::WALK)
		{
			image[1].Render(hdc, pos.x-250, pos.y, 6564 / maxFrame[1], 683, 6564 / maxFrame[1], 0, 6564 / maxFrame[1], 683, frame);
		}
		if (status == STATUS::BACK)
		{
			image[2].Render(hdc, pos.x, pos.y, 6564 / maxFrame[2], 683, 6564 / maxFrame[2], 0, 6564 / maxFrame[2], 683, frame);
		}
		if (status == STATUS::JJAP)
		{
			image[3].Render(hdc, pos.x, pos.y, 7658 / maxFrame[3], 683, 7658 / maxFrame[3], 0, 7658 / maxFrame[3], 683, frame);
		}
		if (status == STATUS::PUNCH)
		{
			image[4].Render(hdc, pos.x, pos.y, 9846 / maxFrame[4], 683, 9846 / maxFrame[4], 0, 9846 / maxFrame[4], 683, frame);
		}
		if (status == STATUS::LOWKICK)
		{
			image[5].Render(hdc, pos.x, pos.y, 6564 / maxFrame[5], 683, 6564 / maxFrame[5], 0, 6564 / maxFrame[5], 683, frame);
		}
		if (status == STATUS::HIGHKICK)
		{
			image[6].Render(hdc, pos.x, pos.y, 13128 / maxFrame[6], 683, 13128 / maxFrame[6], 0, 13128 / maxFrame[6], 683, frame);
		}
		if (status == STATUS::SKILL)
		{
			image[7].Render(hdc, pos.x, pos.y, 3282 / maxFrame[7], 683, 3282 / maxFrame[7], 0, 3282 / maxFrame[7], 683, frame);
			image[8].Render(hdc, pos.x, pos.y, 17504 / maxFrame[8], 683, 17504 / maxFrame[8], 0, 17504 / maxFrame[8], 683, frame);
		}
	}
}

void Character::Move(STATUS status)
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
