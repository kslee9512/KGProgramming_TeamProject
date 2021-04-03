#include "Image.h"

HRESULT Image::Init(int width, int height, bool isTransparent, COLORREF transColor)
{
    HDC hdc = GetDC(g_hWnd);
    
    imageInfo = new IMAGE_INFO();
    imageInfo->resID = 0;
    imageInfo->hMemDC = CreateCompatibleDC(hdc); // hMemDC에서 Mem은 Memory를 의미
    imageInfo->hBitmap = CreateCompatibleBitmap(hdc, width, height);
    imageInfo->hOldBit = (HBITMAP)SelectObject(imageInfo->hMemDC, imageInfo->hBitmap);
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
    this->transColor = transColor;

    return S_OK;
}

HRESULT Image::Init(const char* fileName, int width, int height, bool isTransparent, COLORREF transColor)
{
    HDC hdc = GetDC(g_hWnd);

    imageInfo = new IMAGE_INFO();
    imageInfo->resID = 0;
    imageInfo->hMemDC = CreateCompatibleDC(hdc); // hMemDC에서 Mem은 Memory를 의미
    imageInfo->hBitmap = (HBITMAP)LoadImage(g_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
    imageInfo->hOldBit = (HBITMAP)SelectObject(imageInfo->hMemDC, imageInfo->hBitmap);
    imageInfo->width = width;
    imageInfo->height = height;
    imageInfo->loadType = IMAGE_LOAD_KIND::FILE;


    ReleaseDC(g_hWnd, hdc);

    if (imageInfo->hBitmap == NULL)
    {
        Release();
        return E_FAIL;
    }
    this->isTransparent = isTransparent;
    this->transColor = transColor;

    return S_OK;
}

HRESULT Image::Init(const char* fileName, int width, int height, int maxFrameX, int maxFrameY, bool isTransparent, COLORREF transColor)
{
    HDC hdc = GetDC(g_hWnd);

    imageInfo = new IMAGE_INFO();
    imageInfo->resID = 0;
    imageInfo->hMemDC = CreateCompatibleDC(hdc); // hMemDC에서 Mem은 Memory를 의미
    imageInfo->hBitmap = (HBITMAP)LoadImage(g_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
    imageInfo->hOldBit = (HBITMAP)SelectObject(imageInfo->hMemDC, imageInfo->hBitmap);
    imageInfo->width = width;
    imageInfo->height = height;
    imageInfo->loadType = IMAGE_LOAD_KIND::FILE;

    imageInfo->maxFrameX = maxFrameX;
    imageInfo->maxFrameX = maxFrameY;
    imageInfo->frameWidth = imageInfo->width / maxFrameX;
    imageInfo->frameHeight = imageInfo->height / maxFrameY;
    imageInfo->currFrameX = 0;
    imageInfo->currFrameY = 0;

    ReleaseDC(g_hWnd, hdc);

    if (imageInfo->hBitmap == NULL)
    {
        Release();
        return E_FAIL;
    }
    this->isTransparent = isTransparent;
    this->transColor = transColor;

    return S_OK;
}

void Image::Release()
{
}

void Image::Render(HDC hdc, int x, int y, int frameIndex)
{
    imageInfo->currFrameX = frameIndex;
    if (isTransparent)
    {
        //특정색상제거
        GdiTransparentBlt(
            hdc,    //목적지 DC
            x, y,   //복사 위치
            imageInfo->frameWidth, imageInfo->frameHeight, //복사 크기
            imageInfo->hMemDC, // 원본 DC
            imageInfo->frameWidth * imageInfo->currFrameX, // 복사 x위치 
            imageInfo->frameWidth * imageInfo->currFrameY, // 복사 y위치
            imageInfo->frameWidth, imageInfo->frameHeight, // 복사 크기
            transColor
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

void Image::TestRender(HDC hdc, int destX, int destY, int destW, int destH, int copyX, int copyY, int copyW, int copyH, int frameIndex)
{
    imageInfo->currFrameX = frameIndex;
    GdiTransparentBlt(
        hdc,    //목적지 DC
        destX, destY,   //복사 위치
        destW, destH,
        imageInfo->hMemDC, // 원본 DC
        copyX * imageInfo->currFrameX, // 복사 x위치 
        copyY, // 복사 y위치
        copyW, copyH,// 복사 크기
        transColor
    );
}
