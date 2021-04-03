#include "Kdash.h"
#include "Image.h"
HRESULT Kdash::Init(PPOS pPos)
{
	this->pPos = pPos;
	image = new Image[22];
	frame = 0;
	moveSpeed = 1;
	maxFrame[0] = 15; //1P, 2P stance
	maxFrame[1] = 8; //1p, 2p walkforward
	maxFrame[2] = 9; //1p, 2p, walkback
	maxFrame[3] = 6; //jjap
	maxFrame[4] = 8; //punch
	maxFrame[5] = 12;//lowkich
	maxFrame[6]; //highkick
	status = STATUS::STANCE;
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
	//ĳ���� �̹��� ����
	//1P, 2P stance�ڼ� ����
	if (FAILED(image[0].Init("Image/KdashImage/kdash_stance1p.bmp", 13710, 659, maxFrame[0], 1, true, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, "Image/KdashImage/kdash_stance1p.bmp �ε� ����", "Warning", MB_OK);
		return E_FAIL;
	}
	else if (FAILED(image[1].Init("Image/KdashImage/kdash_stance2p.bmp", 13710, 659, maxFrame[0], 1, true, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, "Image/K'Image/k'_stance2p.bmp �ε� ����", "Warning", MB_OK);
		return E_FAIL;
	}
	//1P, 2P ���� �̹��� ����
	else if (FAILED(image[2].Init("Image/KdashImage/kdash_walkforward1p.bmp", 7312 , 659, maxFrame[1], 1, true, RGB(0, 0, 0))))
	{
		MessageBox(g_hWnd, "Image/K'Image/k'_walkforward1p.bmp �ε� ����", "Warning", MB_OK);
		return E_FAIL;
	}
	else if (FAILED(image[3].Init("Image/KdashImage/kdash_walkforward2p.bmp", 7312, 659, maxFrame[1], 1, true, RGB(0, 0, 0))))
	{
		MessageBox(g_hWnd, "Image/K'Image/k'_walkforward2p.bmp �ε� ����", "Warning", MB_OK);
		return E_FAIL;
	}
	//1p, 2p �Ĺ��̵� �̹��� ����
	else if (FAILED(image[4].Init("Image/KdashImage/kdash_walkback1p.bmp", 8226, 659, maxFrame[2], 1, true, RGB(0, 0, 0))))
	{
		MessageBox(g_hWnd, "Image/K'Image/k'_walkback1p.bmp �ε� ����", "Warning", MB_OK);
		return E_FAIL;
	}
	else if (FAILED(image[5].Init("Image/KdashImage/kdash_walkback2p.bmp", 8226, 659, maxFrame[2], 1, true, RGB(0, 0, 0))))
	{
		MessageBox(g_hWnd, "Image/K'Image/k'_walkback2p.bmp �ε� ����", "Warning", MB_OK);
		return E_FAIL;
	}
	//1p, 2p jjap����
	else if (FAILED(image[6].Init("Image/KdashImage/kdash_jjap1p.bmp", 5484, 659, maxFrame[3], 1, true, RGB(0, 0, 0))))
	{
		MessageBox(g_hWnd, "Image/K'Image/KdashImage/kdash_jjap1p.bmp �ε� ����", "Warning", MB_OK);
		return E_FAIL;
	}
	else if (FAILED(image[7].Init("Image/KdashImage/kdash_jjap2p.bmp", 5484, 659, maxFrame[3], 1, true, RGB(0, 0, 0))))
	{
		MessageBox(g_hWnd, "Image/K'Image/KdashImage/kdash_jjap2p.bmp �ε� ����", "Warning", MB_OK);
		return E_FAIL;
	}
	//1p, 2p punch����
	else if (FAILED(image[8].Init("Image/KdashImage/kdash_punch1p.bmp", 1152, 112, maxFrame[3], 1, true, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, "Image/K'Image/KdashImage/kdash_punch1p.bmp �ε� ����", "Warning", MB_OK);
		return E_FAIL;
	}
	else if (FAILED(image[9].Init("Image/KdashImage/kdash_punch2p.bmp", 1152, 112, maxFrame[3], 1, true, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, "Image/K'Image/KdashImage/kdash_punch2p.bmp �ε� ����", "Warning", MB_OK);
		return E_FAIL;
	}
	//1p, 2p lowkick �̹��� ����
	else if (FAILED(image[10].Init("Image/KdashImage/kdash_lowkick1p.bmp", 640, 128, maxFrame[4], 1, true, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, "Image/K'Image/KdashImage/kdash_highkick1p.bmp �ε� ����", "Warning", MB_OK);
		return E_FAIL;
	}
	else if (FAILED(image[11].Init("Image/KdashImage/kdash_lowkick2p.bmp", 640, 128, maxFrame[4], 1, true, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, "Image/K'Image/KdashImage/kdash_highkick2p.bmp �ε� ����", "Warning", MB_OK);
		return E_FAIL;
	}
	//1p, 2p HighKick�̹��� ����
	else if (FAILED(image[12].Init("Image/KdashImage/kdash_highkick1p.bmp", 1440, 128, maxFrame[5], 1, true, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, "Image/K'Image/KdashImage/kdash_highkick1p.bmp �ε� ����", "Warning", MB_OK);
		return E_FAIL;
	}
	else if (FAILED(image[13].Init("Image/KdashImage/kdash_highkick2p.bmp", 1440, 128, maxFrame[5], 1, true, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, "Image/K'Image/KdashImage/kdash_highkick2p.bmp �ε� ����", "Warning", MB_OK);
		return E_FAIL;
	}
	return S_OK;
}