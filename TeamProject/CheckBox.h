#pragma once
#include "GameNode.h"

class CheckBox : public GameNode
{
protected:
	FPOINT pos; // �ڽ��� �߽���ǥ
	RECT rect;
	bool isActivated;
	float width;
	float height;

public:
	virtual HRESULT Init();			// ��� ������ �ʱ�ȭ, �޸� �Ҵ�
	virtual HRESULT Init(FPOINT pos, int width, int height);
	virtual void Release();			// �޸� ����
	virtual void Update();			// ������ ������ ���� ���� ���� (������ ����)
	virtual void Update(FPOINT pos);
	virtual void Update(PPOS pPos, STATUS status);
	virtual void Render(HDC hdc);		// ������ ������ ��� (�̹���, �ؽ�Ʈ ��)
	virtual void SetPos(FPOINT pos) { this->pos = pos; }
	virtual void SetActivated(bool isActivated) { this->isActivated = isActivated; }
	
	virtual bool GetActivated() { return isActivated;}
	virtual FPOINT GetPos() { return pos; }
	virtual RECT GetRect() { return rect; }
};

