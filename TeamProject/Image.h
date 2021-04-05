#pragma once
#include "config.h"

class Image
{
public:
	enum IMAGE_LOAD_KIND
	{
		RESOURCE,	//프로젝트 자체에 포함 시킬 이미지
		FILE,		//외부에서 로드할 이미지
		EMPTY,		//자체 생산 이미지(투명처리, 색조합 등)
		END
	};

<<<<<<< HEAD
	//typedef struct tagImageInfo
	//{
	//	DWORD resID;	// 리소스의 고유한 ID
	//	HDC hMemDC;		// 그리기를 주관하는 핸들
	//	HBITMAP hBitmap; // 이미지 정보
	//	HBITMAP hOldBit; // 기존 이미지 정보
	//	int width;		// 이미지 가로 크기
	//	int height;		// 이미지 세로 크기
	//	BYTE loadType;	// 로드 타입

	//	//애니메이션 관련 (프레임데이터)
	//	int maxFrameX;
	//	int maxFrameY;
	//	int frameWidth;
	//	int frameHeight;
	//	int currFrameX;
	//	int currFrameY;

	//	tagImageInfo()
	//	{
	//		resID = 0;
	//		hMemDC = NULL;
	//		hBitmap = NULL;
	//		hOldBit = NULL;
	//		width = 0;
	//		height = 0;
	//		loadType = IMAGE_LOAD_KIND::EMPTY;

	//		maxFrameX = 0;
	//		maxFrameY = 0;
	//		frameWidth = 0;
	//		frameHeight = 0;
	//		currFrameX = 0;
	//		currFrameY = 0;
	//	};
	//} IMAGE_INFO, * LPIMAGE_INFO;
	typedef struct tagImageInfo {
		DWORD resId;        //리소스의 고유한 아이디
		HDC hMemDC;            //그리기를 주관하는 핸들
		HDC hMemDC2;
		HBITMAP hBitmap;    //이미지 정보
		HBITMAP hBitmap2;    //이미지 정보
		HBITMAP hOBitmap;    //기존 이미지 정보
		HBITMAP hOBitmap2;    //기존 이미지 정보
		int width;            //이미지 가로 크기
		int height;            //이미지 세로 크기
		BYTE loadType;        //로드 타입
=======
	typedef struct tagImageInfo {
		DWORD resId;		//리소스의 고유한 아이디
		HDC hMemDC;			//그리기를 주관하는 핸들
		HDC hMemDC2;
		HBITMAP hBitmap;	//이미지 정보
		HBITMAP hBitmap2;	//이미지 정보
		HBITMAP hOBitmap;	//기존 이미지 정보
		HBITMAP hOBitmap2;	//기존 이미지 정보
		int width;			//이미지 가로 크기
		int height;			//이미지 세로 크기
		BYTE loadType;		//로드 타입

>>>>>>> origin/SES
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
			hMemDC2 = NULL;
			hBitmap = NULL;
			hBitmap2 = NULL;
			hOBitmap = NULL;
			hOBitmap2 = NULL;
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
	//IMAGE_INFO* imageInfo; 아래와 같다
	LPIMAGE_INFO imageInfo;	//이미지 정보 구조체 포인터
	bool isTransparent;
	COLORREF colorToRemove;
	PPOS pPos;

public:
	// 빈 비트맵 이미지를 만드는 함수
	HRESULT Init(int width, int height);

	// 파일로부터 이미지를 로드하는 함수
	HRESULT Init(const char* fileName, int width, int height, bool isTransparent = false, COLORREF colorToRemove = false);

<<<<<<< HEAD
	// 파일로부터 이미지를 로드하는 함수
	HRESULT Init(const char* fileName, int width, int height, int maxFrameX, int maxFrameY, PPOS pPos, bool isTransparent = false, COLORREF colorToRemove = false);

	// 화면에 출력
	void Render(HDC hdc);
	void Render(HDC hdc, int destX, int destY, int destWidth = 0, int destHeight = 0);
	void RenderReverse(HDC hdc, int destX, int destY, int destWidth = 0, int destHeight = 0);

	void Update();
	void Update(int frameX, int frameY);

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

	void Release();
	void Render(HDC hdc, int x, int y, int frameIndex);
	//get, set
	HDC GetMemDC() { if (this->imageInfo) return this->imageInfo->hMemDC; return NULL; }
	void Render(HDC hdc, int destX, int destY, int destW, int destH, int copyX, int copyY, int copyW, int copyH, int frameIndex);

};
=======

	// 파일로부터 이미지를 로드하는 함수
	HRESULT Init(const char* fileName, int width, int height, int maxFrameX, int maxFrameY, PPOS pPos, bool isTransparent = false, COLORREF colorToRemove = false);

	// 화면에 출력
	void Render(HDC hdc);
	void Render(HDC hdc, int destX, int destY, int destWidth = 0, int destHeight = 0);
	void RenderReverse(HDC hdc, int destX, int destY, int destWidth = 0, int destHeight = 0);

	void Update();
	void Update(int frameX, int frameY);

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

>>>>>>> origin/SES
