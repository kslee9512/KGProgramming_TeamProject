#include "Kyo.h"
#include "Image.h"
#include "HitBox.h"
#include "AttackBox.h"
#include "CommandQueue.h"

HRESULT Kyo::Init()
{
	return Init(PPOS::P1);
}

HRESULT Kyo::Init(PPOS pPos)
{
	isAlive = true;
	this->pPos = pPos;
	curHp = maxHp;
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

	keyCache = new CommandQueue();
	keyCache->Init();

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
		charPos.x = pos.x + 360;
	}
	else {
		charPos.x = pos.x + 340;
	}
	charPos.y = pos.y + 420;

	width = 100;
	height = 230;
	hitBox = new HitBox();
	hitBox->Init(charPos, width, height);
	attackBox = new AttackBox;
	attackBox->Init(charPos, width, height+50);
    /*
    enum STATUS { STANCE, WALK, BACK, JJAP, PUNCH, LOWKICK, HIGHKICK, HIT, DEFEAT, WIN, SKILL, ENDSTATUS };
	*/
    maxFrame[0] = 11; //STANCE
	maxFrame[1] = 11; //WALK
	maxFrame[2] = 10; //BACK
	maxFrame[3] = 10; //JJAP
	maxFrame[4] = 11; //PUNCH
	maxFrame[5] = 9; //LOWKICK
	maxFrame[6] = 10; //HIGHKICK
	maxFrame[7] = 6; //HIT
	maxFrame[8] = 13; //DEFEAT
	maxFrame[9] = 13; //WIN
	maxFrame[10] = 20; //SKILL
	maxFrame[11] = 20; //SKILLEFFECT

	if (FAILED(image[0].Init("Image/KyoImage/kyo_bmp/kyo_stanceR.bmp", 7469, 689, maxFrame[0], 1, true, RGB(0, 0, 0))))
	{
		MessageBox(g_hWnd, "Image/KyoImage/kyo_bmp/kyo_stanceR.bmp", "Warning", MB_OK);
		return E_FAIL;
	}
	if (FAILED(image[1].Init("Image/KyoImage/kyo_bmp/kyo_walkR.bmp", 7469, 689, maxFrame[1], 1, true, RGB(0, 0, 0))))

	{
		MessageBox(g_hWnd, "Image/KyoImage/kyo_bmp/kyo_walkR.bmp", "Warning", MB_OK);
		return E_FAIL;
	}
	if (FAILED(image[2].Init("Image/KyoImage/kyo_bmp/kyo_backR.bmp", 6790, 689, maxFrame[2], 1, true, RGB(0, 0, 0))))

	{
		MessageBox(g_hWnd, "Image/KyoImage/kyo_bmp/kyo_backR.bmp", "Warning", MB_OK);
		return E_FAIL;
	}
	if (FAILED(image[3].Init("Image/KyoImage/kyo_bmp/kyo_jjabR.bmp", 6790, 689, maxFrame[3], 1, true, RGB(0, 0, 0))))
	{
		MessageBox(g_hWnd, "Image/KyoImage/kyo_bmp/kyo_jjabR.bmp", "Warning", MB_OK);
		return E_FAIL;
	}
	if (FAILED(image[4].Init("Image/KyoImage/kyo_bmp/kyo_punchR.bmp", 7469, 689, maxFrame[4], 1, true, RGB(0, 0, 0))))
	{
		MessageBox(g_hWnd, "Image/KyoImage/kyo_bmp/kyo_punchR.bmp", "Warning", MB_OK);
		return E_FAIL;
	}
	if (FAILED(image[5].Init("Image/KyoImage/kyo_bmp/kyo_lowkickR.bmp", 6111, 689, maxFrame[5], 1, true, RGB(0, 0, 0))))
	{
		MessageBox(g_hWnd, "Image/KyoImage/kyo_bmp/kyo_lowkickR.bmp", "Warning", MB_OK);
		return E_FAIL;
	}
	if (FAILED(image[6].Init("Image/KyoImage/kyo_bmp/kyo_highkickR.bmp", 6790, 689, maxFrame[6], 1, true, RGB(0, 0, 0))))
	{
		MessageBox(g_hWnd, "Image/KyoImage/kyo_bmp/kyo_highkickR.bmp", "Warning", MB_OK);
		return E_FAIL;
	}
	if (FAILED(image[7].Init("Image/KyoImage/kyo_bmp/kyo_hitR.bmp", 4074, 689, maxFrame[7], 1, true, RGB(0, 0, 0))))
	{
		MessageBox(g_hWnd, "Image/KyoImage/kyo_bmp/kyo_hitR.bmp", "Warning", MB_OK);
		return E_FAIL;
	}
	if (FAILED(image[8].Init("Image/KyoImage/kyo_bmp/kyo_loseR.bmp", 8827, 689, maxFrame[8], 1, true, RGB(0, 0, 0))))
	{
		MessageBox(g_hWnd, "Image/KyoImage/kyo_bmp/kyo_loseR.bmp", "Warning", MB_OK);
		return E_FAIL;
	}
	if (FAILED(image[9].Init("Image/KyoImage/kyo_bmp/kyo_winR.bmp", 8827, 689, maxFrame[9], 1, true, RGB(0, 0, 0))))
	{
		MessageBox(g_hWnd, "Image/KyoImage/kyo_bmp/kyo_winR.bmp", "Warning", MB_OK);
		return E_FAIL;
	}
	if (FAILED(image[10].Init("Image/KyoImage/kyo_bmp/kyo_skill1R.bmp", 13580, 689, maxFrame[10], 1, true, RGB(0, 0, 0))))
	{
		MessageBox(g_hWnd, "Image/KyoImage/kyo_bmp/kyo_skill1R.bmp", "Warning", MB_OK);
		return E_FAIL;
	}
	if (FAILED(image[11].Init("Image/KyoImage/kyo_bmp/kyo_skill1R2.bmp", 13580, 689, maxFrame[11], 1, true, RGB(0, 0, 0))))
	{
		MessageBox(g_hWnd, "Image/KyoImage/kyo_bmp/kyo_skill1R2.bmp", "Warning", MB_OK);
		return E_FAIL;
	}

	return S_OK;
}



void Kyo::Render(HDC hdc)
{
    if (image) {
        if (status == STATUS::SKILL)
        {
            if (pPos == PPOS::P1) {
                image[status].RenderReverse(hdc, pos.x + 20, pos.y + 25, spriteWidth, spriteHeight);
                image[11].RenderReverse(hdc, pos.x + 400, pos.y - 100, spriteWidth, spriteHeight);
            }
            else if (pPos == PPOS::P2) {
                image[status].Render(hdc, pos.x, pos.y + 25, spriteWidth, spriteHeight);
                image[11].Render(hdc, pos.x - 370, pos.y - 100, spriteWidth, spriteHeight);
            }
        }
        else {
            if (pPos == PPOS::P1) {
                image[status].RenderReverse(hdc, pos.x - 20, pos.y + 25, spriteWidth, spriteHeight);
            }
            else if (pPos == PPOS::P2) {
                image[status].Render(hdc, pos.x + 50, pos.y + 25, spriteWidth, spriteHeight);
            }
        }
    }
	/*hitBox->Render(hdc);
	attackBox->Render(hdc);*/
}
