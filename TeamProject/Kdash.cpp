#include "Kdash.h"
#include "Image.h"
#include "HitBox.h"
#include "AttackBox.h"
#include "CommandQueue.h"

HRESULT Kdash::Init()
{
	return Init(PPOS::P1);
}

HRESULT Kdash::Init(PPOS pPos)
{
	keyCache = new CommandQueue();
	keyCache->Init();
	curHp = maxHp;
	width = 100;
	height = 683;
	hitBox = new HitBox();
	hitBox->Init(pos, width, height);
	attackBox = new AttackBox[5];
	isAlive = true;
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
	if (pPos == PPOS::P1) {
		charPos.x = pos.x + 360;
	}
	else {
		charPos.x = pos.x + 400;
	}
	charPos.y = pos.y + 420;

	width = 150;
	height = 200;
	hitBox = new HitBox();
	hitBox->Init(charPos, width, height);
	attackBox = new AttackBox;
	attackBox->Init(charPos, width, height + 50);
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

	/*hitBox->Render(hdc);
	attackBox->Render(hdc);*/
}

void Kdash::Move()
{

	if (pPos == PPOS::P1 && status == STATUS::WALK)
	{
		if (!isTouched) {
			this->pos.x += moveSpeed;
			charPos.x += moveSpeed;
			hitBox->SetPos(charPos);
			hitBox->Update();
			attackBox->SetPos(charPos);
			attackBox->Update(charPos);
		}
	}
	else if (pPos == PPOS::P1 && status == STATUS::BACK)
	{
		charPos.x -= moveSpeed;
		if (charPos.x <= 70)
		{
			charPos.x += moveSpeed;
		}
		hitBox->SetPos(charPos);
		hitBox->Update();
		attackBox->SetPos(charPos);
		attackBox->Update(charPos);
		this->pos.x -= moveSpeed;
		if (pos.x <= -300)
		{
			pos.x += moveSpeed;
		}
	}
	else if (pPos == PPOS::P2 && status == STATUS::WALK)
	{
		if (!isTouched) {
			charPos.x -= moveSpeed;
			hitBox->SetPos(charPos);
			hitBox->Update();
			attackBox->SetPos(charPos);
			attackBox->Update(charPos);
			this->pos.x -= moveSpeed;
		}
	}
	else if (pPos == PPOS::P2 && status == STATUS::BACK)
	{
		charPos.x += moveSpeed;
		if (charPos.x >= 990)
		{
			charPos.x -= moveSpeed;
		}
		hitBox->SetPos(charPos);
		hitBox->Update();
		attackBox->SetPos(charPos);
		attackBox->Update(charPos);
		this->pos.x += moveSpeed;
		if (pos.x >= 600)
		{
			pos.x -= moveSpeed;
		}
	}
}

void Kdash::Update()
{
	if (pPos == PPOS::P1)
	{
		if (KeyManager::GetSingleton()->IsOnceKeyDown('S'))
		{
			keyCache->PushBack('S', 300);
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyDown('U'))
		{
			keyCache->PushBack('U', 300);
			if (STATUS::STANCE <= status && status <= STATUS::BACK) {
				status = STATUS::JJAP;
				attackBox->SetActivated(true);
				frameX = 0;
			}
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyDown('I'))
		{
			keyCache->PushBack('I', 300);
			if (STATUS::STANCE <= status && status <= STATUS::BACK) {
				status = STATUS::PUNCH;
				attackBox->SetActivated(true);
				frameX = 0;
			}
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyDown('J'))
		{
			keyCache->PushBack('J', 300);
			if (STATUS::STANCE <= status && status <= STATUS::BACK) {
				status = STATUS::LOWKICK;
				attackBox->SetActivated(true);
				frameX = 0;
			}
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyDown('K'))
		{
			keyCache->PushBack('K', 300);
			if (STATUS::STANCE <= status && status <= STATUS::BACK) {
				status = STATUS::HIGHKICK;
				attackBox->SetActivated(true);
				frameX = 0;
			}
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyDown('P'))
		{
			keyCache->PushBack('P', 300);
			if (STATUS::STANCE <= status && status <= STATUS::BACK) {
				status = STATUS::SKILL;
				attackBox->SetActivated(true);
				frameX = 0;
			}
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyDown('A'))
		{
			keyCache->PushBack('A', 300);
			if (STATUS::STANCE <= status && status <= STATUS::BACK) {
				if (status != STATUS::BACK) {
					frameX = 0;
				}
				status = STATUS::BACK;
			}
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyDown('D'))
		{
			keyCache->PushBack('D', 300);
			if (STATUS::STANCE <= status && status <= STATUS::BACK) {
				if (status != STATUS::WALK) {
					frameX = 0;
				}
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
		else if (status != STATUS::DEFEAT && status != STATUS::WIN && frameX >= maxFrame[status])
		{
			status = STATUS::STANCE;
			frameX = 0;
		}
	}
	else if (pPos == PPOS::P2)
	{
		if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_DOWN))
		{
			keyCache->PushBack(char{ VK_DOWN }, 300);
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_NUMPAD5))
		{
			keyCache->PushBack(char{ VK_NUMPAD5 }, 300);
			if (STATUS::STANCE <= status && status <= STATUS::BACK) {
				status = STATUS::JJAP;
				attackBox->SetActivated(true);
				frameX = 0;
			}
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_NUMPAD6))
		{
			keyCache->PushBack(char{ VK_NUMPAD6 }, 300);
			if (STATUS::STANCE <= status && status <= STATUS::BACK) {
				status = STATUS::PUNCH;
				attackBox->SetActivated(true);
				frameX = 0;
			}
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_NUMPAD2))
		{
			keyCache->PushBack(char{ VK_NUMPAD2 }, 300);
			if (STATUS::STANCE <= status && status <= STATUS::BACK) {
				status = STATUS::LOWKICK;
				attackBox->SetActivated(true);
				frameX = 0;
			}
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_NUMPAD3))
		{
			keyCache->PushBack(char{ VK_NUMPAD3 }, 300);
			if (STATUS::STANCE <= status && status <= STATUS::BACK) {
				status = STATUS::HIGHKICK;
				attackBox->SetActivated(true);
				frameX = 0;
			}
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_NUMPAD0))
		{
			keyCache->PushBack(char{ VK_NUMPAD0 }, 300);
			if (STATUS::STANCE <= status && status <= STATUS::BACK) {
				status = STATUS::SKILL;
				attackBox->SetActivated(true);
				frameX = 0;
			}
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_RIGHT))
		{
			keyCache->PushBack(char{ VK_RIGHT }, 300);
			if (STATUS::STANCE <= status && status <= STATUS::BACK) {
				if (status != STATUS::BACK) {
					frameX = 0;
				}
				status = STATUS::BACK;
			}
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_LEFT))
		{
			keyCache->PushBack(char{ VK_LEFT }, 300);
			if (STATUS::STANCE <= status && status <= STATUS::BACK) {
				if (status != STATUS::WALK) {
					frameX = 0;
				}
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
		else if (status != STATUS::DEFEAT && status != STATUS::WIN && frameX >= maxFrame[status])
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
			attackBox->SetPos(charPos);
			attackBox->Update(pPos, status);
		}
		else if (status == STATUS::HIT) {
			image[status].Update(frameX, frameY);
			KnockBack(20);
		}
		else {
			image[status].Update(frameX, frameY);
			attackBox->SetPos(charPos);
			attackBox->Update(pPos, status);
		}
		if (status == STATUS::DEFEAT && frameX >= maxFrame[status] || status == STATUS::WIN && frameX >= maxFrame[status]) {
			//frameX = maxFrame[status]-1;
			isAlive = false;
			Sleep(100);
		}
		frameX++;
		elapsedTime = 0;
	}
}
