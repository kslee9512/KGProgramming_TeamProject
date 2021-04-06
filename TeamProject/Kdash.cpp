#include "Kdash.h"
#include "Image.h"

HRESULT Kdash::Init()
{
	return Init(PPOS::P1);
}

HRESULT Kdash::Init(PPOS pPos)
{

	this->pPos = pPos;
	image = new Image[12];
	frameX = 0;
	frameY = 0;
	moveSpeed = 10;
	spriteWidth = 914;
	spriteHeight = 659;
	maxFrame[0] = 15; //1P, 2P stance
	maxFrame[1] = 10; //1p, 2p walkforward
	maxFrame[2] = 9; //1p, 2p, walkback
	maxFrame[3] = 6; //jjap
	maxFrame[4] = 12; //punch
	maxFrame[5] = 7;//lowkich
	maxFrame[6] = 11; //highkick
	maxFrame[7] = 7; //Hit
	maxFrame[8] = 13; //Defeat
	maxFrame[9] = 12; //WIN
	maxFrame[10] = 11;
	maxFrame[11] = 34;
	status = STATUS::STANCE;
	if (pPos == PPOS::P1)
	{
		pos.x = 0;
		pos.y = (GROUND_Y);
	}
	else if (pPos == PPOS::P2)
	{
		pos.x = 300;
		pos.y = (GROUND_Y);
	}
	//��???? ????? ????
	//1P stance??? ????
	if (FAILED(image[0].Init("Image/KdashImage/kdash_stance2p.bmp", 13710, 659, maxFrame[0], 1, true, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, "Image/KdashImage/kdash_stance1p.bmp ?ュ? ????", "Warning", MB_OK);
		return E_FAIL;
	}
	//1p ???? ????? ????
	else if (FAILED(image[1].Init("Image/KdashImage/kdash_walkforward2p.bmp", 9140, 659, maxFrame[1], 1, true, RGB(0, 0, 0))))
	{
		MessageBox(g_hWnd, "Image/K'Image/k'_walkforward1p.bmp ?ュ? ????", "Warning", MB_OK);
		return E_FAIL;
	}
	//1p ?????? ????? ????
	else if (FAILED(image[2].Init("Image/KdashImage/kdash_walkback2p.bmp", 8226, 659, maxFrame[2], 1, true, RGB(0, 0, 0))))
	{
		MessageBox(g_hWnd, "Image/K'Image/k'_walkback2p.bmp ?ュ? ????", "Warning", MB_OK);
		return E_FAIL;
	}
	//1p jjap????
	else if (FAILED(image[3].Init("Image/KdashImage/kdash_jjap2p.bmp", 5484, 659, maxFrame[3], 1, true, RGB(0, 0, 0))))
	{
		MessageBox(g_hWnd, "Image/K'Image/KdashImage/kdash_jjap2p.bmp ?ュ? ????", "Warning", MB_OK);
		return E_FAIL;
	}
	//1p punch????
	else if (FAILED(image[4].Init("Image/KdashImage/kdash_punch2p.bmp", 10968, 659, maxFrame[4], 1, true, RGB(0, 0, 0))))
	{
		MessageBox(g_hWnd, "Image/K'Image/KdashImage/kdash_punch2p.bmp ?ュ? ????", "Warning", MB_OK);
		return E_FAIL;
	}
	//1p lowkick ????? ????
	else if (FAILED(image[5].Init("Image/KdashImage/kdash_lowkick2p.bmp", 6398, 659, maxFrame[5], 1, true, RGB(0, 0, 0))))
	{
		MessageBox(g_hWnd, "Image/K'Image/KdashImage/kdash_highkick2p.bmp ?ュ? ????", "Warning", MB_OK);
		return E_FAIL;
	}
	//1p HighKick????? ????
	else if (FAILED(image[6].Init("Image/KdashImage/kdash_highkick2p.bmp", 10054, 659, maxFrame[6], 1, true, RGB(0, 0, 0))))
	{
		MessageBox(g_hWnd, "Image/K'Image/KdashImage/kdash_highkick2p.bmp ?ュ? ????", "Warning", MB_OK);
		return E_FAIL;
	}
	//??????? ????
	else if (FAILED(image[7].Init("Image/KdashImage/kdash_hit2p.bmp", 6398, 659, maxFrame[7], 1, true, RGB(0, 0, 0))))
	{
		MessageBox(g_hWnd, "Image/K'Image/KdashImage/kdash_hit2p.bmp ?ュ? ????", "Warning", MB_OK);
		return E_FAIL;
	}
	//?��??? ????
	else if (FAILED(image[8].Init("Image/KdashImage/kdash_defeat2p.bmp", 11882, 659, maxFrame[8], 1, true, RGB(0, 0, 0))))
	{
		MessageBox(g_hWnd, "Image/K'Image/KdashImage/kdash_defeat2p.bmp ?ュ? ????", "Warning", MB_OK);
		return E_FAIL;
	}
	//?↑???? ????
	else if (FAILED(image[9].Init("Image/KdashImage/kdash_win2p.bmp", 10968, 659, maxFrame[9], 1, true, RGB(0, 0, 0))))
	{
		MessageBox(g_hWnd, "Image/K'Image/KdashImage/kdash_win2p.bmp ?ュ? ????", "Warning", MB_OK);
		return E_FAIL;
	}
	//?????? ????
	else if (FAILED(image[10].Init("Image/KdashImage/kdash_skill2p.bmp", 10054, 659, maxFrame[10], 1, true, RGB(0, 0, 0))))
	{
	MessageBox(g_hWnd, "Image/K'Image/KdashImage/kdash_skill2p.bmp ?ュ? ????", "Warning", MB_OK);
	return E_FAIL;
	}
	//????? ????? ????
	else if (FAILED(image[11].Init("Image/KdashImage/kdash_trigger2p.bmp", 31076, 659, maxFrame[11], 1, true, RGB(0, 0, 0))))
	{
	MessageBox(g_hWnd, "Image/K'Image/KdashImage/kdash_skill2p.bmp ?ュ? ????", "Warning", MB_OK);
	return E_FAIL;
	}
	return S_OK;
}

void Kdash::Render(HDC hdc)
{
    if (image) {
        if (status == STATUS::SKILL)
        {
            if (pPos == PPOS::P1) {
                image[status].RenderReverse(hdc, pos.x, pos.y, spriteWidth, spriteHeight);
                image[11].RenderReverse(hdc, pos.x, pos.y, spriteWidth, spriteHeight);
            }
            else if (pPos == PPOS::P2) {
                image[status].Render(hdc, pos.x - 150, pos.y, spriteWidth, spriteHeight);
                image[11].Render(hdc, pos.x - 150, pos.y, spriteWidth, spriteHeight);
            }
        }
        else {
            if (pPos == PPOS::P1) {
                image[status].RenderReverse(hdc, pos.x, pos.y, spriteWidth, spriteHeight);
            }
            else if (pPos == PPOS::P2) {
                image[status].Render(hdc, pos.x - 150, pos.y, spriteWidth, spriteHeight);
            }
        }
    }
    
}

void Kdash::Update()
{
	if (pPos == PPOS::P1)
	{
		if (KeyManager::GetSingleton()->IsOnceKeyDown('U'))
		{
			if (STATUS::STANCE <= status && status <= STATUS::BACK) {
				status = STATUS::JJAP;
				frameX = 0;
			}
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyDown('I'))
		{
			if (STATUS::STANCE <= status && status <= STATUS::BACK) {
				status = STATUS::PUNCH;
				frameX = 0;
			}
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyDown('J'))
		{
			if (STATUS::STANCE <= status && status <= STATUS::BACK) {
				status = STATUS::LOWKICK;
				frameX = 0;
			}
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyDown('K'))
		{
			if (STATUS::STANCE <= status && status <= STATUS::BACK) {
				status = STATUS::HIGHKICK;
				frameX = 0;
			}
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyDown('P'))
		{
			if (STATUS::STANCE <= status && status <= STATUS::BACK) {
				status = STATUS::SKILL;
				frameX = 0;
			}
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
			if (STATUS::STANCE <= status && status <= STATUS::BACK) {
				status = STATUS::JJAP;
				frameX = 0;
			}
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_NUMPAD6))
		{
			if (STATUS::STANCE <= status && status <= STATUS::BACK) {
				status = STATUS::PUNCH;
				frameX = 0;
			}
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_NUMPAD2))
		{
			if (STATUS::STANCE <= status && status <= STATUS::BACK) {
				status = STATUS::LOWKICK;
				frameX = 0;
			}
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_NUMPAD3))
		{
			if (STATUS::STANCE <= status && status <= STATUS::BACK) {
				status = STATUS::HIGHKICK;
				frameX = 0;
			}
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_NUMPAD0))
		{
			if (STATUS::STANCE <= status && status <= STATUS::BACK) {
				status = STATUS::SKILL;
				frameX = 0;
			}
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
