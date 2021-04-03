// config.h

#pragma once

#include <Windows.h>
#include <string>
#include <ctime>
#include <bitset>
#include "KeyManager.h"

using namespace std;

#define WINSIZE_X	1080
#define WINSIZE_Y	720
#define GROUND_Y	520
enum STATUS {STANCE, WALK, BACK, JJAP, PUNCH, LOWKICK, HIGHKICK, HIT, DEFEAT, WIN ,ENDSTATUS };
/*
	STANCE : 통상 자세
	WALK : 앞으로 이동
	BACK : 뒤로 이동
	JJAP : 약손
	PUNCH : 강손
	LOWKICK : 약발
	HIGHKICK : 강발
	HIT : 피격
	DEFEAT : 패배시 연출
	WIN : 승리모션
	END : 끝
*/
enum PPOS {P1, P2, ENDPPOS};
enum COMMAND{NO_COMMAND, FIRST_COMMAND};

typedef struct tagFPoint
{
	float x;
	float y;
} FPOINT, *PFPOINT;

//typedef tagFPoint FPOINT2;
//typedef tagFPoint* PFPOINT2;

extern HWND g_hWnd;
extern HINSTANCE g_hInstance;