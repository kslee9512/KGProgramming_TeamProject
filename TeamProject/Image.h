#pragma once
#include "config.h"

class Image
{
public:
	enum IMAGE_LOAD_KIND
	{
		RESOURCE,	//������Ʈ ��ü�� ���� ��ų �̹���
		FILE,		//�ܺο��� �ε��� �̹���
		EMPTY,		//��ü ���� �̹���(����ó��, ������ ��)
		END
	};

	typedef struct tagImageInfo {
		DWORD resId;		//���ҽ��� ������ ���̵�
		HDC hMemDC;			//�׸��⸦ �ְ��ϴ� �ڵ�
		HBITMAP hBitmap;	//�̹��� ����
		HBITMAP hOBitmap;	//���� �̹��� ����
		int width;			//�̹��� ���� ũ��
		int height;			//�̹��� ���� ũ��
		BYTE loadType;		//�ε� Ÿ��

		int maxFrameX;
		int maxFrameY;
		int frameWidth;
		int frameHeight;
		int curFrameX;
		int curFrameY;

		tagImageInfo()
		{
			resId = 0;
			hMemDC = NULL;
			hBitmap = NULL;
			hOBitmap = NULL;
			width = 0;
			height = 0;

			maxFrameX = 0;
			maxFrameY = 0;
			frameWidth = 0;
			frameHeight = 0;
			curFrameX = 0;
			curFrameY = 0;
			loadType = IMAGE_LOAD_KIND::EMPTY;
		}
	} IMAGE_INFO, * LPIMAGE_INFO;

private:
	//IMAGE_INFO* imageInfo; �Ʒ��� ����
	LPIMAGE_INFO imageInfo;	//�̹��� ���� ����ü ������
	bool isTransparent;
	COLORREF colorToRemove;
	PPOS pPos;

public:
	// �� ��Ʈ�� �̹����� ����� �Լ�
	HRESULT Init(int width, int height);

	// ���Ϸκ��� �̹����� �ε��ϴ� �Լ�
	HRESULT Init(const char* fileName, int width, int height, bool isTransparent = false, COLORREF colorToRemove = false);


	// ���Ϸκ��� �̹����� �ε��ϴ� �Լ�
	HRESULT Init(const char* fileName, int width, int height, int maxFrameX, int maxFrameY, bool isTransparent = false, COLORREF colorToRemove = false);

	// ȭ�鿡 ���
	void Render(HDC hdc);
	void Render(HDC hdc, int destX, int destY, int destWidth = 0, int destHeight = 0);
	/*void RenderTransparent(HDC destHdc, int destX, int destY, int destWidth, int destHeight, int frameIdx);*/

	void Update();
	void Update(int curFrameX, int curFrameY);

	void Release();

	HDC GetMemDC() {
		if (this->imageInfo)
			return this->imageInfo->hMemDC;
		return NULL;
	}
	void SetPPOS(PPOS pPos) { 
		this->pPos = pPos; 
		if (pPos == PPOS::P1) 
			imageInfo->curFrameX = imageInfo->maxFrameX - 1; 
		else 
			imageInfo->curFrameX = 0; 
	}

};

