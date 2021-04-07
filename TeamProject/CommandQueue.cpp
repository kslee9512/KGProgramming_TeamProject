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


bool CommandQueue::HasCommand(string str, int miliseconds)
{
	//�и������� ���� �ð��� �޾Ƽ� �ش� �ð���ŭ time�� ���ҽ�Ű��
	//�ش� ���ڿ��� ������ ��ȯ�ϰ� ť�� ����.
	if (queue->empty()) return false;

	string tmpStr = "";
	for (list<datas>::iterator iter = queue->begin(); iter != queue->end(); iter++) {
		iter->time -= miliseconds;
		tmpStr.append(string{ char{iter->value} });
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
	for (list<datas>::iterator iter = queue->begin(); iter != queue->end(); ) {
		if (iter->time <= 0) {
			iter = queue->erase(iter);
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
