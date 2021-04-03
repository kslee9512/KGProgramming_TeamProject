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
	frame = 0;
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

	if (FAILED(image[0].Init("Image/KyoImage/kyo_bmp/kyo_stance.bmp", 640, 106, 10, 1, true, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, "Image/KyoImage/kyo_bmp/kyo_stance.bmp", "Warning", MB_OK);
		return E_FAIL;
	}
	if (FAILED(image[1].Init("Image/KyoImage/kyo_bmp/kyo_walk.bmp", 320, 119, 5, 1, true, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, "Image/KyoImage/kyo_bmp/kyo_walk.bmp", "Warning", MB_OK);
		return E_FAIL;
	}
	if (FAILED(image[2].Init("Image/KyoImage/kyo_bmp/kyo_back.bmp", 348, 121, 6, 1, true, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, "Image/KyoImage/kyo_bmp/kyo_back.bmp", "Warning", MB_OK);
		return E_FAIL;
	}
	if (FAILED(image[3].Init("Image/KyoImage/kyo_bmp/kyo_jjab.bmp", 516, 128, 4, 1, true, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, "Image/KyoImage/kyo_bmp/kyo_jjab.bmp", "Warning", MB_OK);
		return E_FAIL;
	}
	if (FAILED(image[4].Init("Image/KyoImage/kyo_bmp/kyo_punch.bmp", 516, 126, 4, 1, true, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, "Image/KyoImage/kyo_bmp/kyo_punch.bmp", "Warning", MB_OK);
		return E_FAIL;
	}
	if (FAILED(image[5].Init("Image/KyoImage/kyo_bmp/kyo_lowkick.bmp", 903, 126, 7, 1, true, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, "Image/KyoImage/kyo_bmp/kyo_lowkick.bmp", "Warning", MB_OK);
		return E_FAIL;
	}
	if (FAILED(image[6].Init("Image/KyoImage/kyo_bmp/kyo_highkick.bmp", 1188, 132, 9, 1, true, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, "Image/KyoImage/kyo_bmp", "Warning", MB_OK);
		return E_FAIL;
	}
	if (FAILED(image[7].Init("Image/KyoImage/kyo_bmp/kyo_hit.bmp", 392, 115, 4, 1, true, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, "Image/KyoImage/kyo_bmp", "Warning", MB_OK);
		return E_FAIL;
	}
	if (FAILED(image[8].Init("Image/KyoImage/kyo_bmp/kyo_defeat.bmp", 640, 106, 10, 1, true, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, "Image/KyoImage/kyo_bmp", "Warning", MB_OK);
		return E_FAIL;
	}
	if (FAILED(image[9].Init("Image/KyoImage/kyo_bmp/kyo_win.bmp", 640, 106, 10, 1, true, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, "Image/KyoImage/kyo_bmp", "Warning", MB_OK);
		return E_FAIL;
	}
	if (FAILED(image[10].Init("Image/KyoImage/kyo_bmp", 640, 106, 10, 1, true, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, "Image/KyoImage/kyo_bmp", "Warning", MB_OK);
		return E_FAIL;
	}
	return S_OK;

	return S_OK;
}
