#pragma once
#include "GameNode.h"

class Image;
class Character : public GameNode
{
protected:
	int imageWidth = 15316;
	Image* image;
	int maxHp;
	int curHp;
	STATUS status; // ĳ���� ����
	PPOS pPos; //1P, 2P���п�
	FPOINT pos; //���� ĳ���� ��ǥ
	float moveSpeed;
	int maxFrame[12]{ 0, };
	int width, height;
	int attack[5];
	int elapsedTime;
	int frame; // �ӽú���(�������)
public:
	virtual HRESULT Init(PPOS pPos);			// ��� ������ �ʱ�ȭ, �޸� �Ҵ�
	virtual void Release();			// �޸� ����
	virtual void Update(STATUS status);			// ������ ������ ���� ���� ���� (������ ����)
	virtual void Render(HDC hdc);	// ������ ������ ��� (�̹���, �ؽ�Ʈ ��)
	virtual void Move(STATUS status);
	virtual void Attack(STATUS status);
	inline virtual FPOINT GetPos() { return this->pos; }
	inline virtual void SetStatus(STATUS status) { this->status = status; }
	inline virtual STATUS GetStatus() { return this->status; }
};

