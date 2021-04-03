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
	STANCE : ��� �ڼ�
	WALK : ������ �̵�
	BACK : �ڷ� �̵�
	JJAP : ���
	PUNCH : ����
	LOWKICK : ���
	HIGHKICK : ����
	HIT : �ǰ�
	DEFEAT : �й�� ����
	WIN : �¸����
	END : ��
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