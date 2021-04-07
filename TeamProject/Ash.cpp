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
