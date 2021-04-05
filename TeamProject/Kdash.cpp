#include "Kdash.h"
#include "Image.h"
HRESULT Kdash::Init(PPOS pPos)
{

	this->pPos = pPos;
	image = new Image[12];
	moveSpeed = 1;
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
	//캐릭터 이미지 복사
	//1P stance자세 복사
	if (FAILED(image[0].Init("Image/KdashImage/kdash_stance2p.bmp", 13710, 659, maxFrame[0], 1, true, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, "Image/KdashImage/kdash_stance1p.bmp 로드 실패", "Warning", MB_OK);
		return E_FAIL;
	}
	//1p 전진 이미지 복사
	else if (FAILED(image[1].Init("Image/KdashImage/kdash_walkforward2p.bmp", 9140, 659, maxFrame[1], 1, true, RGB(0, 0, 0))))
	{
		MessageBox(g_hWnd, "Image/K'Image/k'_walkforward1p.bmp 로드 실패", "Warning", MB_OK);
		return E_FAIL;
	}
	//1p 후방이동 이미지 복사
	else if (FAILED(image[2].Init("Image/KdashImage/kdash_walkback2p.bmp", 8226, 659, maxFrame[2], 1, true, RGB(0, 0, 0))))
	{
		MessageBox(g_hWnd, "Image/K'Image/k'_walkback2p.bmp 로드 실패", "Warning", MB_OK);
		return E_FAIL;
	}
	//1p jjap복사
	else if (FAILED(image[3].Init("Image/KdashImage/kdash_jjap2p.bmp", 5484, 659, maxFrame[3], 1, true, RGB(0, 0, 0))))
	{
		MessageBox(g_hWnd, "Image/K'Image/KdashImage/kdash_jjap2p.bmp 로드 실패", "Warning", MB_OK);
		return E_FAIL;
	}
	//1p punch복사
	else if (FAILED(image[4].Init("Image/KdashImage/kdash_punch2p.bmp", 10968, 659, maxFrame[4], 1, true, RGB(0, 0, 0))))
	{
		MessageBox(g_hWnd, "Image/K'Image/KdashImage/kdash_punch2p.bmp 로드 실패", "Warning", MB_OK);
		return E_FAIL;
	}
	//1p lowkick 이미지 복사
	else if (FAILED(image[5].Init("Image/KdashImage/kdash_lowkick2p.bmp", 6398, 659, maxFrame[5], 1, true, RGB(0, 0, 0))))
	{
		MessageBox(g_hWnd, "Image/K'Image/KdashImage/kdash_highkick2p.bmp 로드 실패", "Warning", MB_OK);
		return E_FAIL;
	}
	//1p HighKick이미지 복사
	else if (FAILED(image[6].Init("Image/KdashImage/kdash_highkick2p.bmp", 10054, 659, maxFrame[6], 1, true, RGB(0, 0, 0))))
	{
		MessageBox(g_hWnd, "Image/K'Image/KdashImage/kdash_highkick2p.bmp 로드 실패", "Warning", MB_OK);
		return E_FAIL;
	}
	//경직모션 복사
	else if (FAILED(image[7].Init("Image/KdashImage/kdash_hit2p.bmp", 6398, 659, maxFrame[7], 1, true, RGB(0, 0, 0))))
	{
		MessageBox(g_hWnd, "Image/K'Image/KdashImage/kdash_hit2p.bmp 로드 실패", "Warning", MB_OK);
		return E_FAIL;
	}
	//패배모션 복사
	else if (FAILED(image[8].Init("Image/KdashImage/kdash_defeat2p.bmp", 11882, 659, maxFrame[8], 1, true, RGB(0, 0, 0))))
	{
		MessageBox(g_hWnd, "Image/K'Image/KdashImage/kdash_defeat2p.bmp 로드 실패", "Warning", MB_OK);
		return E_FAIL;
	}
	//승리모션 복사
	else if (FAILED(image[9].Init("Image/KdashImage/kdash_win2p.bmp", 10968, 659, maxFrame[9], 1, true, RGB(0, 0, 0))))
	{
		MessageBox(g_hWnd, "Image/K'Image/KdashImage/kdash_win2p.bmp 로드 실패", "Warning", MB_OK);
		return E_FAIL;
	}
	//스킬모션 복사
	else if (FAILED(image[10].Init("Image/KdashImage/kdash_skill2p.bmp", 10054, 659, maxFrame[10], 1, true, RGB(0, 0, 0))))
	{
	MessageBox(g_hWnd, "Image/K'Image/KdashImage/kdash_skill2p.bmp 로드 실패", "Warning", MB_OK);
	return E_FAIL;
	}
	//투사체 이미지 복사
	else if (FAILED(image[11].Init("Image/KdashImage/kdash_trigger2p.bmp", 31076, 659, maxFrame[11], 1, true, RGB(0, 0, 0))))
	{
	MessageBox(g_hWnd, "Image/K'Image/KdashImage/kdash_skill2p.bmp 로드 실패", "Warning", MB_OK);
	return E_FAIL;
	}
	return S_OK;
}