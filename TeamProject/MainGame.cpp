#include "MainGame.h"
#include "Image.h"
#include "Kdash.h"
#include "Ash.h"
#include "Kyo.h"
#include "CheckBox.h"
#include "CommandQueue.h"

/*
	1. ??? bin.bmp?? ?????? ????? ????? ?????.
	2. ????? ?????? ?????? ????.bmp?? ????????.
	3. ??????? ??? ???? ???? 1????? ???????? ????? ????
*/
#define MAIN_TIMER_ID 0
#define COMMAND_TIMER_ID 1
#define COMMAND_TIMER_CYCLE 50

HRESULT MainGame::Init()
{
	KeyManager::GetSingleton()->Init();

	count = 0;
	sizex = 68;
	sizey = 104;
	print_posx = 0;
	background = new Image();
	background->Init("Image/BackGround/background.bmp", WINSIZE_X, WINSIZE_Y);

	hTimer = (HANDLE)SetTimer(g_hWnd, MAIN_TIMER_ID, 10, NULL);
	CommandTimer = (HANDLE)SetTimer(g_hWnd, COMMAND_TIMER_ID, COMMAND_TIMER_CYCLE, NULL);

	//????? ?????
	backBuffer = new Image();
	backBuffer->Init(WINSIZE_X, WINSIZE_Y);
	isInited = true;

	characterSelect = new Image();
	characterSelect->Init("Image/BackGround/CharacterSelect.bmp", WINSIZE_X, WINSIZE_Y);

	gameStatus = GAMESTATUS::CHAR_SELECT;
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
		gameStatus = GAMESTATUS::INGAME;
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

	KillTimer(g_hWnd, MAIN_TIMER_ID);
	KillTimer(g_hWnd, COMMAND_TIMER_ID);
}

void MainGame::Update()
{
	if(gameStatus == GAMESTATUS::INGAME){
		player1->Update();
		player2->Update();
		CheckCollision();
	}
	else if (gameStatus == GAMESTATUS::CHAR_SELECT) {
		ChooseCharacter();
	}

	InvalidateRect(g_hWnd, NULL, false);
}

void MainGame::UpdateCommand()
{
	bool player1HasCommand = player1->GetKeyCache()->HasCommand("SDI", COMMAND_TIMER_CYCLE);
	bool player2HasCommand = player2->GetKeyCache()->HasCommand(string{ char{VK_DOWN} } + string{ char{VK_LEFT} } + string{ char{VK_NUMPAD6} }, COMMAND_TIMER_CYCLE);

	if (player1HasCommand && player2HasCommand) {
		//플레이어가 동시에 사용했을 때 처리
	}
	else if (player1HasCommand)
	{
		player1->SetStatus(STATUS::SKILL); 
		player1->SetFrameX(0);
	}
	else if (player2HasCommand)
	{
		player2->SetStatus(STATUS::SKILL);
		player2->SetFrameX(0);
	}
	player1->GetKeyCache()->PopInvalidElements();
	player2->GetKeyCache()->PopInvalidElements();
}

void MainGame::RenderCharacterChoice(HDC hdc) {

	HDC hBackDC = backBuffer->GetMemDC();

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

	backBuffer->Render(hdc, 0, 0, 0);
}

void MainGame::Render(HDC hdc)
{

	HDC hBackDC = backBuffer->GetMemDC();

	background->Render(hBackDC);

	// ?λ?
	TextOut(hBackDC, 20, 20, "MainGame", strlen("MainGame"));
	// ???콺 ???
	wsprintf(szText, "X : %d, Y : %d", ptMouse.x, ptMouse.y);
	TextOut(hBackDC, 200, 20, szText, strlen(szText));

	player1->Render(hBackDC);
	player2->Render(hBackDC);

	backBuffer->Render(hdc, 0, 0, 0);
}

void MainGame::CheckCollision()
{
	//TODO 버그 수정
	if (player1->GetStatus() >= STATUS::JJAP && player1->GetStatus() <= STATUS::HIGHKICK || player1->GetStatus() == STATUS::SKILL
		|| player2->GetStatus() >= STATUS::JJAP && player2->GetStatus() <= STATUS::HIGHKICK || player2->GetStatus() == STATUS::SKILL) {

		if (player1->getAttackBox()->GetRect().right >= player2->getHitBox()->GetRect().left) {
			player2->SetStatus(STATUS::HIT);
			//HP 감소
			player1->getAttackBox()->SetActivated(false);
		}
		else if (player2->getAttackBox()->GetRect().left <= player1->getHitBox()->GetRect().right) {
			player1->SetStatus(STATUS::HIT);
			player2->getAttackBox()->SetActivated(false);
		}
	}
	if (player1->getHitBox()->GetRect().right >= player2->getHitBox()->GetRect().left) {
		player1->SetTouched(true);
		player2->SetTouched(true);
	}
	else {
		player1->SetTouched(false);
		player2->SetTouched(false);
	}
}



LRESULT MainGame::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_CREATE:
		break;
	case WM_TIMER:
		if (wParam == MAIN_TIMER_ID)
		{
			if(isInited)
				this->Update();
		}
		else if (wParam == COMMAND_TIMER_ID) {
			if(gameStatus == GAMESTATUS::INGAME)
				this->UpdateCommand();
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
			if (gameStatus == GAMESTATUS::CHAR_SELECT)
				this->RenderCharacterChoice(hdc);
			else if (gameStatus == GAMESTATUS::INGAME)
				this->Render(hdc);
			else if (gameStatus == GAMESTATUS::ENDGAME)
				this->Render(hdc); //TODO 게임 종료 시 출력 사항 수정 바람
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