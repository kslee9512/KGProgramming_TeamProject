#include "Ash.h"
#include "Image.h"

HRESULT Ash::Init(PPOS pPos)
{
	this->pPos = pPos;
	image = new Image[12];
	frameX = 0;
	frameY = 0;
	spriteWidth = 1074;
	spriteHeight = 683;
	moveSpeed = 10;
	maxImage = 12;
	maxFrame[0] = 14;
	maxFrame[1] = 6;
	maxFrame[2] = 6;
	maxFrame[3] = 7;
	maxFrame[4] = 9;
	maxFrame[5] = 6;
	maxFrame[6] = 12;
	maxFrame[7] = 4;
	maxFrame[8] = 11;
	maxFrame[9] = 16;
	maxFrame[10] = 16;
	maxFrame[11] = 16;
	status = STATUS::STANCE;
	if (pPos == PPOS::P1)
	{
		pos.x = 0;
		pos.y = GROUND_Y;
	}
	else if (pPos == PPOS::P2)
	{
		pos.x = (WINSIZE_X)-679;
		pos.y = GROUND_Y;
	}

	if (FAILED(image[0].Init("Image/Ash_Image/stance_1.bmp", spriteWidth*maxFrame[0], spriteHeight, maxFrame[0], 1, true, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, "Image/stance.bmp 로드 실패", "Warning", MB_OK);
		return E_FAIL;
	}
	if (FAILED(image[1].Init("Image/Ash_Image/walk.bmp", spriteWidth * maxFrame[1], spriteHeight, maxFrame[1], 1, true, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, "Image/stance.bmp 로드 실패", "Warning", MB_OK);
		return E_FAIL;
	}
	if (FAILED(image[2].Init("Image/Ash_Image/back.bmp", spriteWidth * maxFrame[2], spriteHeight, maxFrame[2], 1, true, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, "Image/stance.bmp 로드 실패", "Warning", MB_OK);
		return E_FAIL;
	}
	if (FAILED(image[3].Init("Image/Ash_Image/JJAP.bmp", spriteWidth * maxFrame[3], spriteHeight, maxFrame[3], 1, true, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, "Image/stance.bmp 로드 실패", "Warning", MB_OK);
		return E_FAIL;
	}
	if (FAILED(image[4].Init("Image/Ash_Image/PUNCH.bmp", spriteWidth * maxFrame[4], spriteHeight, maxFrame[4], 1, true, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, "Image/stance.bmp 로드 실패", "Warning", MB_OK);
		return E_FAIL;
	}
	if (FAILED(image[5].Init("Image/Ash_Image/LOWKICK.bmp", spriteWidth * maxFrame[5], spriteHeight, maxFrame[5], 1, true, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, "Image/stance.bmp 로드 실패", "Warning", MB_OK);
		return E_FAIL;
	}
	if (FAILED(image[6].Init("Image/Ash_Image/HIGHKICK.bmp", spriteWidth * maxFrame[6], spriteHeight, maxFrame[6], 1, true, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, "Image/stance.bmp 로드 실패", "Warning", MB_OK);
		return E_FAIL;
	}
	if (FAILED(image[7].Init("Image/Ash_Image/HIT.bmp", spriteWidth * maxFrame[7], spriteHeight, maxFrame[7], 1, true, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, "Image/stance.bmp 로드 실패", "Warning", MB_OK);
		return E_FAIL;
	}
	if (FAILED(image[8].Init("Image/Ash_Image/DEFEAT.bmp", spriteWidth * maxFrame[8], spriteHeight, maxFrame[8], 1, true, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, "Image/stance.bmp 로드 실패", "Warning", MB_OK);
		return E_FAIL;
	}
	if (FAILED(image[9].Init("Image/Ash_Image/WIN.bmp", spriteWidth * maxFrame[9], spriteHeight, maxFrame[9], 1, true, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, "Image/stance.bmp 로드 실패", "Warning", MB_OK);
		return E_FAIL;
	}
	if (FAILED(image[10].Init("Image/Ash_Image/SKILL.bmp", spriteWidth * maxFrame[10], spriteHeight, maxFrame[10], 1, true, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, "Image/stance.bmp 로드 실패", "Warning", MB_OK);
		return E_FAIL;
	}
	if (FAILED(image[11].Init("Image/Ash_Image/SKILL_EFFECT.bmp", spriteWidth * maxFrame[11], spriteHeight, maxFrame[11], 1, true, RGB(0, 0, 0))))
	{
		MessageBox(g_hWnd, "Image/stance.bmp 로드 실패", "Warning", MB_OK);
		return E_FAIL;
	}
	return S_OK;
}

HRESULT Ash::Init()
{
	return Init(PPOS::P1);
}

void Ash::Update()
{
	if (pPos == PPOS::P1)
	{
		if (KeyManager::GetSingleton()->IsOnceKeyDown('U'))
		{
			status = STATUS::JJAP;
			frameX = 0;
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyDown('I'))
		{
			status = STATUS::PUNCH;
			frameX = 0;
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyDown('J'))
		{
			status = STATUS::LOWKICK;
			frameX = 0;
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyDown('K'))
		{
			status = STATUS::HIGHKICK;
			frameX = 0;
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyDown('P'))
		{
			status = STATUS::SKILL;
			frameX = 0;
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyDown('A'))
		{
			if (STATUS::STANCE <= status && status <= STATUS::BACK) {
				if (status != STATUS::BACK)
					frameX = 0;
				status = STATUS::BACK;
			}
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyDown('D'))
		{
			if (STATUS::STANCE <= status && status <= STATUS::BACK) {
				if (status != STATUS::WALK)
					frameX = 0;
				status = STATUS::WALK;
			}
		}
		if (STATUS::WALK <= status && status <= STATUS::BACK)
		{
			if (KeyManager::GetSingleton()->IsOnceKeyUp('A')
				|| KeyManager::GetSingleton()->IsOnceKeyUp('D'))
			{
				status = STATUS::STANCE;
				frameX = 0;
			}
		}
		else if (frameX >= maxFrame[status])
		{
			status = STATUS::STANCE;
			frameX = 0;
		}
	}
	else if (pPos == PPOS::P2)
	{
		if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_NUMPAD5))
		{
			status = STATUS::JJAP;
			frameX = 0;
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_NUMPAD6))
		{
			status = STATUS::PUNCH;
			frameX = 0;
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_NUMPAD2))
		{
			status = STATUS::LOWKICK;
			frameX = 0;
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_NUMPAD3))
		{
			status = STATUS::HIGHKICK;
			frameX = 0;
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_NUMPAD0))
		{
			status = STATUS::SKILL;
			frameX = 0;
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_RIGHT))
		{
			if (STATUS::STANCE <= status && status <= STATUS::BACK) {
				if (status != STATUS::BACK)
					frameX = 0;
				status = STATUS::BACK;
			}
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_LEFT))
		{
			if (STATUS::STANCE <= status && status <= STATUS::BACK) {
				if (status != STATUS::WALK)
					frameX = 0;
				status = STATUS::WALK;
			}
		}
		if (STATUS::WALK <= status && status <= STATUS::BACK)
		{
			if (KeyManager::GetSingleton()->IsOnceKeyUp(VK_LEFT)
				|| KeyManager::GetSingleton()->IsOnceKeyUp(VK_RIGHT))
			{
				status = STATUS::STANCE;
				frameX = 0;
			}
		}
		else if (frameX >= maxFrame[status])
		{
			status = STATUS::STANCE;
			frameX = 0;
		}
	}
	elapsedTime++;
	if (elapsedTime >= 5)
	{
		if (status >= STATUS::WALK && status <= STATUS::BACK) {

			Move();
			if (frameX >= maxFrame[status])
				frameX = 0;
			image[status].Update(frameX, frameY);
		}
		else if (status == STATUS::SKILL) {
			image[status].Update(frameX, frameY);
			image[11].Update(frameX, frameY);
		}
		else {
			image[status].Update(frameX, frameY);
		}
		frameX++;
		elapsedTime = 0;
	}
}