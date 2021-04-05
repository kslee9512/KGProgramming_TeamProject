#include "Image.h"

HRESULT Image::Init(int width, int height, bool isTransparent, COLORREF transColor)
{
    HDC hdc = GetDC(g_hWnd);
    
    imageInfo = new IMAGE_INFO();
    imageInfo->resId = 0;
    imageInfo->hMemDC = CreateCompatibleDC(hdc); // hMemDC���� Mem�� Memory�� �ǹ�
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
}

HRESULT Image::Init(const char* fileName, int width, int height, bool isTransparent, COLORREF transColor)
{
    HDC hdc = GetDC(g_hWnd);

    imageInfo = new IMAGE_INFO();
    imageInfo->resId = 0;
    imageInfo->hMemDC = CreateCompatibleDC(hdc); // hMemDC���� Mem�� Memory�� �ǹ�
    imageInfo->hBitmap = (HBITMAP)LoadImage(g_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
    imageInfo->hOBitmap = (HBITMAP)SelectObject(imageInfo->hMemDC, imageInfo->hBitmap);
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
    this->colorToRemove = transColor;

    return S_OK;
}

//HRESULT Image::Init(const char* fileName, int width, int height, int maxFrameX, int maxFrameY, bool isTransparent, COLORREF transColor)
//{
//    HDC hdc = GetDC(g_hWnd);
//
//    imageInfo = new IMAGE_INFO();
//    imageInfo->resID = 0;
//    imageInfo->hMemDC = CreateCompatibleDC(hdc); // hMemDC���� Mem�� Memory�� �ǹ�
//    imageInfo->hBitmap = (HBITMAP)LoadImage(g_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
//    imageInfo->hOldBit = (HBITMAP)SelectObject(imageInfo->hMemDC, imageInfo->hBitmap);
//    imageInfo->width = width;
//    imageInfo->height = height;
//    imageInfo->loadType = IMAGE_LOAD_KIND::FILE;
//
//    imageInfo->maxFrameX = maxFrameX;
//    imageInfo->maxFrameX = maxFrameY;
//    imageInfo->frameWidth = imageInfo->width / maxFrameX;
//    imageInfo->frameHeight = imageInfo->height / maxFrameY;
//    imageInfo->currFrameX = 0;
//    imageInfo->currFrameY = 0;
//
//    ReleaseDC(g_hWnd, hdc);
//
//    if (imageInfo->hBitmap == NULL)
//    {
//        Release();
//        return E_FAIL;
//    }
//    this->isTransparent = isTransparent;
//    this->transColor = transColor;
//
//    return S_OK;
//}
HRESULT Image::Init(const char* fileName, int width, int height, int maxFrameX, int maxFrameY, PPOS pPos, bool isTransparent, COLORREF colorToRemove)
{
    HDC hdc = GetDC(g_hWnd); // g_hWnd�� �Ѱ��ϴ� ���� hdc�� ������

    imageInfo = new IMAGE_INFO();
    imageInfo->resId = 0;
    imageInfo->hMemDC = CreateCompatibleDC(hdc);//bitmap�� �����ϴ� ���� DC�� �����.
    imageInfo->hMemDC2 = CreateCompatibleDC(hdc);
    imageInfo->hBitmap = CreateCompatibleBitmap(hdc, width, height);
    imageInfo->hBitmap2 = (HBITMAP)LoadImage(g_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);//DC�� �����ϴ� ����
    imageInfo->hOBitmap = (HBITMAP)SelectObject(imageInfo->hMemDC, imageInfo->hBitmap);    //bBitmap �׸��� ������ �����ϱ� ���� hMemDC�� ����
    imageInfo->hOBitmap2 = (HBITMAP)SelectObject(imageInfo->hMemDC2, imageInfo->hBitmap2);    //bBitmap �׸��� ������ �����ϱ� ���� hMemDC�� ����
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
    //�޸𸮸� ���� ���� �ʴ´�. hdc�� ��� �������
    ReleaseDC(g_hWnd, hdc);

    if (imageInfo->hBitmap == NULL)//hBitmap ���� ���� ��
    {
        Release();
        return E_FAIL;
    }

    return S_OK;
}

void Image::Release()
{
}

void Image::Render(HDC hdc, int x, int y, int frameIndex)
{
   // imageInfo->hBitmap;
    imageInfo->curFrameX = frameIndex;
    if (isTransparent)
    {
        //Ư����������
        GdiTransparentBlt(
            hdc,    //������ DC
            x, y,   //���� ��ġ
            imageInfo->frameWidth, imageInfo->frameHeight, //���� ũ��
            imageInfo->hMemDC, // ���� DC
            imageInfo->frameWidth * imageInfo->curFrameX, // ���� x��ġ 
            imageInfo->frameWidth * imageInfo->curFrameY, // ���� y��ġ
            imageInfo->frameWidth, imageInfo->frameHeight, // ���� ũ��
            colorToRemove
        );
    }
    else
    {
        BitBlt(
            hdc,        //������ DC
            x, y,       // ���� ���� ��ġ(��ǥ)
            imageInfo->width,   // ����Ǵ� ������ ũ��
            imageInfo->height,  // ����Ǵ� ������ ũ��
            imageInfo->hMemDC,  // ����Ǵ� ���� DC
            0, 0,       // ����Ǵ� ������ ������ǥ
            SRCCOPY     // ���� �ɼ�
        );
    }
}
void Image::Render(HDC hdc, int destX, int destY, int destW, int destH, int copyX, int copyY, int copyW, int copyH, int frameIndex)
{
    imageInfo->curFrameX = frameIndex;
    GdiTransparentBlt(
        hdc,    //������ DC
        destX, destY,   //���� ��ġ
        destW, destH,
        imageInfo->hMemDC, // ���� DC
        copyX * imageInfo->curFrameX, // ���� x��ġ 
        copyY, // ���� y��ġ
        copyW, copyH,// ���� ũ��
        colorToRemove
    );
}