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
	else if (elapsedTime >= 7 && status == STATUS::WALK)
	{
		frame++;
		if (frame >= maxFrame[1])
		{
			frame = 0;
		}
		elapsedTime = 0;
	}
	else if (elapsedTime >= 7 && status == STATUS::BACK)
	{
		frame++;
		if (frame >= maxFrame[2])
		{
			frame = 0;
		}
		elapsedTime = 0;
	}
	else if (elapsedTime >= 5 && status == STATUS::JJAP)
	{
		frame++;
		if (frame >= maxFrame[2])
		{
			frame = 0;
		}
		elapsedTime = 0;
	}
	else if (elapsedTime >= 5 && status == STATUS::PUNCH)
	{
		frame++;
		if (frame >= maxFrame[3])
		{
			frame = 0;
		}
		elapsedTime = 0;
	}
	else if (elapsedTime >= 5 && status == STATUS::LOWKICK)
	{
		frame++;
		if (frame >= maxFrame[4])
		{
			frame = 0;
		}
		elapsedTime = 0;
	}
	else if (elapsedTime >= 5 && status == STATUS::HIGHKICK)
	{
		frame++;
		if (frame >= maxFrame[5])
		{
			frame = 0;
		}
		elapsedTime = 0;
	}
	if (pPos == PPOS::P1)
	{
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
		else
		{
			SetStatus(STATUS::STANCE);
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
			image[0].TestRender(hdc, 0, 150, 13710 / maxFrame[0], 659, 13710 / maxFrame[0], 0, 13710 /maxFrame[0], 659, frame);
		}
		else if (status == STATUS::WALK)
		{
			image[2].TestRender(hdc, 0, 150, 9140 / maxFrame[1], 659, 9140 / maxFrame[1], 0, 9140 / maxFrame[1], 659,frame);
		}
		else if (status == STATUS::BACK)
		{
			image[4].TestRender(hdc, 0, 150, 4570 / maxFrame[2], 659, 4570 / maxFrame[2], 0, 4570 / maxFrame[2], 659,frame);
		}
		else if (status == STATUS::JJAP)
		{
			image[6].Render(hdc, pos.x, pos.y, frame);
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
