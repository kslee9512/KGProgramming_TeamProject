#pragma once
#include "GameNode.h"

class CheckBox : public GameNode
{
protected:
	RECT* shape;
public:
	virtual HRESULT Init();			// ��� ������ �ʱ�ȭ, �޸� �Ҵ�
	virtual void Release();			// �޸� ����
	virtual void Update();			// ������ ������ ���� ���� ���� (������ ����)
	virtual void Render(HDC hdc);		// ������ ������ ��� (�̹���, �ؽ�Ʈ ��)
};

