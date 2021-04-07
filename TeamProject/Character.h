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
	STATUS status; // 캐릭터 상태
	PPOS pPos; //1P, 2P구분용
	FPOINT pos; //이미지 좌표
	FPOINT charPos; //캐릭터 중심 좌표
	float moveSpeed;
	int maxFrame[12]{ 0, };

	CheckBox* hitBox;
	CheckBox* attackBox;

	CommandQueue* keyCache;

	int maxImage;
	int width, height;
	int attack[5];
	int elapsedTime;
	int frameX; // 임시변수(삭제요망)
	int frameY;

	int spriteWidth;
	int spriteHeight;
	bool isTouched;
	bool isAlive;


public:
	virtual HRESULT Init(PPOS pPos);			// 멤버 변수의 초기화, 메모리 할당
	virtual void Release();			// 메모리 해제
	virtual void Update();			// 프레임 단위로 게임 로직 실행 (데이터 변동)
	virtual void Render(HDC hdc);	// 프레임 단위로 출력 (이미지, 텍스트 등)
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
	// 프레임 단위로 게임 로직 실행 (데이터 변동)
};
