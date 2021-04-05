#include "MainGame.h"
#include "Image.h"
#include "Kdash.h"
#include "Ash.h"
#include "Kyo.h"

/*
	1. ??? bin.bmp?? ?????? ????? ????? ?????.
	2. ????? ?????? ?????? ????.bmp?? ????????.
	3. ??????? ??? ???? ???? 1????? ???????? ????? ????
*/

HRESULT MainGame::Init()
{
	KeyManager::GetSingleton()->Init();

	count = 0;
	sizex = 68;
	sizey = 104;
	print_posx = 0;
	background = new Image();
	background->Init("Image/BackGround/background.bmp", WINSIZE_X, WINSIZE_Y);

	hTimer = (HANDLE)SetTimer(g_hWnd, 0, 10, NULL);

	//????? ?????
	backBuffer = new Image();
	backBuffer->Init(WINSIZE_X, WINSIZE_Y);
	isInited = true;

	characterSelect = new Image();
	characterSelect->Init("Image/BackGround/CharacterSelect.bmp", WINSIZE_X, WINSIZE_Y);

	isCharChosen = false;
	isPlayer1Chosen = false;
	isPlayer2Chosen = false;
	player1SelectPos.x = 55;
	player1SelectPos.y = 100;
	player2SelectPos.x = 50;
	player2SelectPos.y = 95;

	return S_OK;
}

void MainGame::ChooseCharacter()
{
	if (KeyManager::GetSingleton()->IsOnceKeyDown('A')) {
		if (player1SelectPos.x > 100 && !isPlayer1Chosen)
			player1SelectPos.x -= 360;
	}
	else if (KeyManager::GetSingleton()->IsOnceKeyDown('D')) {
		if (player1SelectPos.x < 700 && !isPlayer1Chosen)
			player1SelectPos.x += 360;
	}
	else if (KeyManager::GetSingleton()->IsOnceKeyDown('U')) {
		isPlayer1Chosen = !isPlayer1Chosen;
	}
	else if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_LEFT)) {
		if (player2SelectPos.x > 100 && !isPlayer2Chosen)
			player2SelectPos.x -= 360;
	}
	else if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_RIGHT)) {
		if (player2SelectPos.x < 700 && !isPlayer2Chosen)
			player2SelectPos.x += 360;
	}
	else if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_NUMPAD5)) {
		isPlayer2Chosen = !isPlayer2Chosen;
	}

	if (isPlayer1Chosen && isPlayer2Chosen) {
		if (player1SelectPos.x < 100) {
			player1 = new Kyo();
		}
		else if (player1SelectPos.x < 500) {
			player1 = new Ash();
		}
		else {
			player1 = new Kdash();
		}

		if (player2SelectPos.x < 100) {
			player2 = new Kyo();
		}
		else if (player2SelectPos.x < 500) {
			player2 = new Ash();
		}
		else {
			player2 = new Kdash();
		}
		player1->Init(PPOS::P1);
		player2->Init(PPOS::P2);
		isCharChosen = true;
	}
}

void MainGame::Release()
{
	KeyManager::GetSingleton()->Release();
	if (characterSelect) {
		characterSelect->Release();
		delete characterSelect;
		characterSelect = nullptr;
	}
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
	if(isCharChosen){
		player1->Update();
		player2->Update();
	}
	else {
		ChooseCharacter();
	}

	InvalidateRect(g_hWnd, NULL, false);
}

void MainGame::RenderCharacterChoice(HDC hBackDC) {
	characterSelect->Render(hBackDC);
	//임시 좌표
	wsprintf(szText, "X : %d, Y : %d", ptMouse.x, ptMouse.y);
	TextOut(hBackDC, 200, 20, szText, strlen(szText));

	SetBkMode(hBackDC, 1);

	//player1 선택박스
	hPen = CreatePen(PS_SOLID, 5, RGB(0, 255, 0));
	hOldPen = (HPEN)SelectObject(hBackDC, hPen);
	SetTextColor(hBackDC, RGB(0, 255, 0));
	if (!isPlayer1Chosen) {
		wsprintf(szText, "Player1");
	}
	else {
		wsprintf(szText, "[#Player1]");
	}
	TextOut(hBackDC, player1SelectPos.x, player1SelectPos.y - 40, szText, strlen(szText));
	MoveToEx(hBackDC, player1SelectPos.x, player1SelectPos.y, NULL);
	LineTo(hBackDC, player1SelectPos.x + 255, player1SelectPos.y);
	LineTo(hBackDC, player1SelectPos.x + 255, player1SelectPos.y + 500);
	LineTo(hBackDC, player1SelectPos.x, player1SelectPos.y + 500);
	LineTo(hBackDC, player1SelectPos.x, player1SelectPos.y);
	SelectObject(hBackDC, hOldPen);
	DeleteObject(hPen);

	//player2 선택박스
	hPen = CreatePen(PS_SOLID, 5, RGB(0, 0, 255));
	hOldPen = (HPEN)SelectObject(hBackDC, hPen);
	SetTextColor(hBackDC, RGB(0, 0, 255));
	if (!isPlayer2Chosen) {
		wsprintf(szText, "Player2");
	}
	else {
		wsprintf(szText, "[#Player2]");
	}
	TextOut(hBackDC, player2SelectPos.x + 200, player2SelectPos.y - 35, szText, strlen(szText));
	
	MoveToEx(hBackDC, player2SelectPos.x, player2SelectPos.y, NULL);
	LineTo(hBackDC, player2SelectPos.x + 265, player2SelectPos.y);
	LineTo(hBackDC, player2SelectPos.x + 265, player2SelectPos.y + 510);
	LineTo(hBackDC, player2SelectPos.x, player2SelectPos.y + 510);
	LineTo(hBackDC, player2SelectPos.x, player2SelectPos.y);
	SelectObject(hBackDC, hOldPen);
	DeleteObject(hPen);
}

void MainGame::Render(HDC hdc)
{

	HDC hBackDC = backBuffer->GetMemDC();

	if (!isCharChosen) {
		RenderCharacterChoice(hBackDC);
		
	}
	else {
		background->Render(hBackDC);

		// ?λ?
		TextOut(hBackDC, 20, 20, "MainGame", strlen("MainGame"));
		// ???콺 ???
		wsprintf(szText, "X : %d, Y : %d", ptMouse.x, ptMouse.y);
		TextOut(hBackDC, 200, 20, szText, strlen(szText));

		player1->Render(hBackDC);
		player2->Render(hBackDC);
	}

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