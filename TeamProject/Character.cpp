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
		if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LEFT))
		{
			SetStatus(STATUS::BACK);
		}
		else if (KeyManager::GetSingleton()->IsStayKeyDown(VK_RIGHT))
		{
			SetStatus(STATUS::WALK);
		}
		else
		{
			SetStatus(STATUS::STANCE);
		}
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
	elapsedTime++;
	if (elapsedTime >= 5 && status == STATUS::STANCE)
	{
		frameX++;
		if (frameX >= 16)
		{
			elapsedTime = 0;

			frameX = 0;
		}
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
	if (pPos == PPOS::P1 && status == STATUS::WALK)
	{
		if (!isTouched) {
			charPos.x += moveSpeed;
			hitBox->SetPos(charPos);
			hitBox->Update();
			attackBox->SetPos(charPos);
			attackBox->Update(charPos);
			this->pos.x += moveSpeed;
		}
	}
	else if (pPos == PPOS::P1 && status == STATUS::BACK)
	{
		charPos.x -= moveSpeed;
		hitBox->SetPos(charPos);
		hitBox->Update();
		attackBox->SetPos(charPos);
		attackBox->Update(charPos);
		this->pos.x -= moveSpeed;
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
		hitBox->SetPos(charPos);
		hitBox->Update();
		attackBox->SetPos(charPos);
		attackBox->Update(charPos);
		this->pos.x += moveSpeed;
	}
}

void Character::Attack(STATUS status)
{

}

void Character::KnockBack(int distance)
{
	if (pPos == PPOS::P1) {
		charPos.x -= distance;
		hitBox->SetPos(charPos);
		hitBox->Update();
		pos.x -= distance;
		//TODO 화면 끝이면 막아주기
	}
	else if(pPos == PPOS::P2){
		charPos.x += distance;
		hitBox->SetPos(charPos);
		hitBox->Update();
		pos.x += distance;
		//TODO 화면 끝이면 막아주기
	}
}
