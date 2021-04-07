#pragma once
#include "GameNode.h"

class Image;
class Character;
class MainGame : public GameNode
{
private:
	bool isInited;
	HDC hdc;
	PAINTSTRUCT ps;
	HANDLE hTimer;
	HANDLE CommandTimer;
	POINT ptMouse{ 0, 0 };
	char szText[128] = "";

	Image* backBuffer;
	Image* background;
	Image* characterSelect;
	Image* hpBarFrame_p1;
	Image* hpBar_p1;
	Image* hpBarFrame_p2;
	Image* hpBar_p2;
	Image* koImage;

	Character* player1;
	Character* player2;

	FPOINT player1SelectPos;
	FPOINT player2SelectPos;

	HPEN hPen;
	HPEN hOldPen;
	
	bool isPlayer1Chosen;
	bool isPlayer2Chosen; 
	GAMESTATUS gameStatus;


public:
	HRESULT Init();
	void Release();
	void Update();
	void UpdateCommand();
	void Render(HDC hdc);
	void RenderCharacterChoice(HDC hdc);
	void CheckCollision();
	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
	void ChooseCharacter();

	MainGame();
	~MainGame();
};