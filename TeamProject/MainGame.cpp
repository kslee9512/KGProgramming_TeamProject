#include "MainGame.h"
#include "Image.h"
<<<<<<< HEAD
#include "Kdash.h"
#include "Ash.h"
=======
#include "Kyo.h"
>>>>>>> origin/SES
/*
	1. ��� bin.bmp�� ������ ���ϴ� ���Ϸ� �ٲ㺸��.
	2. ��ũ�� �߻��ϴ� �̻��Ͽ� ����.bmp�� ��������.
	3. �̿����� ȭ�� �ϴܿ� ���� 1�ʸ��� �������� �ٲ�� ����
*/

HRESULT MainGame::Init()
{
	KeyManager::GetSingleton()->Init();

	player1 = new Ash;
	player1->Init(PPOS::P1);

	count = 0;
	sizex = 68;
	sizey = 104;
	print_posx = 0;
	background = new Image();
	background->Init("Image/BackGround/background.bmp", WINSIZE_X, WINSIZE_Y);
<<<<<<< HEAD
	player1 = new Kdash();
	player1->Init(PPOS::P1);
	player2 = new Kdash();
=======
	player1 = new Kyo();
	player1->Init(PPOS::P1);
	player2 = new Kyo();
>>>>>>> origin/SES
	player2->Init(PPOS::P2);
	// ���ΰ����� �ʱ�ȭ �Լ�
	hTimer = (HANDLE)SetTimer(g_hWnd, 0, 10, NULL);

	//����� �̹���
	backBuffer = new Image();
	backBuffer->Init(WINSIZE_X, WINSIZE_Y);
	isInited = true;

	return S_OK;
}

void MainGame::Release()
{
	KeyManager::GetSingleton()->Release();

	if (player1) {
		player1->Release();
		delete player1;
		player1 = nullptr;
	}
	if (player2) {
		player2->Release();
		delete player2;
		player2 = nullptr;
	}
	background->Release();
	delete background;
	background = nullptr;

	backBuffer->Release();
	delete backBuffer;
	backBuffer = nullptr;

	KillTimer(g_hWnd, 0);
}

void MainGame::Update()
{
	player1->Update();
	player2->Update();
<<<<<<< HEAD

=======
>>>>>>> origin/SES
	InvalidateRect(g_hWnd, NULL, false);
}

void MainGame::Render(HDC hdc)
{

	HDC hBackDC = backBuffer->GetMemDC();
	background->Render(hBackDC);

	// �λ�
	TextOut(hBackDC, 20, 20, "MainGame ���� ��", strlen("MainGame ���� ��"));
	// ���콺 ��ǥ
	wsprintf(szText, "X : %d, Y : %d", ptMouse.x, ptMouse.y);
	TextOut(hBackDC, 200, 20, szText, strlen(szText));

	player1->Render(hBackDC);
	player2->Render(hBackDC);
<<<<<<< HEAD
=======

>>>>>>> origin/SES
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
		ptMouse.x = LOWORD(lParam);
		ptMouse.y = HIWORD(lParam);
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