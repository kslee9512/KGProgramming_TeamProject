#pragma once
#include "config.h"
#include <list>

class CommandQueue
{
private:
	struct datas {
		char value;
		int time;
	};
	list<datas>* queue;

public:
	~CommandQueue();
	HRESULT Init();
	void Release();
	bool HasCommand(string str, int miliseconds);
	void PopInvalidElements();
	void PushBack(char value, int miliseconds);
	bool compare(datas* d1, datas* d2);
};
