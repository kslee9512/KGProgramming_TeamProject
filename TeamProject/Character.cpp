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
		if (frame >= maxFrame[status])
		{
			finishAction = true;
			SetStatus(STATUS::STANCE);
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
		if (isFired == true)
		{
				bulletElapsedTime += 4;
			if (bulletElapsedTime >= 8)
			{
				bulletFrame++;
				bulletElapsedTime = 0;

				if (bulletFrame == maxFrame[11])
				{
					isFired = false;
					bulletFrame = 0;
				}
			}
		}
		//키입력처리
		if (KeyManager::GetSingleton()->IsStayKeyDown('A')&& finishAction == true)
		{
			SetStatus(STATUS::BACK);
		}
		else if (KeyManager::GetSingleton()->IsStayKeyDown('D') && finishAction == true)
		{
			SetStatus(STATUS::WALK);
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyDown('U') && finishAction == true)
		{
			finishAction = false;
			SetStatus(STATUS::JJAP);
			frame = 0;
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyDown('I') && finishAction == true)
		{
			finishAction = false;
			SetStatus(STATUS::PUNCH);
			frame = 0;
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyDown('J') && finishAction == true)
		{
			finishAction = false;
			SetStatus(STATUS::LOWKICK);
			frame = 0;
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyDown('K') && finishAction == true)
		{
			finishAction = false;
			SetStatus(STATUS::HIGHKICK);
			frame = 0;
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyDown('O') && finishAction == true)
		{
			finishAction = false;
			SetStatus(STATUS::HIT);
			frame = 0;
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyDown('P') && finishAction == true)
		{
			finishAction = false;
			SetStatus(STATUS::DEFEAT);
			frame = 0;
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyDown('L') && finishAction == true)
		{
			finishAction = false;
			SetStatus(STATUS::WIN);
			frame = 0;
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyDown('M') && finishAction == true)
		{
			finishAction = false;
			if (isFired != true)
			{
				SetStatus(STATUS::SKILL);
				isFired = true;
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
			image[0].TestRender(hdc, pos.x, pos.y, 13710 / maxFrame[0], 659, 13710 / maxFrame[0], 0, 13710 /maxFrame[0], 659, frame);
		}
		else if (status == STATUS::WALK)
		{
			image[2].TestRender(hdc, pos.x, pos.y, 9140 / maxFrame[1], 659, 9140 / maxFrame[1], 0, 9140 / maxFrame[1], 659,frame);
		}
		else if (status == STATUS::BACK)
		{
			image[4].TestRender(hdc, pos.x, pos.y, 8226 / maxFrame[2], 659, 8226 / maxFrame[2], 0, 8226 / maxFrame[2], 659,frame);
		}
		else if (status == STATUS::JJAP)
		{
			image[6].TestRender(hdc, pos.x, pos.y, 5484 / maxFrame[3], 659, 5484 / maxFrame[3], 0, 5484 / maxFrame[3], 659, frame);
		}
		else if (status == STATUS::PUNCH)
		{
			image[8].TestRender(hdc, pos.x, pos.y, 10968 / maxFrame[4], 659, 10968 / maxFrame[4], 0, 10968 / maxFrame[4], 659, frame);
		}
		else if (status == STATUS::LOWKICK)
		{
			image[10].TestRender(hdc, pos.x, pos.y, 6398 / maxFrame[5], 659, 6398 / maxFrame[5], 0, 6398 / maxFrame[5], 659, frame);
		}
		else if (status == STATUS::HIGHKICK)
		{
			image[12].TestRender(hdc, pos.x, pos.y, 10054 / maxFrame[6], 659, 10054 / maxFrame[6], 0, 10054 / maxFrame[6], 659, frame);
		}
		else if (status == STATUS::HIT)
		{
			image[14].TestRender(hdc, pos.x, pos.y, 6398 / maxFrame[7], 659, 6398 / maxFrame[7], 0, 6398 / maxFrame[7], 659, frame);
		}
		else if (status == STATUS::DEFEAT)
		{
			image[16].TestRender(hdc, pos.x, pos.y, 11882 / maxFrame[8], 659, 11882 / maxFrame[8], 0, 11882 / maxFrame[8], 659, frame);
		}
		else if (status == STATUS::WIN)
		{
			image[18].TestRender(hdc, pos.x, pos.y, 10968 / maxFrame[9], 659, 10968 / maxFrame[9], 0, 10968 / maxFrame[9], 659, frame);
		}
		else if (status == STATUS::SKILL)
		{
			image[20].TestRender(hdc, pos.x, pos.y, 10054 / maxFrame[10], 659, 10054 / maxFrame[10], 0, 10054 / maxFrame[10], 659, frame);
			
		}
		if (isFired == true)
		{
			image[22].TestRender(hdc, pos.x, pos.y, 31076 / maxFrame[11], 659, 31076 / maxFrame[11], 0, 31076 / maxFrame[11], 659, bulletFrame);
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
