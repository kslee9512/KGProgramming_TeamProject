#pragma once
#include "GameNode.h"

class CheckBox : public GameNode
{
protected:
	FPOINT pos;
	float radius;
	bool isActivated;

public:
	virtual HRESULT Init();			// 멤버 변수의 초기화, 메모리 할당
	virtual void Release();			// 메모리 해제
	virtual void Update();			// 프레임 단위로 게임 로직 실행 (데이터 변동)
	virtual void Render(HDC hdc);		// 프레임 단위로 출력 (이미지, 텍스트 등)
	virtual void SetPos(FPOINT pos) { this->pos = pos; }
	virtual void SetRadius(float radius) { this->radius = radius; }

	virtual FPOINT GetPos() { return pos; }
	virtual float GetRadius() { return radius; }
};

