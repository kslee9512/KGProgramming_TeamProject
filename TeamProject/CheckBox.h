#pragma once
#include "GameNode.h"

class CheckBox : public GameNode
{
protected:
	FPOINT pos;
	float radius;
	bool isActivated;

public:
	virtual HRESULT Init();			// ��� ������ �ʱ�ȭ, �޸� �Ҵ�
	virtual void Release();			// �޸� ����
	virtual void Update();			// ������ ������ ���� ���� ���� (������ ����)
	virtual void Render(HDC hdc);		// ������ ������ ��� (�̹���, �ؽ�Ʈ ��)
	virtual void SetPos(FPOINT pos) { this->pos = pos; }
	virtual void SetRadius(float radius) { this->radius = radius; }

	virtual FPOINT GetPos() { return pos; }
	virtual float GetRadius() { return radius; }
};

