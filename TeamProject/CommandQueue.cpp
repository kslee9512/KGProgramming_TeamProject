#include "CommandQueue.h"
#include <algorithm>

CommandQueue::~CommandQueue()
{
	if (queue) {
		delete queue;
		queue = nullptr;
	}
}

void CommandQueue::Release()
{
	if (queue) {
		delete queue;
		queue = nullptr;
	}
}

HRESULT CommandQueue::Init()
{
	queue = new list<datas>;
	return S_OK;
}


bool CommandQueue::Update(string str, int miliseconds)
{
	if (queue->empty()) return false;
	//밀리세컨즈 단위 시간을 받아서 해당 시간만큼 time을 감소시키고
	//해당 문자열이 있으면 반환하고 큐를 비운다.
	string tmpStr = "";
	for (list<datas>::iterator iter = queue->begin(); iter != queue->end(); iter++) {
		iter->time -= miliseconds;
		tmpStr += iter->value;
	}
	if (tmpStr.find(str) != string::npos) {
		queue->clear();
		return true;
	}

	return false;
}

void CommandQueue::PopInvalidElements()
{
	if (queue->empty()) return;

	//sort(queue->begin(), queue->end(), compare);
	for (list<datas>::iterator iter = queue->begin(); iter != queue->end(); iter++) {
		if (iter->time <= 0) {
			queue->pop_front();
		}
		else {
			return;
		}
	}
}

void CommandQueue::PushBack(char value, int miliseconds)
{
	queue->push_back(datas{value, miliseconds});
}

bool CommandQueue::compare(datas* d1, datas* d2)
{
	return d1->time < d2->time;
}
