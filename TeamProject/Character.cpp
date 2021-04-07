#include "Character.h"
#include "Image.h"
#include "HitBox.h"
#include "AttackBox.h"
#include "CommandQueue.h"

HRESULT Character::Init(PPOS pPos)
{
	this->pPos = pPos;
	image = new Image[12];
	frameX = 0;
	frameY = 0;
	maxFrame[12];
	status = STATUS::STANCE;
	

	hitBox = new HitBox();
	attackBox = new AttackBox;

	keyCache = new CommandQueue();
	keyCache->Init();

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

	if (pPos == PPOS::P1) {
		charPos.x = pos.x + 400;
	}
	else {
		charPos.x = pos.x + 800;
	}
	charPos.y = pos.y / 2 + GROUND_Y;

	if (FAILED(image[0].Init("Image/K'Image/k'_stance1p.bmp", 1344, 122, 16, 1, true, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, "Image/Iori_walk.bmp 로드 실패", "Warning", MB_OK);
		return E_FAIL;
	}

	return S_OK;
}

void Character::Release()
{
	if(hitBox){
		delete hitBox;
		hitBox = nullptr;
	}
	if (attackBox) {
		delete attackBox;
		attackBox = nullptr;
	}
	if (image)
	{
		for (int i = 0; i < 11; i++)
		{
			image[i].Release();
		}
		delete[] image;
		image = nullptr;
	}
	if (keyCache) {
		keyCache->Release();
		delete keyCache;
		keyCache = nullptr;
	}
}

void Character::Update()
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
				if (KeyManager::GetSingleton()->IsStayKeyDown('A')) {
					status = STATUS::BACK;
				}
				else if (KeyManager::GetSingleton()->IsStayKeyDown('D')) {
					status = STATUS::WALK;
				}
				else {
					status = STATUS::STANCE;
					frameX = 0;
				}
			}
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
				if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LEFT)) {
					status = STATUS::WALK;
				}
				else if (KeyManager::GetSingleton()->IsStayKeyDown(VK_RIGHT)) {
					status = STATUS::BACK;
				}
				else {
					status = STATUS::STANCE;
					frameX = 0;
				}
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

		if (status >= STATUS::STANCE && status <= STATUS::BACK) {
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

void Character::Render(HDC hdc)
{
	if (image) {
		if (status == STATUS::SKILL)
		{
			if (pPos == PPOS::P1) {
				image[status].RenderReverse(hdc, pos.x, pos.y, spriteWidth, spriteHeight);
				image[11].RenderReverse(hdc, pos.x, pos.y, spriteWidth, spriteHeight);
			}
			else if (pPos == PPOS::P2) {
				image[status].Render(hdc, pos.x, pos.y, spriteWidth, spriteHeight);
				image[11].Render(hdc, pos.x, pos.y, spriteWidth, spriteHeight);
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

void Character::Move()
{
	if (pPos == PPOS::P1 && status == STATUS::STANCE) {
		if (walkingStatus == WALKINGSTATUS::GETTING_PUSHED) {
			charPos.x -= moveSpeed;
			if (charPos.x <= 70)
			{
				charPos.x += moveSpeed;
				walkingStatus = WALKINGSTATUS::IS_BLOCKED;
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
	}
	else if (pPos == PPOS::P1 && status == STATUS::WALK)
	{
		if (walkingStatus != WALKINGSTATUS::IS_CANCELLED) {
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
		this->pos.x -= moveSpeed;
		if (charPos.x <= 70)
		{
			charPos.x += moveSpeed;
			pos.x += moveSpeed;
		}
		hitBox->SetPos(charPos);
		hitBox->Update();
		attackBox->SetPos(charPos);
		attackBox->Update(charPos);
	}
	else if (pPos == PPOS::P2 && status == STATUS::STANCE) {
		if (walkingStatus == WALKINGSTATUS::GETTING_PUSHED) {
			charPos.x += moveSpeed;
			this->pos.x += moveSpeed;
			if (charPos.x >= 980)
			{
				charPos.x -= moveSpeed;
				pos.x -= moveSpeed;
				walkingStatus = WALKINGSTATUS::IS_BLOCKED;
			}
			hitBox->SetPos(charPos);
			hitBox->Update();
			attackBox->SetPos(charPos);
			attackBox->Update(charPos);
		}
	}
	else if (pPos == PPOS::P2 && status == STATUS::WALK)
	{
		if (walkingStatus != WALKINGSTATUS::IS_CANCELLED) {
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
		this->pos.x += moveSpeed;
		if (charPos.x >= 980)
		{
			charPos.x -= moveSpeed;
			pos.x -= moveSpeed;
		}
		hitBox->SetPos(charPos);
		hitBox->Update();
		attackBox->SetPos(charPos);
		attackBox->Update(charPos);
	}
}

void Character::Attack(STATUS status)
{

}

void Character::KnockBack(int distance)
{
	if (pPos == PPOS::P1) {
		charPos.x -= distance;
		pos.x -= distance;
		if (charPos.x <= 70)
		{
			pos.x += distance;
			charPos.x += distance;
		}
		hitBox->SetPos(charPos);
		hitBox->Update();
		attackBox->SetPos(charPos);
		attackBox->Update();
	}
	else if(pPos == PPOS::P2){
		charPos.x += distance;
		pos.x += distance;
		//TODO 화면 끝이면 막아주기
		if (charPos.x >= 980)
		{
			pos.x -= distance;
			charPos.x -= distance;
		}
		hitBox->SetPos(charPos);
		hitBox->Update();
		attackBox->SetPos(charPos);
		attackBox->Update();
	}
}
