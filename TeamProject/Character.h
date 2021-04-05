#pragma once
#include "GameNode.h"

class Image;
class CheckBox;
class Character : public GameNode
{
protected:
	Image* image;
	int maxHp;
	int curHp;
	STATUS status; // ĳ���� ����
	PPOS pPos; //1P, 2P���п�
	FPOINT pos; //���� ĳ���� ��ǥ
	float moveSpeed;
	int maxFrame[12]{ 0, };

	CheckBox* hitBox;
	CheckBox* attackBox;

	int maxImage;
	int width, height;
	int attack[5];
	int elapsedTime;
	int frameX; // �ӽú���(�������)
	int frameY;
	int spriteWidth;
	int spriteHeight;

public:
	virtual HRESULT Init(PPOS pPos);			// ��� ������ �ʱ�ȭ, �޸� �Ҵ�
	virtual void Release();			// �޸� ����
	virtual void Update();			// ������ ������ ���� ���� ���� (������ ����)
	virtual void Render(HDC hdc);	// ������ ������ ��� (�̹���, �ؽ�Ʈ ��)
	virtual void Move();
	virtual void Attack(STATUS status);
	inline virtual FPOINT GetPos() { return this->pos; }
	inline virtual void SetStatus(STATUS status) { this->status = status; }
	inline virtual STATUS GetStatus() { return this->status; }
	// ������ ������ ���� ���� ���� (������ ����)
};