#include "MainGame.h"
#include "Image.h"
#include "Character.h"
/*
	1. 배경 bin.bmp를 본인이 원하는 파일로 바꿔보자.
	2. 탱크가 발사하는 미사일에 구슬.bmp를 씌워보자.
	3. 이오리를 화면 하단에 띄우고 1초마다 프레임이 바뀌도록 설정
*/

HRESULT MainGame::Init()
{
	KeyManager::GetSingleton()->Init();

	count = 0;
	sizex = 68;
	sizey = 104;
	print_posx = 0;
	background = new Image();
	background->Init("Image/BackGround/background.bmp", WINSIZE_X, WINSIZE_Y, NULL, NULL);
	// 메인게임의 초기화 함수
	hTimer = (HANDLE)SetTimer(g_hWnd, 0, 10, NULL);

	//백버퍼 이미지
	backBuffer = new Image();
	backBuffer->Init(WINSIZE_X, WINSIZE_Y);
	isInited = true;

	return S_OK;
}

void MainGame::Release()
{
	KeyManager::GetSingleton()->Release();

	backBuffer->Release();
	delete backBuffer;
	backBuffer = nullptr;

	background->Release();
	delete background;
	background = nullptr;

	KillTimer(g_hWnd, 0);
}

void MainGame::Update()
{
	InvalidateRect(g_hWnd, NULL, false);
}

void MainGame::Render(HDC hdc)
{

	HDC hBackDC = backBuffer->GetMemDC();
	background->Render(hBackDC,0, 0, 0 );

	// 인사
	TextOut(hBackDC, 20, 20, "MainGame 렌더 중", strlen("MainGame 렌더 중"));
	// 마우스 좌표
	wsprintf(szText, "X : %d, Y : %d", ptMouse.x, ptMouse.y);
	TextOut(hBackDC, 200, 20, szText, strlen(szText));

	backBuffer->Render(hdc, 0, 0, 0);
}

void MainGame::CheckCollision()
{
	
}


LRESULT MainGame::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_CREATE:
		break;
	case WM_TIMER:
		if (isInited)
		{
			this->Update();
		}
		break;
	case WM_LBUTTONDOWN:
		break;
	case WM_LBUTTONUP:
		break;
	case WM_RBUTTONDOWN:
		break;
	case WM_MOUSEMOVE:
		break;
	case WM_PAINT:
		hdc = BeginPaint(g_hWnd, &ps);

		if (isInited)
		{
			this->Render(hdc);
		}

		EndPaint(g_hWnd, &ps);

		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}

MainGame::MainGame()
{
	isInited = false;
}

MainGame::~MainGame()
{
}
