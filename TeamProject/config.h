
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
<<<<<<< HEAD
#define GROUND_Y	520
enum STATUS {STANCE, WALK, BACK, JJAP, PUNCH, LOWKICK, HIGHKICK, HIT, DEFEAT, WIN , SKILL, ENDSTATUS };
=======
#define GROUND_Y	120
enum STATUS {STANCE, WALK, BACK, JJAP, PUNCH, LOWKICK, HIGHKICK, HIT, SKILL, DEFEAT, WIN ,ENDSTATUS };
>>>>>>> origin/SES
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
<<<<<<< HEAD
enum PPOS { P1, P2, ENDPPOS };
=======
enum PPOS {P1, P2, ENDPPOS};
enum COMMAND{NO_COMMAND, FIRST_COMMAND};
>>>>>>> origin/SES

typedef struct tagFPoint
{
	float x;
	float y;
} FPOINT, * PFPOINT;

//typedef tagFPoint FPOINT2;
//typedef tagFPoint* PFPOINT2;

<<<<<<< HEAD

=======
>>>>>>> origin/SES
extern HWND g_hWnd;
extern HINSTANCE g_hInstance;