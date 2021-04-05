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
	moveSpeed = 10;
	maxImage = 12;
	status = STATUS::STANCE;
	if (pPos == PPOS::P1)
	{
		pos.x = 0;
		pos.y = GROUND_Y;
	}
	else if (pPos == PPOS::P2)
	{
		pos.x = (WINSIZE_X) - 679;
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
	maxFrame[8] = 30;
	maxFrame[9] = 5;
	maxFrame[10] = 3;
	maxFrame[11] = 30;
	if (FAILED(image[0].Init("Image/KyoImage/kyo_bmp/kyo_stanceR.bmp", 7469, 689, maxFrame[0], 1, true, RGB(0, 0, 0))))
	{
		MessageBox(g_hWnd, "Image/KyoImage/kyo_bmp/kyo_stanceR.bmp", "Warning", MB_OK);
		return E_FAIL;
	}
	if (FAILED(image[1].Init("Image/KyoImage/kyo_bmp/kyo_walkR.bmp", 7469, 689, maxFrame[1], 1, true, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, "Image/KyoImage/kyo_bmp/kyo_walkR.bmp", "Warning", MB_OK);
		return E_FAIL;
	}
	if (FAILED(image[2].Init("Image/KyoImage/kyo_bmp/kyo_backR.bmp", 6790, 689, maxFrame[2], 1, true, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, "Image/KyoImage/kyo_bmp/kyo_backR.bmp", "Warning", MB_OK);
		return E_FAIL;
	}
	if (FAILED(image[3].Init("Image/KyoImage/kyo_bmp/kyo_jjabR.bmp", 2037, 689, maxFrame[3], 1, true, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, "Image/KyoImage/kyo_bmp/kyo_jjabR.bmp", "Warning", MB_OK);
		return E_FAIL;
	}
	if (FAILED(image[4].Init("Image/KyoImage/kyo_bmp/kyo_punchR.bmp", 4074, 689, maxFrame[4], 1, true, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, "Image/KyoImage/kyo_bmp/kyo_punchR.bmp", "Warning", MB_OK);
		return E_FAIL;
	}
	if (FAILED(image[5].Init("Image/KyoImage/kyo_bmp/kyo_lowkickR.bmp", 2716, 689, maxFrame[5], 1, true, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, "Image/KyoImage/kyo_bmp/kyo_lowkickR.bmp", "Warning", MB_OK);
		return E_FAIL;
	}
	if (FAILED(image[6].Init("Image/KyoImage/kyo_bmp/kyo_highkickR.bmp", 4074, 689, maxFrame[6], 1, true, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, "Image/KyoImage/kyo_bmp/kyo_highkickR.bmp", "Warning", MB_OK);
		return E_FAIL;
	}
	if (FAILED(image[7].Init("Image/KyoImage/kyo_bmp/kyo_hitR.bmp", 2716, 689, maxFrame[7], 1, true, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, "Image/KyoImage/kyo_bmp/kyo_hitR.bmp", "Warning", MB_OK);
		return E_FAIL;
	}
	if (FAILED(image[8].Init("Image/KyoImage/kyo_bmp/kyo_skill1R.bmp", 20370, 689, maxFrame[8], 1, true, RGB(0, 0, 0))))
	{
		MessageBox(g_hWnd, "Image/KyoImage/kyo_bmp/kyo_skill1R.bmp", "Warning", MB_OK);
		return E_FAIL;
	}
	if (FAILED(image[9].Init("Image/KyoImage/kyo_bmp/kyo_defeatR.bmp", 3395, 689, maxFrame[9], 1, true, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, "Image/KyoImage/kyo_bmp/kyo_defeatR.bmp", "Warning", MB_OK);
		return E_FAIL;
	}
	if (FAILED(image[10].Init("Image/KyoImage/kyo_bmp/kyo_winR.bmp", 2037, 689, maxFrame[10], 1, true, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, "Image/KyoImage/kyo_bmp/kyo_winR.bmp", "Warning", MB_OK);
		return E_FAIL;
	}
	if (FAILED(image[11].Init("Image/KyoImage/kyo_bmp/kyo_skill1R2.bmp", 20370, 689, maxFrame[11], 1, true, RGB(0, 0, 0))))
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
		if (KeyManager::GetSingleton()->IsOnceKeyDown('u')
			|| KeyManager::GetSingleton()->IsOnceKeyDown('U'))
		{
			status = STATUS::JJAP;
			frameX = 0;
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyDown('i')
			|| KeyManager::GetSingleton()->IsOnceKeyDown('I'))
		{
			status = STATUS::PUNCH;
			frameX = 0;
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyDown('j')
			|| KeyManager::GetSingleton()->IsOnceKeyDown('J'))
		{
			status = STATUS::LOWKICK;
			frameX = 0;
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyDown('k')
			|| KeyManager::GetSingleton()->IsOnceKeyDown('K'))
		{
			status = STATUS::HIGHKICK;
			frameX = 0;
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyDown('p')
			|| KeyManager::GetSingleton()->IsOnceKeyDown('P'))
		{
			status = STATUS::SKILL;
			frameX = 0;
		}
		else if (KeyManager::GetSingleton()->IsStayKeyDown('a')
			|| KeyManager::GetSingleton()->IsStayKeyDown('A'))
		{
			if (STATUS::STANCE <= status && status <= STATUS::BACK) {
				if (status != STATUS::BACK)
					frameX = 0;
				status = STATUS::BACK;
			}
		}
		else if (KeyManager::GetSingleton()->IsStayKeyDown('d')
			|| KeyManager::GetSingleton()->IsStayKeyDown('D'))
		{
			if (STATUS::STANCE <= status && status <= STATUS::BACK) {
				if (status != STATUS::WALK)
					frameX = 0;
				status = STATUS::WALK;
			}
		}
		if (frameX >= maxFrame[status])
		{
			status = STATUS::STANCE;
			frameX = 0;
		}
		else if (STATUS::WALK <= status && status <= STATUS::BACK)
		{
			if (KeyManager::GetSingleton()->IsOnceKeyUp('a')
				|| KeyManager::GetSingleton()->IsOnceKeyUp('A')
				|| KeyManager::GetSingleton()->IsOnceKeyUp('d')
				|| KeyManager::GetSingleton()->IsOnceKeyUp('D'))
			{
				status = STATUS::STANCE;
				frameX = 0;
			}
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
		else if (KeyManager::GetSingleton()->IsStayKeyDown(VK_RIGHT))
		{
			if (STATUS::STANCE <= status && status <= STATUS::BACK) {
				if (status != STATUS::BACK)
					frameX = 0;
				status = STATUS::BACK;
			}
		}
		else if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LEFT))
		{
			if (STATUS::STANCE <= status && status <= STATUS::BACK) {
				if (status != STATUS::WALK)
					frameX = 0;
				status = STATUS::WALK;
			}
		}
		if (frameX >= maxFrame[status])
		{
			status = STATUS::STANCE;
			frameX = 0;
		}
		else if (STATUS::WALK <= status && status <= STATUS::BACK)
		{
			if (KeyManager::GetSingleton()->IsOnceKeyUp(VK_LEFT)
				|| KeyManager::GetSingleton()->IsOnceKeyUp(VK_RIGHT))
			{
				status = STATUS::STANCE;
				frameX = 0;
			}
		}
	}
	elapsedTime++;
	if (elapsedTime >= 5)
	{
		if (status >= STATUS::WALK && status <= STATUS::BACK)
			Move();
		if (status == STATUS::SKILL) {
			image[status].Update(frameX, frameY);
			image[11].Update(frameX, frameY);
		}else{
			image[status].Update(frameX, frameY);
		}
		frameX++;
		elapsedTime = 0;
	}
}