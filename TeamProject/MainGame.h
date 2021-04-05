#pragma once
#include "GameNode.h"

class Image;
class Character;
class MainGame : public GameNode
{
private:
	bool isInited;
	int count = 0;
	int sizex = 68;
	int sizey = 104;
	int print_posx = 0;
	HDC hdc;
	PAINTSTRUCT ps;
	HANDLE hTimer;
	POINT ptMouse{ 0, 0 };
	char szText[128] = "";

	Image* backBuffer;
	Image* background;
	Image* characterSelect;

	Character* player1;
	Character* player2;

	FPOINT player1SelectPos;
	FPOINT player2SelectPos;
	HPEN hPen;
	HPEN hOldPen;
	
	bool isPlayer1Chosen;
	bool isPlayer2Chosen;
	bool isCharChosen;

public:
	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);
	void RenderCharacterChoice(HDC hdc);
	void CheckCollision();
	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
	void ChooseCharacter();

	MainGame();
	~MainGame();
};