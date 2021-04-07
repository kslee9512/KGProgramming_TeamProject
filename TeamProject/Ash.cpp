#include "Ash.h"
#include "Image.h"
#include "HitBox.h"
#include "AttackBox.h"
#include "CommandQueue.h"

HRESULT Ash::Init()
{
	return Init(pPos);
}


HRESULT Ash::Init(PPOS pPos)
{
	curHp = maxHp;
	this->pPos = pPos;
	image = new Image[12];
	isAlive = true;
	frameX = 0;
	frameY = 0;
	spriteWidth = 1094;
	spriteHeight = 683;
	moveSpeed = 10;
	maxFrame[0] = 28;
	maxFrame[1] = 12;
	maxFrame[2] = 12;
	maxFrame[3] = 11;
	maxFrame[4] = 12;
	maxFrame[5] = 9;
	maxFrame[6] = 12;
	maxFrame[7] = 4;
	maxFrame[8] = 12;
	maxFrame[9] = 21;
	maxFrame[10] = 15;
	maxFrame[11] = 15;
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

	if (pPos == PPOS::P1) {
		charPos.x = pos.x + 400;
	}
	else {
		charPos.x = pos.x + 270;
	}
	charPos.y = pos.y + 420;

	width = 100;
	height = 230;
	keyCache = new CommandQueue();
	keyCache->Init();
	hitBox = new HitBox();
	hitBox->Init(charPos, width, height);
	attackBox = new AttackBox;
	attackBox->Init(charPos, width, height + 50);

	if (FAILED(image[0].Init("Image/Ash_Image/stance_1.bmp", spriteWidth*maxFrame[0], spriteHeight, maxFrame[0], 1, true, RGB(0, 0, 0))))
	{
		MessageBox(g_hWnd, "Image/stance.bmp ?ュ? ????", "Warning", MB_OK);
		return E_FAIL;
	}
	if (FAILED(image[1].Init("Image/Ash_Image/walk.bmp", spriteWidth * maxFrame[1], spriteHeight, maxFrame[1], 1, true, RGB(0, 0, 0))))
	{
		MessageBox(g_hWnd, "Image/stance.bmp ?ュ? ????", "Warning", MB_OK);
		return E_FAIL;
	}
	if (FAILED(image[2].Init("Image/Ash_Image/back.bmp", spriteWidth * maxFrame[2], spriteHeight, maxFrame[2], 1, true, RGB(0, 0, 0))))
	{
		MessageBox(g_hWnd, "Image/stance.bmp ?ュ? ????", "Warning", MB_OK);
		return E_FAIL;
	}
	if (FAILED(image[3].Init("Image/Ash_Image/JJAP.bmp", spriteWidth * maxFrame[3], spriteHeight, maxFrame[3], 1, true, RGB(0, 0, 0))))
	{
		MessageBox(g_hWnd, "Image/stance.bmp ?ュ? ????", "Warning", MB_OK);
		return E_FAIL;
	}
	if (FAILED(image[4].Init("Image/Ash_Image/PUNCH.bmp", spriteWidth * maxFrame[4], spriteHeight, maxFrame[4], 1, true, RGB(0, 0, 0))))
	{
		MessageBox(g_hWnd, "Image/stance.bmp ?ュ? ????", "Warning", MB_OK);
		return E_FAIL;
	}
	if (FAILED(image[5].Init("Image/Ash_Image/LOWKICK.bmp", spriteWidth * maxFrame[5], spriteHeight, maxFrame[5], 1, true, RGB(0, 0, 0))))
	{
		MessageBox(g_hWnd, "Image/stance.bmp ?ュ? ????", "Warning", MB_OK);
		return E_FAIL;
	}
	if (FAILED(image[6].Init("Image/Ash_Image/HIGHKICK.bmp", spriteWidth * maxFrame[6], spriteHeight, maxFrame[6], 1, true, RGB(0, 0, 0))))
	{
		MessageBox(g_hWnd, "Image/stance.bmp ?ュ? ????", "Warning", MB_OK);
		return E_FAIL;
	}
	if (FAILED(image[7].Init("Image/Ash_Image/HIT.bmp", spriteWidth * maxFrame[7], spriteHeight, maxFrame[7], 1, true, RGB(0, 0, 0))))
	{
		MessageBox(g_hWnd, "Image/stance.bmp ?ュ? ????", "Warning", MB_OK);
		return E_FAIL;
	}
	if (FAILED(image[8].Init("Image/Ash_Image/DEFEAT.bmp", spriteWidth * maxFrame[8], spriteHeight, maxFrame[8], 1, true, RGB(0, 0, 0))))
	{
		MessageBox(g_hWnd, "Image/stance.bmp ?ュ? ????", "Warning", MB_OK);
		return E_FAIL;
	}
	if (FAILED(image[9].Init("Image/Ash_Image/WIN.bmp", spriteWidth * maxFrame[9], spriteHeight, maxFrame[9], 1, true, RGB(0, 0, 0))))
	{
		MessageBox(g_hWnd, "Image/stance.bmp ?ュ? ????", "Warning", MB_OK);
		return E_FAIL;
	}
	if (FAILED(image[10].Init("Image/Ash_Image/SKILL.bmp", spriteWidth * maxFrame[10], spriteHeight, maxFrame[10], 1, true, RGB(0, 0, 0))))
	{
		MessageBox(g_hWnd, "Image/stance.bmp ?ュ? ????", "Warning", MB_OK);
		return E_FAIL;
	}
	if (FAILED(image[11].Init("Image/Ash_Image/SKILL_EFFECT.bmp", spriteWidth * maxFrame[11], spriteHeight, maxFrame[11], 1, true, RGB(0, 0, 0))))
	{
		MessageBox(g_hWnd, "Image/stance.bmp ?ュ? ????", "Warning", MB_OK);
		return E_FAIL;
	}
	return S_OK;
}

void Ash::Update()
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


	}
	elapsedTime++;
	if (elapsedTime >= 5)
	{
		if (status != STATUS::DEFEAT && status != STATUS::WIN && !(status >= STATUS::WALK && status <= STATUS::BACK) && frameX >= maxFrame[status] - 1)
		{
			status = STATUS::STANCE;
			frameX = 0;
		}
		else if (status == STATUS::DEFEAT && frameX >= maxFrame[status] - 1 || status == STATUS::WIN && frameX >= maxFrame[status] - 1) {
			//frameX = maxFrame[status]-1;
			isAlive = false;
			frameX = maxFrame[status] - 2;
			Sleep(100);
		}

		if (status >= STATUS::WALK && status <= STATUS::BACK) {
			if (KeyManager::GetSingleton()->IsOnceKeyUp(VK_LEFT)
				|| KeyManager::GetSingleton()->IsOnceKeyUp(VK_RIGHT)
				|| KeyManager::GetSingleton()->IsOnceKeyUp('D')
				|| KeyManager::GetSingleton()->IsOnceKeyUp('A'))
			{
				status = STATUS::STANCE;
				frameX = 0;
			}
			else {
				Move();
				if (frameX >= maxFrame[status])
					frameX = 0;
				image[status].Update(frameX, frameY);
			}
		}
		else if (status == STATUS::SKILL) {
			image[status].Update(frameX, frameY);
			image[11].Update(frameX, frameY);
			attackBox->SetPos(charPos);
			attackBox->Update(pPos, status);
		}
		else if (status == STATUS::HIT) {
			KnockBack(20);
			image[status].Update(frameX, frameY);
		}
		else {
			image[status].Update(frameX, frameY);
			attackBox->SetPos(charPos);
			attackBox->Update(pPos, status);
		}

		frameX++;
		elapsedTime = 0;
	}
}

void Ash::Move()
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
		if (pos.x <= -330)
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
		if (charPos.x >= 1000)
		{
			charPos.x -= moveSpeed;
		}
		hitBox->SetPos(charPos);
		hitBox->Update();
		attackBox->SetPos(charPos);
		attackBox->Update(charPos);
		this->pos.x += moveSpeed;
		if (pos.x >= 730)
		{
			pos.x -= moveSpeed;
		}
	}
}

void Ash::Render(HDC hdc)
{
    if (image) {
        if (status == STATUS::SKILL)
        {
            if (pPos == PPOS::P1) {
                image[status].RenderReverse(hdc, pos.x + 20, pos.y + 35, spriteWidth, spriteHeight);
                image[11].RenderReverse(hdc, pos.x, pos.y, spriteWidth, spriteHeight);
            }
            else if (pPos == PPOS::P2) {
                image[status].Render(hdc, pos.x - 400, pos.y + 35, spriteWidth, spriteHeight);
                image[11].Render(hdc, pos.x - 400, pos.y + 45, spriteWidth, spriteHeight);
            }
        }
        else {
            if (pPos == PPOS::P1) {
                image[status].RenderReverse(hdc, pos.x - 20, pos.y + 35, spriteWidth, spriteHeight);
            }
            else if (pPos == PPOS::P2) {
                image[status].Render(hdc, pos.x - 400, pos.y + 45, spriteWidth, spriteHeight);
            }
        }
    }
	/*hitBox->Render(hdc);
	attackBox->Render(hdc);*/
}
