#include "Image.h"

HRESULT Image::Init(int width, int height)
{
	HDC hdc = GetDC(g_hWnd);

	imageInfo = new IMAGE_INFO();
	imageInfo->resId = 0;
	imageInfo->hMemDC = CreateCompatibleDC(hdc);
	imageInfo->hBitmap = CreateCompatibleBitmap(hdc, width, height);
	imageInfo->hOBitmap = (HBITMAP)SelectObject(imageInfo->hMemDC, imageInfo->hBitmap);
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


	ReleaseDC(g_hWnd, hdc);

	if (imageInfo->hBitmap == NULL)//hBitmap ???? ???? ??
	{
		Release();
		return E_FAIL;
	}

	return S_OK;
}

HRESULT Image::Init(const char* fileName, int width, int height, bool isTransparent, COLORREF colorToRemove)
{
	HDC hdc = GetDC(g_hWnd); // g_hWnd?? ?????? ???? hdc?? ??????

	imageInfo = new IMAGE_INFO();
	imageInfo->resId = 0;
	imageInfo->hMemDC = CreateCompatibleDC(hdc);//bitmap?? ??????? ???? DC?? ?????. 
	imageInfo->hBitmap = (HBITMAP)LoadImage(g_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);//DC?? ??????? ????
	imageInfo->hOBitmap = (HBITMAP)SelectObject(imageInfo->hMemDC, imageInfo->hBitmap);	//bBitmap ????? ?????? ??????? ???? hMemDC?? ????
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
	//????? ???? ???? ??ве?. hdc?? ??? ???????
	ReleaseDC(g_hWnd, hdc);

	if (imageInfo->hBitmap == NULL)//hBitmap ???? ???? ??
	{
		Release();
		return E_FAIL;
	}

	return S_OK;
}

HRESULT Image::Init(const char* fileName, int width, int height, int maxFrameX, int maxFrameY, bool isTransparent, COLORREF colorToRemove)
{
	HDC hdc = GetDC(g_hWnd); // g_hWnd?? ?????? ???? hdc?? ??????

	imageInfo = new IMAGE_INFO();
	imageInfo->resId = 0;
	imageInfo->hMemDC = CreateCompatibleDC(hdc);//bitmap?? ??????? ???? DC?? ?????.
	imageInfo->hMemDC2 = CreateCompatibleDC(hdc);
	imageInfo->hBitmap = CreateCompatibleBitmap(hdc, width, height);
	imageInfo->hBitmap2 = (HBITMAP)LoadImage(g_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);//DC?? ??????? ????
	imageInfo->hOBitmap = (HBITMAP)SelectObject(imageInfo->hMemDC, imageInfo->hBitmap);	//bBitmap ????? ?????? ??????? ???? hMemDC?? ????
	imageInfo->hOBitmap2 = (HBITMAP)SelectObject(imageInfo->hMemDC2, imageInfo->hBitmap2);	//bBitmap ????? ?????? ??????? ???? hMemDC?? ????
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
	//????? ???? ???? ??ве?. hdc?? ??? ???????
	ReleaseDC(g_hWnd, hdc);

	if (imageInfo->hBitmap == NULL)//hBitmap ???? ???? ??
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
		destHeight = !destHeight ? imageInfo->height : destHeight;
		GdiTransparentBlt(
			hdc,
			destX, destY,
			destWidth, destHeight,
			imageInfo->hMemDC2,
			imageInfo->width / imageInfo->maxFrameX * imageInfo->curFrameX,
			imageInfo->height / imageInfo->maxFrameY * imageInfo->curFrameY,
			imageInfo->frameWidth,
			imageInfo->frameHeight,
			colorToRemove
		);
		return;
	}
	BitBlt(
		hdc,				//???? ?????? DC
		destX, destY,		//?????? ?? ???
		imageInfo->width / imageInfo->maxFrameX,			//???????? ????? ????, ???? ???
		imageInfo->height / imageInfo->maxFrameY,
		imageInfo->hMemDC,	//???? DC
		imageInfo->width / imageInfo->maxFrameX * (imageInfo->curFrameX),
		imageInfo->height / imageInfo->maxFrameY * (imageInfo->curFrameY),		//???????? ???? ???? ???
		SRCCOPY				//???? ???
	);
}

void Image::RenderReverse(HDC hdc, int destX, int destY, int destWidth, int destHeight)
{
	if (isTransparent)
	{
		destWidth = !destWidth ? imageInfo->width : destWidth;
		destHeight = !destHeight ? imageInfo->height : destHeight;
		StretchBlt(
			imageInfo->hMemDC,
			destWidth - 1, 0,
			-destWidth, destHeight,
			imageInfo->hMemDC2,
			imageInfo->width / imageInfo->maxFrameX * (imageInfo->curFrameX),
			imageInfo->height / imageInfo->maxFrameY * imageInfo->curFrameY,
			imageInfo->frameWidth,
			imageInfo->frameHeight,
			SRCCOPY
		);
		GdiTransparentBlt(
			hdc,
			destX, destY,
			destWidth, destHeight,
			imageInfo->hMemDC,
			0,
			imageInfo->height / imageInfo->maxFrameY * imageInfo->curFrameY,
			imageInfo->frameWidth,
			imageInfo->frameHeight,
			colorToRemove
		);
		return;
	}

	StretchBlt(
		hdc,
		(destX + destWidth) - 1, destY,
		-destWidth, destHeight,
		imageInfo->hMemDC,
		imageInfo->width / imageInfo->maxFrameX * (imageInfo->curFrameX),
		imageInfo->height / imageInfo->maxFrameY * imageInfo->curFrameY,
		imageInfo->frameWidth,
		imageInfo->frameHeight,
		SRCCOPY
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
	imageInfo->curFrameX++;
	if (imageInfo->curFrameX >= imageInfo->maxFrameX) {
		imageInfo->curFrameX = 0;
	}
	imageInfo->curFrameY++;
	if (imageInfo->curFrameY >= imageInfo->maxFrameY) {
		imageInfo->curFrameY = 0;
	}
}


void Image::Update(int frameX, int frameY)
{
	imageInfo->curFrameX = frameX;
	imageInfo->curFrameY = frameY;
}

void Image::Release()
{
	if (imageInfo) {
		SelectObject(imageInfo->hMemDC, imageInfo->hOBitmap);
		SelectObject(imageInfo->hMemDC2, imageInfo->hOBitmap2);
		DeleteObject(imageInfo->hBitmap);
		DeleteObject(imageInfo->hBitmap2);
		DeleteDC(imageInfo->hMemDC);
		DeleteDC(imageInfo->hMemDC2);

		delete imageInfo;
		imageInfo = nullptr;
	}
}
