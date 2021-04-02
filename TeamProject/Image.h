#pragma once
#include "config.h"

class Image
{
public:
	enum IMAGE_LOAD_KIND
	{
		RESOURCE,		// ������Ʈ ��ü�� ���� ��ų �̹���
		FILE,			// �ܺο��� �ε��� �̹���
		EMPTY,			// ��ü ���� �̹���
		END
	};

	typedef struct tagImageInfo
	{
		DWORD resID;	// ���ҽ��� ������ ID
		HDC hMemDC;		// �׸��⸦ �ְ��ϴ� �ڵ�
		HBITMAP hBitmap; // �̹��� ����
		HBITMAP hOldBit; // ���� �̹��� ����
		int width;		// �̹��� ���� ũ��
		int height;		// �̹��� ���� ũ��
		BYTE loadType;	// �ε� Ÿ��

		//�ִϸ��̼� ���� (�����ӵ�����)
		int maxFrameX;
		int maxFrameY;
		int frameWidth;
		int frameHeight;
		int currFrameX;
		int currFrameY;

		tagImageInfo()
		{
			resID = 0;
			hMemDC = NULL;
			hBitmap = NULL;
			hOldBit = NULL;
			width = 0;
			height = 0;
			loadType = IMAGE_LOAD_KIND::EMPTY;

			maxFrameX = 0;
			maxFrameY = 0;
			frameWidth = 0;
			frameHeight = 0;
			currFrameX = 0;
			currFrameY = 0;
		};
	} IMAGE_INFO, * LPIMAGE_INFO;

private:
	IMAGE_INFO* imageInfo; // �̹��� ���� ����ü ������
	//LPIMAGE_INFO imageInfo; �̹��� ���� ����ü ������
	bool isTransparent;
	COLORREF transColor;

public:
	// �� ��Ʈ�� �̹����� ����� �Լ�
	HRESULT Init(int width, int height, bool isTransparent = FALSE, COLORREF transColor = FALSE);

	HRESULT Init(const char* fileName, int width, int height, bool isTransparent, COLORREF transColor);

	//���Ϸκ��� �̹����� �ҷ����� �Լ�
	HRESULT Init(const char* fileName, int width, int height, int maxFrameX, int maxFrameY,
		bool isTransparent, COLORREF transColor);
	void Release();
	void Render(HDC hdc, int x, int y, int frameIndex);
	//get, set
	HDC GetMemDC() { if (this->imageInfo) return this->imageInfo->hMemDC; return NULL; }
	void Render(HDC hdc, int destX, int destY, int destW, int destH, int copyX, int copyY, int copyW, int copyH, int frameIndex);


};
