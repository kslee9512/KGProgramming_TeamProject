#include "Image.h"

HRESULT Image::Init(int width, int height)
{
<<<<<<< HEAD
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
=======
	HDC hdc = GetDC(g_hWnd); // g_hWnd�� �Ѱ��ϴ� ���� hdc�� ������

	imageInfo = new IMAGE_INFO();
	imageInfo->resId = 0;
	imageInfo->hMemDC = CreateCompatibleDC(hdc);//bitmap�� �����ϴ� ���� DC�� �����. 
	imageInfo->hBitmap = CreateCompatibleBitmap(hdc, width, height);//DC�� �����ϴ� ����
	imageInfo->hOBitmap = (HBITMAP)SelectObject(imageInfo->hMemDC, imageInfo->hBitmap);	//bBitmap �׸��� ������ �����ϱ� ���� hMemDC�� ����
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

	//�޸𸮸� ���� ���� �ʴ´�. hdc�� ��� �������
	ReleaseDC(g_hWnd, hdc);

	if (imageInfo->hBitmap == NULL)//hBitmap ���� ���� ��
	{
		Release();
		return E_FAIL;
	}

	return S_OK;
>>>>>>> origin/SES
}

HRESULT Image::Init(const char* fileName, int width, int height, bool isTransparent, COLORREF colorToRemove)
{
	HDC hdc = GetDC(g_hWnd); // g_hWnd�� �Ѱ��ϴ� ���� hdc�� ������

	imageInfo = new IMAGE_INFO();
	imageInfo->resId = 0;
	imageInfo->hMemDC = CreateCompatibleDC(hdc);//bitmap�� �����ϴ� ���� DC�� �����. 
	imageInfo->hBitmap = (HBITMAP)LoadImage(g_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);//DC�� �����ϴ� ����
	imageInfo->hOBitmap = (HBITMAP)SelectObject(imageInfo->hMemDC, imageInfo->hBitmap);	//bBitmap �׸��� ������ �����ϱ� ���� hMemDC�� ����
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
	//�޸𸮸� ���� ���� �ʴ´�. hdc�� ��� �������
	ReleaseDC(g_hWnd, hdc);

	if (imageInfo->hBitmap == NULL)//hBitmap ���� ���� ��
	{
		Release();
		return E_FAIL;
	}

	return S_OK;
}

HRESULT Image::Init(const char* fileName, int width, int height, int maxFrameX, int maxFrameY, PPOS pPos, bool isTransparent, COLORREF colorToRemove)
{
	HDC hdc = GetDC(g_hWnd); // g_hWnd�� �Ѱ��ϴ� ���� hdc�� ������

	imageInfo = new IMAGE_INFO();
	imageInfo->resId = 0;
	imageInfo->hMemDC = CreateCompatibleDC(hdc);//bitmap�� �����ϴ� ���� DC�� �����.
	imageInfo->hMemDC2 = CreateCompatibleDC(hdc);
	imageInfo->hBitmap = CreateCompatibleBitmap(hdc, width, height);
	imageInfo->hBitmap2 = (HBITMAP)LoadImage(g_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);//DC�� �����ϴ� ����
	imageInfo->hOBitmap = (HBITMAP)SelectObject(imageInfo->hMemDC, imageInfo->hBitmap);	//bBitmap �׸��� ������ �����ϱ� ���� hMemDC�� ����
	imageInfo->hOBitmap2 = (HBITMAP)SelectObject(imageInfo->hMemDC2, imageInfo->hBitmap2);	//bBitmap �׸��� ������ �����ϱ� ���� hMemDC�� ����
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
	//�޸𸮸� ���� ���� �ʴ´�. hdc�� ��� �������
	ReleaseDC(g_hWnd, hdc);
<<<<<<< HEAD

	if (imageInfo->hBitmap == NULL)//hBitmap ���� ���� ��
	{
		Release();
		return E_FAIL;
	}

	return S_OK;
}

HRESULT Image::Init(const char* fileName, int width, int height, int maxFrameX, int maxFrameY, PPOS pPos, bool isTransparent, COLORREF colorToRemove)
{
	HDC hdc = GetDC(g_hWnd); // g_hWnd�� �Ѱ��ϴ� ���� hdc�� ������

	imageInfo = new IMAGE_INFO();
	imageInfo->resId = 0;
	imageInfo->hMemDC = CreateCompatibleDC(hdc);//bitmap�� �����ϴ� ���� DC�� �����.
	imageInfo->hMemDC2 = CreateCompatibleDC(hdc);
	imageInfo->hBitmap = CreateCompatibleBitmap(hdc, width, height);
	imageInfo->hBitmap2 = (HBITMAP)LoadImage(g_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);//DC�� �����ϴ� ����
	imageInfo->hOBitmap = (HBITMAP)SelectObject(imageInfo->hMemDC, imageInfo->hBitmap);	//bBitmap �׸��� ������ �����ϱ� ���� hMemDC�� ����
	imageInfo->hOBitmap2 = (HBITMAP)SelectObject(imageInfo->hMemDC2, imageInfo->hBitmap2);	//bBitmap �׸��� ������ �����ϱ� ���� hMemDC�� ����
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
		hdc,				//���� ������ DC
		destX, destY,		//�ٿ��ֱ� �� ��ġ
		imageInfo->width / imageInfo->maxFrameX,			//�������� ����� ����, ���� ũ��
		imageInfo->height / imageInfo->maxFrameY,
		imageInfo->hMemDC,	//���� DC
		imageInfo->width / imageInfo->maxFrameX * (imageInfo->curFrameX),
		imageInfo->height / imageInfo->maxFrameY * (imageInfo->curFrameY),		//�������� ���� ���� ��ġ
		SRCCOPY				//���� �ɼ�
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

	if (imageInfo->hBitmap == NULL)//hBitmap ���� ���� ��
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
		hdc,				//���� ������ DC
		destX, destY,		//�ٿ��ֱ� �� ��ġ
		imageInfo->width / imageInfo->maxFrameX,			//�������� ����� ����, ���� ũ��
		imageInfo->height / imageInfo->maxFrameY,
		imageInfo->hMemDC,	//���� DC
		imageInfo->width / imageInfo->maxFrameX * (imageInfo->curFrameX),
		imageInfo->height / imageInfo->maxFrameY * (imageInfo->curFrameY),		//�������� ���� ���� ��ġ
		SRCCOPY				//���� �ɼ�
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
=======
}
>>>>>>> origin/SES
