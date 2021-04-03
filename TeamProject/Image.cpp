#include "Image.h"

HRESULT Image::Init(int width, int height)
{
	HDC hdc = GetDC(g_hWnd); // g_hWnd가 총괄하는 메인 hdc를 가져옴

	imageInfo = new IMAGE_INFO();
	imageInfo->resId = 0;
	imageInfo->hMemDC = CreateCompatibleDC(hdc);//bitmap을 관리하는 작은 DC를 만든다. 
	imageInfo->hBitmap = CreateCompatibleBitmap(hdc, width, height);//DC가 관리하는 업무
	imageInfo->hOBitmap = (HBITMAP)SelectObject(imageInfo->hMemDC, imageInfo->hBitmap);	//bBitmap 그리기 정보를 관리하기 위해 hMemDC를 선택
	imageInfo->width = width;
	imageInfo->height = height;
	imageInfo->loadType = IMAGE_LOAD_KIND::EMPTY;

	this->isTransparent = false;
	this->colorToRemove = false;

	imageInfo->maxFrameX = 1;
	imageInfo->maxFrameY = 1;
	imageInfo->frameWidth = width / 1;
	imageInfo->frameHeight = height / 1;
	imageInfo->curFrameX = 0;
	imageInfo->curFrameY = 0;

	//메모리를 참조 하지 않는다. hdc는 계속 살아있음
	ReleaseDC(g_hWnd, hdc);

	if (imageInfo->hBitmap == NULL)//hBitmap 생성 실패 시
	{
		Release();
		return E_FAIL;
	}

	return S_OK;
}

HRESULT Image::Init(const char* fileName, int width, int height, bool isTransparent, COLORREF colorToRemove)
{
	HDC hdc = GetDC(g_hWnd); // g_hWnd가 총괄하는 메인 hdc를 가져옴

	imageInfo = new IMAGE_INFO();
	imageInfo->resId = 0;
	imageInfo->hMemDC = CreateCompatibleDC(hdc);//bitmap을 관리하는 작은 DC를 만든다. 
	imageInfo->hBitmap = (HBITMAP)LoadImage(g_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);//DC가 관리하는 업무
	imageInfo->hOBitmap = (HBITMAP)SelectObject(imageInfo->hMemDC, imageInfo->hBitmap);	//bBitmap 그리기 정보를 관리하기 위해 hMemDC를 선택
	imageInfo->width = width;
	imageInfo->height = height;
	imageInfo->loadType = IMAGE_LOAD_KIND::FILE;
	this->isTransparent = isTransparent;
	this->colorToRemove = colorToRemove;

	imageInfo->maxFrameX = 1;
	imageInfo->maxFrameY = 1;
	imageInfo->frameWidth = width / 1;
	imageInfo->frameHeight = height / 1;
	imageInfo->curFrameX = 0;
	imageInfo->curFrameY = 0;
	//메모리를 참조 하지 않는다. hdc는 계속 살아있음
	ReleaseDC(g_hWnd, hdc);

	if (imageInfo->hBitmap == NULL)//hBitmap 생성 실패 시
	{
		Release();
		return E_FAIL;
	}

	return S_OK;
}

HRESULT Image::Init(const char* fileName, int width, int height, int maxFrameX, int maxFrameY, bool isTransparent, COLORREF colorToRemove)
{
	HDC hdc = GetDC(g_hWnd); // g_hWnd가 총괄하는 메인 hdc를 가져옴

	imageInfo = new IMAGE_INFO();
	imageInfo->resId = 0;
	imageInfo->hMemDC = CreateCompatibleDC(hdc);//bitmap을 관리하는 작은 DC를 만든다. 
	imageInfo->hBitmap = (HBITMAP)LoadImage(g_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);//DC가 관리하는 업무
	imageInfo->hOBitmap = (HBITMAP)SelectObject(imageInfo->hMemDC, imageInfo->hBitmap);	//bBitmap 그리기 정보를 관리하기 위해 hMemDC를 선택
	imageInfo->width = width;
	imageInfo->height = height;
	imageInfo->loadType = IMAGE_LOAD_KIND::FILE;
	this->isTransparent = isTransparent;
	this->colorToRemove = colorToRemove;

	imageInfo->maxFrameX = maxFrameX;
	imageInfo->maxFrameY = maxFrameY;
	imageInfo->frameWidth = width / maxFrameX;
	imageInfo->frameHeight = height / maxFrameY;
	imageInfo->curFrameX = 0;
	imageInfo->curFrameY = 0;

	//메모리를 참조 하지 않는다. hdc는 계속 살아있음
	ReleaseDC(g_hWnd, hdc);

	if (imageInfo->hBitmap == NULL)//hBitmap 생성 실패 시
	{
		Release();
		return E_FAIL;
	}

	return S_OK;
}

void Image::Render(HDC hdc)
{
	Render(hdc, 0, 0);
}

void Image::Render(HDC hdc, int destX, int destY, int destWidth, int destHeight)
{
	if (isTransparent)
	{
		destWidth = !destWidth ? imageInfo->width : destWidth;
		destWidth = !destWidth ? imageInfo->height : destHeight;
		GdiTransparentBlt(
			hdc,
			destX, destY,
			destWidth, destHeight,
			imageInfo->hMemDC,
			imageInfo->width / imageInfo->maxFrameX * imageInfo->curFrameX,
			imageInfo->height / imageInfo->maxFrameY * imageInfo->curFrameY,
			imageInfo->frameWidth,
			imageInfo->frameHeight,
			colorToRemove
		);
		return;
	}
	BitBlt(
		hdc,				//복사 목적지 DC
		destX, destY,		//붙여넣기 할 위치
		imageInfo->width / imageInfo->maxFrameX,			//원본에서 복사될 가로, 세로 크기
		imageInfo->height / imageInfo->maxFrameY,
		imageInfo->hMemDC,	//원본 DC
		imageInfo->width / imageInfo->maxFrameX * (imageInfo->curFrameX),
		imageInfo->height / imageInfo->maxFrameY * (imageInfo->curFrameY),		//원본에서 복사 시작 위치
		SRCCOPY				//복사 옵션
	);
}


//void Image::RenderTransparent(HDC destHdc, int destX, int destY, int destWidth, int destHeight, int frameIdx)
//{
//	TransparentBlt(
//		destHdc,
//		destX,
//		destY,
//		destWidth,
//		destHeight,
//		imageInfo->hMemDC,
//		imageInfo->width / imageInfo->frameCnt * frameIdx,
//		0,
//		imageInfo->width / imageInfo->frameCnt,
//		imageInfo->height,
//		RGB(255, 0 , 255)
//	);
//}


void Image::Update()
{
	if (imageInfo->maxFrameX > 1) {
		imageInfo->curFrameX++;
		if (imageInfo->curFrameX >= imageInfo->maxFrameX) {
			imageInfo->curFrameX = 0;
		}
		imageInfo->curFrameY++;
		if (imageInfo->curFrameY >= imageInfo->maxFrameY) {
			imageInfo->curFrameY = 0;
		}
	}
}

void Image::Update(int curFrameX, int curFrameY)
{
	imageInfo->curFrameX = 0;
	imageInfo->curFrameY = 0;
}

void Image::Release()
{
	if (imageInfo) {
		SelectObject(imageInfo->hMemDC, imageInfo->hOBitmap);
		DeleteObject(imageInfo->hBitmap);
		DeleteDC(imageInfo->hMemDC);

		delete imageInfo;
		imageInfo = nullptr;
	}
}
