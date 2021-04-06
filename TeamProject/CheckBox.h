#pragma once
#include "GameNode.h"

class CheckBox : public GameNode
{
protected:
	FPOINT pos; // 박스의 중심좌표
	RECT rect;
	bool isActivated;
	float width;
	float height;

public:
	virtual HRESULT Init();			// 멤버 변수의 초기화, 메모리 할당
	virtual HRESULT Init(FPOINT pos, int width, int height);
	virtual void Release();			// 메모리 해제
	virtual void Update();			// 프레임 단위로 게임 로직 실행 (데이터 변동)
	virtual void Update(FPOINT pos);
	virtual void Update(PPOS pPos, STATUS status);
	virtual void Render(HDC hdc);		// 프레임 단위로 출력 (이미지, 텍스트 등)
	virtual void SetPos(FPOINT pos) { this->pos = pos; }
	virtual void SetActivated(bool isActivated) { this->isActivated = isActivated; }
	
	virtual bool GetActivated() { return isActivated;}
	virtual FPOINT GetPos() { return pos; }
	virtual RECT GetRect() { return rect; }
};

