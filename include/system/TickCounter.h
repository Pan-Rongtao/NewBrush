#pragma once
#include "system/Global.h"

namespace nb{ namespace System{

class NB_EXPORT TickCounter
{
public:
	//����һ���δ�������������󼴼�¼��ǰ�δ���
	TickCounter();

	//��ȡ���ŵ�tick
	//bReset��true������tickcount����ǰ����������
	UInt64 passed(bool bReset = false);

private:
	UInt64		m_systemTickCount;	
};

}}