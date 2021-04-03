#include "Character.h"
#include "Image.h"

HRESULT Character::Init(PPOS pPos)
{
	this->pPos = pPos;
	image = new Image[12];
	frame = 0;
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
	
	if (FAILED(image[0].Init("Image/K'Image/k'_stance1p.bmp", 1344, 122, 16, 1, true, RGB(255, 255, 255))))
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
	if (pPos == PPOS::P1)
	{
		elapsedTime++;
		if (elapsedTime >= 5)
		{
			frame++;
			elapsedTime = 0;
		}
		if (KeyManager::GetSingleton()->IsStayKeyDown('A'))
		{
			SetStatus(STATUS::BACK);
		}
		else if (KeyManager::GetSingleton()->IsStayKeyDown('D'))
		{
			SetStatus(STATUS::WALK);
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyDown('U'))
		{
			SetStatus(STATUS::JJAP);
			frame = 0;
		}
		else if (KeyManager::GetSingleton()->IsStayKeyDown('I'))
		{
			SetStatus(STATUS::PUNCH);
		}
		else if (KeyManager::GetSingleton()->IsStayKeyDown('J'))
		{
			SetStatus(STATUS::LOWKICK);
		}
		else if (KeyManager::GetSingleton()->IsStayKeyDown('K'))
		{
			SetStatus(STATUS::HIGHKICK);
		}
		if (frame >= maxFrame[status])
		{
			SetStatus(::STATUS::STANCE);
			frame = 0;
		}
		else if (STATUS::STANCE < status && status < STATUS::JJAP)
		{
			if (KeyManager::GetSingleton()->IsOnceKeyUp('A') || KeyManager::GetSingleton()->IsOnceKeyUp('D'))
			{
				SetStatus(STATUS::STANCE);
				frame = 0;
			}
		}
		Move(status);
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
	if (pPos == PPOS::P1)
	{
		if (status == STATUS::STANCE)
		{
			image[0].TestRender(hdc, 0, 100, 13710 / maxFrame[0], 659, 13710 / maxFrame[0], 0, 13710 /maxFrame[0], 659, frame);
		}
		else if (status == STATUS::WALK)
		{
			image[2].TestRender(hdc, 0, GROUND_Y, 7312 / maxFrame[1], 659, 7312 / maxFrame[1], 0, 7312 / maxFrame[1], 659,frame);
		}
		else if (status == STATUS::BACK)
		{
			image[4].TestRender(hdc, 0, GROUND_Y, 8226 / maxFrame[2], 659, 8226 / maxFrame[2], 0, 8226 / maxFrame[2], 659,frame);
		}
		else if (status == STATUS::JJAP)
		{
			image[6].TestRender(hdc, 0, GROUND_Y, 5484 / maxFrame[3], 659, 5484 / maxFrame[3], 0, 5484 / maxFrame[3], 659, frame);
		}
		else if (status == STATUS::PUNCH)
		{
			image[8].Render(hdc, pos.x, pos.y, frame);
		}
		else if (status == STATUS::LOWKICK)
		{
			image[10].Render(hdc, pos.x, pos.y, frame);
		}
		else if (status == STATUS::HIGHKICK)
		{
			image[12].Render(hdc, pos.x, pos.y, frame);
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
