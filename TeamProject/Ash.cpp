#include "Ash.h"
#include "Image.h"

HRESULT Ash::Init(PPOS pPos)
{
	this->pPos = pPos;
	image = new Image[15];
	frameX = 0;
	frameY = 0;
	moveSpeed = 1;
	maxFrame[0] = 14;
	maxFrame[1] = 6;
	maxFrame[2] = 6;
	maxFrame[3] = 7;
	maxFrame[4] = 9;
	maxFrame[5] = 6;
	maxFrame[6] = 12;
	maxFrame[7] = 4;
	maxFrame[8] = 11;
	maxFrame[9] = 16;
	maxFrame[10] = 16;
	maxFrame[11] = 16;
	status = STATUS::STANCE;
if (pPos == PPOS::P1)
{
	//pos.x = (WINSIZE_X / 2) - 300;
	//pos.y = (GROUND_Y);
	pos.x = -200;
	pos.y = +150;
}
else if (pPos == PPOS::P2)
{
	pos.x = (WINSIZE_X / 2) + 300;
	pos.y = (GROUND_Y);
}

if (FAILED(image[0].Init("Image/Ash_Image/stance_1.bmp", imageWidth, 683, maxFrame[0], 1, true, RGB(255, 255, 255))))
{
	MessageBox(g_hWnd, "Image/stance.bmp 로드 실패", "Warning", MB_OK);
	return E_FAIL;
}
if (FAILED(image[1].Init("Image/Ash_Image/walk.bmp", 6564, 683, maxFrame[1], 1, true, RGB(255, 255, 255))))
{
	MessageBox(g_hWnd, "Image/stance.bmp 로드 실패", "Warning", MB_OK);
	return E_FAIL;
}
if (FAILED(image[2].Init("Image/Ash_Image/back.bmp", 6564, 683, maxFrame[2], 1, true, RGB(255, 255, 255))))
{
	MessageBox(g_hWnd, "Image/stance.bmp 로드 실패", "Warning", MB_OK);
	return E_FAIL;
}
if (FAILED(image[3].Init("Image/Ash_Image/JJAP.bmp", 7658, 683, maxFrame[3], 1, true, RGB(255, 255, 255))))
{
	MessageBox(g_hWnd, "Image/stance.bmp 로드 실패", "Warning", MB_OK);
	return E_FAIL;
}
if (FAILED(image[4].Init("Image/Ash_Image/PUNCH.bmp", 9846, 683, maxFrame[4], 1, true, RGB(255, 255, 255))))
{
	MessageBox(g_hWnd, "Image/stance.bmp 로드 실패", "Warning", MB_OK);
	return E_FAIL;
}
if (FAILED(image[5].Init("Image/Ash_Image/LOWKICK.bmp", 6564, 683, maxFrame[5], 1, true, RGB(255, 255, 255))))
{
	MessageBox(g_hWnd, "Image/stance.bmp 로드 실패", "Warning", MB_OK);
	return E_FAIL;
}
if (FAILED(image[6].Init("Image/Ash_Image/HIGHKICK.bmp", 13128, 683, maxFrame[6], 1, true, RGB(255, 255, 255))))
{
	MessageBox(g_hWnd, "Image/stance.bmp 로드 실패", "Warning", MB_OK);
	return E_FAIL;
}
if (FAILED(image[7].Init("Image/Ash_Image/HIT.bmp", 4376, 683, maxFrame[7], 1, true, RGB(255, 255, 255))))
{
	MessageBox(g_hWnd, "Image/stance.bmp 로드 실패", "Warning", MB_OK);
	return E_FAIL;
}
if (FAILED(image[8].Init("Image/Ash_Image/DEFEAT.bmp", 12034, 683, maxFrame[8], 1, true, RGB(255, 255, 255))))
{
	MessageBox(g_hWnd, "Image/stance.bmp 로드 실패", "Warning", MB_OK);
	return E_FAIL;
}
if (FAILED(image[9].Init("Image/Ash_Image/WIN.bmp", 17504, 683, maxFrame[9], 1, true, RGB(255, 255, 255))))
{
	MessageBox(g_hWnd, "Image/stance.bmp 로드 실패", "Warning", MB_OK);
	return E_FAIL;
}
if (FAILED(image[10].Init("Image/Ash_Image/SKILL.bmp", 17504, 683, maxFrame[10], 1, true, RGB(255, 255, 255))))
{
	MessageBox(g_hWnd, "Image/stance.bmp 로드 실패", "Warning", MB_OK);
	return E_FAIL;
}
if (FAILED(image[11].Init("Image/Ash_Image/SKILL_EFFECT.bmp", 17504, 683, maxFrame[11], 1, true, RGB(0, 0, 0))))
{
	MessageBox(g_hWnd, "Image/stance.bmp 로드 실패", "Warning", MB_OK);
	return E_FAIL;
}
return S_OK;
}

void Ash::Update(STATUS status)
{
	if (pPos == PPOS::P1)
	{
		if (KeyManager::GetSingleton()->IsStayKeyDown('a') 
			|| KeyManager::GetSingleton()->IsStayKeyDown('A'))
		{
			if (frameX == 0)
				SetStatus(STATUS::BACK);
		}
		else if (KeyManager::GetSingleton()->IsStayKeyDown('d')
			|| KeyManager::GetSingleton()->IsStayKeyDown('D'))
		{
			if (frameX == 0)
				SetStatus(STATUS::WALK);
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyDown('u')
			|| KeyManager::GetSingleton()->IsOnceKeyDown('U'))
		{
			SetStatus(STATUS::JJAP);
			frameX = 0;
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyDown('i')
			|| KeyManager::GetSingleton()->IsOnceKeyDown('I'))
		{
			SetStatus(STATUS::PUNCH);
			frameX = 0;
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyDown('j')
			|| KeyManager::GetSingleton()->IsOnceKeyDown('J'))
		{
			SetStatus(STATUS::LOWKICK);
			frameX = 0;
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyDown('k')
			|| KeyManager::GetSingleton()->IsOnceKeyDown('K'))
		{
			SetStatus(STATUS::HIGHKICK);
			frameX = 0;
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyDown('p')
			|| KeyManager::GetSingleton()->IsOnceKeyDown('P'))
		{
			SetStatus(STATUS::SKILL);
			frameX = 0;
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyDown('l')
			|| KeyManager::GetSingleton()->IsOnceKeyDown('L'))
		{
			SetStatus(STATUS::HIT);
			frameX = 0;
		}

		if (frameX >= maxFrame[status])
		{
			SetStatus(STATUS::STANCE);
			frameX = 0;
		}
		else if( STATUS::STANCE < status && status < STATUS::JJAP ) 
		{
			if (KeyManager::GetSingleton()->IsOnceKeyUp(VK_LEFT)
				|| KeyManager::GetSingleton()->IsOnceKeyUp(VK_RIGHT))
			{
				SetStatus(STATUS::STANCE);
				frameX = 0;
			}
		}
		if (status == STATUS::WALK)
			pos.x += moveSpeed;
		if (status == STATUS::BACK)
			pos.x -= moveSpeed;

		if (KeyManager::GetSingleton()->IsOnceKeyDown('m')
			|| KeyManager::GetSingleton()->IsOnceKeyDown('M'))
		{
			SetStatus(STATUS::DEFEAT);
			frameX = 0;
		}
		if (KeyManager::GetSingleton()->IsOnceKeyDown('n')
			|| KeyManager::GetSingleton()->IsOnceKeyDown('N'))
		{
			SetStatus(STATUS::WIN);
			frameX = 0;
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
		if (frameX >= maxFrame[status])
		{
			SetStatus(STATUS::STANCE);
			frameX = 0;
		}
	}
	elapsedTime++;
	if (elapsedTime >= 5)
	{
		frameX++;
		elapsedTime = 0;
	}

	//if (elapsedTime >= 5 && status == STATUS::STANCE)
	//{
	//	frame++;
	//	if (frame >= maxFrame[0])
	//	{
	//		frame = 0;
	//	}
	//	elapsedTime = 0;
	//}
	//else if (elapsedTime >= 5 && status == STATUS::WALK)
	//{
	//	//앞으로 이동 시 이미지 출력되도록 UPDATE 작성
	//	{
	//		frame++;
	//		if (frame >= maxFrame[1])
	//		{
	//			frame = 0;
	//		}
	//		elapsedTime = 0;
	//		pos.x += 10;
	//	}
	//}
	//else if (elapsedTime >= 5 && status == STATUS::BACK)
	//{
	//	// 뒤로 이동 시 이미지 출력되도록 UDPATER 작성
	//	{
	//		frame++;
	//		if (frame >= maxFrame[2])
	//		{
	//			frame = 0;
	//		}
	//		elapsedTime = 0;
	//		pos.x -= 10;
	//	}
	//}
	//else if (elapsedTime >= 5 && status == STATUS::JJAP)
	//{
	//	// JJAP시 이미지 출력되도록 UDPATER 작성
	//	{
	//		frame++;
	//		if (frame >= maxFrame[3])
	//		{
	//			frame = 0;
	//		}
	//		elapsedTime = 0;
	//	}
	//}
	
}