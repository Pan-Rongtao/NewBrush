#pragma once
#include "../core/Def.h"

namespace nb{ namespace core {

class NB_API TickCounter
{
public:
	//����һ���δ�������������󼴼�¼��ǰ�δ���
	TickCounter();

	//��ȡ���ŵ�tick
	//bReset��true������tickcount����ǰ����������
	uint64_t passed(bool bReset = false);

private:
	uint64_t		m_systemTickCount;
};

}}