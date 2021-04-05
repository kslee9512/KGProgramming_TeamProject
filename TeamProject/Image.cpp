#include "Image.h"

HRESULT Image::Init(int width, int height)
{
<<<<<<< HEAD
    HDC hdc = GetDC(g_hWnd);
    
    imageInfo = new IMAGE_INFO();
    imageInfo->resId = 0;
    imageInfo->hMemDC = CreateCompatibleDC(hdc); // hMemDC에서 Mem은 Memory를 의미
    imageInfo->hBitmap = CreateCompatibleBitmap(hdc, width, height);
    imageInfo->hOBitmap = (HBITMAP)SelectObject(imageInfo->hMemDC, imageInfo->hBitmap);
    imageInfo->width = width;
    imageInfo->height = height;
    imageInfo->loadType = IMAGE_LOAD_KIND::EMPTY;
    
    ReleaseDC(g_hWnd, hdc);

    if (imageInfo->hBitmap == NULL)
    {
        Release();
        return E_FAIL;
    }

    this->isTransparent = isTransparent;
    this->colorToRemove = transColor;

    return S_OK;
=======
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
>>>>>>> origin/SES
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
<<<<<<< HEAD

	imageInfo->maxFrameX = 1;
	imageInfo->maxFrameY = 1;
	imageInfo->frameWidth = width / 1;
	imageInfo->frameHeight = height / 1;
=======

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

HRESULT Image::Init(const char* fileName, int width, int height, int maxFrameX, int maxFrameY, PPOS pPos, bool isTransparent, COLORREF colorToRemove)
{
	HDC hdc = GetDC(g_hWnd); // g_hWnd가 총괄하는 메인 hdc를 가져옴

	imageInfo = new IMAGE_INFO();
	imageInfo->resId = 0;
	imageInfo->hMemDC = CreateCompatibleDC(hdc);//bitmap을 관리하는 작은 DC를 만든다.
	imageInfo->hMemDC2 = CreateCompatibleDC(hdc);
	imageInfo->hBitmap = CreateCompatibleBitmap(hdc, width, height);
	imageInfo->hBitmap2 = (HBITMAP)LoadImage(g_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);//DC가 관리하는 업무
	imageInfo->hOBitmap = (HBITMAP)SelectObject(imageInfo->hMemDC, imageInfo->hBitmap);	//bBitmap 그리기 정보를 관리하기 위해 hMemDC를 선택
	imageInfo->hOBitmap2 = (HBITMAP)SelectObject(imageInfo->hMemDC2, imageInfo->hBitmap2);	//bBitmap 그리기 정보를 관리하기 위해 hMemDC를 선택
	imageInfo->width = width;
	imageInfo->height = height;
	imageInfo->loadType = IMAGE_LOAD_KIND::FILE;
	this->isTransparent = isTransparent;
	this->colorToRemove = colorToRemove;

	imageInfo->maxFrameX = maxFrameX;
	imageInfo->maxFrameY = maxFrameY;
	imageInfo->frameWidth = width / maxFrameX;
	imageInfo->frameHeight = height / maxFrameY;
>>>>>>> origin/SES
	imageInfo->curFrameX = 0;
	imageInfo->curFrameY = 0;
	//메모리를 참조 하지 않는다. hdc는 계속 살아있음
	ReleaseDC(g_hWnd, hdc);
<<<<<<< HEAD

	if (imageInfo->hBitmap == NULL)//hBitmap 생성 실패 시
	{
		Release();
		return E_FAIL;
	}

	return S_OK;
}

HRESULT Image::Init(const char* fileName, int width, int height, int maxFrameX, int maxFrameY, PPOS pPos, bool isTransparent, COLORREF colorToRemove)
{
	HDC hdc = GetDC(g_hWnd); // g_hWnd가 총괄하는 메인 hdc를 가져옴

	imageInfo = new IMAGE_INFO();
	imageInfo->resId = 0;
	imageInfo->hMemDC = CreateCompatibleDC(hdc);//bitmap을 관리하는 작은 DC를 만든다.
	imageInfo->hMemDC2 = CreateCompatibleDC(hdc);
	imageInfo->hBitmap = CreateCompatibleBitmap(hdc, width, height);
	imageInfo->hBitmap2 = (HBITMAP)LoadImage(g_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);//DC가 관리하는 업무
	imageInfo->hOBitmap = (HBITMAP)SelectObject(imageInfo->hMemDC, imageInfo->hBitmap);	//bBitmap 그리기 정보를 관리하기 위해 hMemDC를 선택
	imageInfo->hOBitmap2 = (HBITMAP)SelectObject(imageInfo->hMemDC2, imageInfo->hBitmap2);	//bBitmap 그리기 정보를 관리하기 위해 hMemDC를 선택
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

void Image::RenderReverse(HDC hdc, int destX, int destY, int destWidth, int destHeight)
{
	if (isTransparent)
	{
		destWidth = !destWidth ? imageInfo->width : destWidth;
		destWidth = !destWidth ? imageInfo->height : destHeight;
		StretchBlt(
			imageInfo->hMemDC,
			destWidth, 0,
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
		destX + destWidth, destY,
		-destWidth, destHeight,
		imageInfo->hMemDC,
		imageInfo->width / imageInfo->maxFrameX * (imageInfo->curFrameX),
		imageInfo->height / imageInfo->maxFrameY * imageInfo->curFrameY,
		imageInfo->frameWidth,
		imageInfo->frameHeight,
		SRCCOPY
	);
}


void Image::Update()
{
=======

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

void Image::RenderReverse(HDC hdc, int destX, int destY, int destWidth, int destHeight)
{
	if (isTransparent)
	{
		destWidth = !destWidth ? imageInfo->width : destWidth;
		destWidth = !destWidth ? imageInfo->height : destHeight;
		StretchBlt(
			imageInfo->hMemDC,
			destWidth, 0,
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
		destX + destWidth, destY,
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
>>>>>>> origin/SES
	imageInfo->curFrameX++;
	if (imageInfo->curFrameX >= imageInfo->maxFrameX) {
		imageInfo->curFrameX = 0;
	}
	imageInfo->curFrameY++;
	if (imageInfo->curFrameY >= imageInfo->maxFrameY) {
		imageInfo->curFrameY = 0;
	}
<<<<<<< HEAD
}

HRESULT Image::Init(const char* fileName, int width, int height, int maxFrameX, int maxFrameY, PPOS pPos, bool isTransparent, COLORREF colorToRemove)
{
    HDC hdc = GetDC(g_hWnd); // g_hWnd가 총괄하는 메인 hdc를 가져옴

    imageInfo = new IMAGE_INFO();
    imageInfo->resId = 0;
    imageInfo->hMemDC = CreateCompatibleDC(hdc);//bitmap을 관리하는 작은 DC를 만든다.
    imageInfo->hMemDC2 = CreateCompatibleDC(hdc);
    imageInfo->hBitmap = CreateCompatibleBitmap(hdc, width, height);
    imageInfo->hBitmap2 = (HBITMAP)LoadImage(g_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);//DC가 관리하는 업무
    imageInfo->hOBitmap = (HBITMAP)SelectObject(imageInfo->hMemDC, imageInfo->hBitmap);    //bBitmap 그리기 정보를 관리하기 위해 hMemDC를 선택
    imageInfo->hOBitmap2 = (HBITMAP)SelectObject(imageInfo->hMemDC2, imageInfo->hBitmap2);    //bBitmap 그리기 정보를 관리하기 위해 hMemDC를 선택
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
=======

>>>>>>> origin/SES
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
<<<<<<< HEAD
   // imageInfo->hBitmap;
    imageInfo->curFrameX = frameIndex;
    if (isTransparent)
    {
        //특정색상제거
        GdiTransparentBlt(
            hdc,    //목적지 DC
            x, y,   //복사 위치
            imageInfo->frameWidth, imageInfo->frameHeight, //복사 크기
            imageInfo->hMemDC, // 원본 DC
            imageInfo->frameWidth * imageInfo->curFrameX, // 복사 x위치 
            imageInfo->frameWidth * imageInfo->curFrameY, // 복사 y위치
            imageInfo->frameWidth, imageInfo->frameHeight, // 복사 크기
            colorToRemove
        );
    }
    else
    {
        BitBlt(
            hdc,        //목적지 DC
            x, y,       // 복사 시작 위치(좌표)
            imageInfo->width,   // 복사되는 원본의 크기
            imageInfo->height,  // 복사되는 원본의 크기
            imageInfo->hMemDC,  // 복사되는 원본 DC
            0, 0,       // 복사되는 원본의 시작좌표
            SRCCOPY     // 복사 옵션
        );
    }
}
void Image::Render(HDC hdc, int destX, int destY, int destW, int destH, int copyX, int copyY, int copyW, int copyH, int frameIndex)
{
    imageInfo->curFrameX = frameIndex;
    GdiTransparentBlt(
        hdc,    //목적지 DC
        destX, destY,   //복사 위치
        destW, destH,
        imageInfo->hMemDC, // 원본 DC
        copyX * imageInfo->curFrameX, // 복사 x위치 
        copyY, // 복사 y위치
        copyW, copyH,// 복사 크기
        colorToRemove
    );
}
=======
}
>>>>>>> origin/SES
