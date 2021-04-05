#include "Kyo.h"
#include "Image.h"

HRESULT Kyo::Init()
{
	return Init(PPOS::P1);
}

HRESULT Kyo::Init(PPOS pPos)
{
	this->pPos = pPos;
	image = new Image[12];
	frameX = 0;
	frameY = 0;
	spriteWidth = 679;
	spriteHeight = 689;
	moveSpeed = 10;
	maxImage = 12;
	status = STATUS::STANCE;
	spriteWidth = 679;
	spriteHeight = 689;
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

	maxFrame[0] = 11;
	maxFrame[1] = 11;
	maxFrame[2] = 10;
	maxFrame[3] = 3;
	maxFrame[4] = 6;
	maxFrame[5] = 4;
	maxFrame[6] = 6;
	maxFrame[7] = 4;
	maxFrame[8] = 5;
	maxFrame[9] = 3;
	maxFrame[10] = 30;
	maxFrame[11] = 30;
	if (FAILED(image[0].Init("Image/KyoImage/kyo_bmp/kyo_stanceR.bmp", spriteWidth*maxFrame[0], spriteHeight, maxFrame[0], 1, true, RGB(0, 0, 0))))
	{
		MessageBox(g_hWnd, "Image/KyoImage/kyo_bmp/kyo_stanceR.bmp", "Warning", MB_OK);
		return E_FAIL;
	}
	if (FAILED(image[1].Init("Image/KyoImage/kyo_bmp/kyo_walkR.bmp", spriteWidth*maxFrame[1], spriteHeight, maxFrame[1], 1, true, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, "Image/KyoImage/kyo_bmp/kyo_walkR.bmp", "Warning", MB_OK);
		return E_FAIL;
	}
	if (FAILED(image[2].Init("Image/KyoImage/kyo_bmp/kyo_backR.bmp", spriteWidth * maxFrame[2], spriteHeight, maxFrame[2], 1, true, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, "Image/KyoImage/kyo_bmp/kyo_backR.bmp", "Warning", MB_OK);
		return E_FAIL;
	}
	if (FAILED(image[3].Init("Image/KyoImage/kyo_bmp/kyo_jjabR.bmp", spriteWidth * maxFrame[3], spriteHeight, maxFrame[3], 1, true, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, "Image/KyoImage/kyo_bmp/kyo_jjabR.bmp", "Warning", MB_OK);
		return E_FAIL;
	}
	if (FAILED(image[4].Init("Image/KyoImage/kyo_bmp/kyo_punchR.bmp", spriteWidth * maxFrame[4], spriteHeight, maxFrame[4], 1, true, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, "Image/KyoImage/kyo_bmp/kyo_punchR.bmp", "Warning", MB_OK);
		return E_FAIL;
	}
	if (FAILED(image[5].Init("Image/KyoImage/kyo_bmp/kyo_lowkickR.bmp", spriteWidth * maxFrame[5], spriteHeight, maxFrame[5], 1, true, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, "Image/KyoImage/kyo_bmp/kyo_lowkickR.bmp", "Warning", MB_OK);
		return E_FAIL;
	}
	if (FAILED(image[6].Init("Image/KyoImage/kyo_bmp/kyo_highkickR.bmp", spriteWidth * maxFrame[6], spriteHeight, maxFrame[6], 1, true, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, "Image/KyoImage/kyo_bmp/kyo_highkickR.bmp", "Warning", MB_OK);
		return E_FAIL;
	}
	if (FAILED(image[7].Init("Image/KyoImage/kyo_bmp/kyo_hitR.bmp", spriteWidth * maxFrame[7], spriteHeight, maxFrame[7], 1, true, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, "Image/KyoImage/kyo_bmp/kyo_hitR.bmp", "Warning", MB_OK);
		return E_FAIL;
	}
	if (FAILED(image[8].Init("Image/KyoImage/kyo_bmp/kyo_defeatR.bmp", spriteWidth * maxFrame[8], spriteHeight, maxFrame[8], 1, true, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, "Image/KyoImage/kyo_bmp/kyo_defeatR.bmp", "Warning", MB_OK);
		return E_FAIL;
	}
	if (FAILED(image[9].Init("Image/KyoImage/kyo_bmp/kyo_winR.bmp", spriteWidth * maxFrame[9], spriteHeight, maxFrame[9], 1, true, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, "Image/KyoImage/kyo_bmp/kyo_winR.bmp", "Warning", MB_OK);
		return E_FAIL;
	}
	if (FAILED(image[10].Init("Image/KyoImage/kyo_bmp/kyo_skill1R.bmp", spriteWidth * maxFrame[10], spriteHeight, maxFrame[10], 1, true, RGB(0, 0, 0))))
	{
		MessageBox(g_hWnd, "Image/KyoImage/kyo_bmp/kyo_skill1R.bmp", "Warning", MB_OK);
		return E_FAIL;
	}
	if (FAILED(image[11].Init("Image/KyoImage/kyo_bmp/kyo_skill1R2.bmp", spriteWidth * maxFrame[11], spriteHeight, maxFrame[11], 1, true, RGB(0, 0, 0))))
	{
		MessageBox(g_hWnd, "Image/KyoImage/kyo_bmp/kyo_skill1R2.bmp", "Warning", MB_OK);
		return E_FAIL;
	}

	return S_OK;
}

void Kyo::Update()
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
		if (status >= STATUS::WALK && status <= STATUS::BACK){

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

void Kyo::Render(HDC hdc)
{
	if (image) {
		if (status == STATUS::SKILL)
		{
			if (pPos == PPOS::P1) {
				image[status].RenderReverse(hdc, pos.x, pos.y, spriteWidth, spriteHeight);
				image[11].RenderReverse(hdc, pos.x + 479, pos.y - 189, spriteWidth, spriteHeight);
			}
			else if (pPos == PPOS::P2) {
				image[status].Render(hdc, pos.x, pos.y, spriteWidth, spriteHeight);
				image[11].Render(hdc, pos.x - 479, pos.y - 189, spriteWidth, spriteHeight);
			}
		}
		else {
			if (pPos == PPOS::P1) {
				image[status].RenderReverse(hdc, pos.x, pos.y, spriteWidth, spriteHeight);
			}
			else if (pPos == PPOS::P2) {
				image[status].Render(hdc, pos.x, pos.y, spriteWidth, spriteHeight);
			}
		}
	}
}