#pragma once
#include "GameNode.h"

class Image;
class CheckBox;
class CommandQueue;
class Character : public GameNode
{
protected:
	Image* image;
	int maxHp = 400;
	int curHp;
	STATUS status; // ĳ���� ����
	PPOS pPos; //1P, 2P���п�
	FPOINT pos; //�̹��� ��ǥ
	FPOINT charPos; //ĳ���� �߽� ��ǥ
	float moveSpeed;
	int maxFrame[12]{ 0, };

	CheckBox* hitBox;
	CheckBox* attackBox;

	CommandQueue* keyCache;

	int maxImage;
	int width, height;
	int attack[5];
	int elapsedTime;
	int frameX; // �ӽú���(�������)
	int frameY;

	int spriteWidth;
	int spriteHeight;
	bool isTouched;
	bool isAlive;


public:
	virtual HRESULT Init(PPOS pPos);			// ��� ������ �ʱ�ȭ, �޸� �Ҵ�
	virtual void Release();			// �޸� ����
	virtual void Update();			// ������ ������ ���� ���� ���� (������ ����)
	virtual void Render(HDC hdc);	// ������ ������ ��� (�̹���, �ؽ�Ʈ ��)
	virtual void Move();
	virtual void Attack(STATUS status);
	virtual void KnockBack(int distance);
	inline virtual int GetCurHp() { return this->curHp; }
	inline virtual void GotDamage(int damage) { this->curHp -= damage; if (this->curHp <= 0) { this->curHp = 1; }}
	inline virtual FPOINT GetPos() { return this->pos; }
	inline virtual void SetStatus(STATUS status) { this->status = status; }
	inline virtual void SetFrameX(int frameX) { this->frameX; }
	inline virtual STATUS GetStatus() { return this->status; }
	inline virtual void SetTouched(bool isTouched) { this->isTouched = isTouched; }
	inline virtual CheckBox* getAttackBox() { return attackBox; }
	inline virtual CheckBox* getHitBox() { return hitBox; }
	inline virtual CommandQueue* GetKeyCache() { return keyCache; }
	// ������ ������ ���� ���� ���� (������ ����)
};
