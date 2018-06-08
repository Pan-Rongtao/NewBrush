#pragma once
#include "core/Object.h"

namespace nb{ namespace System{

class NativeThread;
class NB_EXPORT Thread
{
public:
	enum Priority
	{
		Priority_Idle,						//����ʱ
		Priority_Lowest,					//
		Priority_Low,						//
		Priority_OperatingSystem_Normal,	//����ϵͳϵͳĬ��
		Priority_High,						//
		Priority_Highest,					//
		Priority_Realtime,					//ʵʱ���ȼ�
		Priority_Inherit,					//�̳У������ڴ��������̣߳�Ĭ�ϣ�
	};

public:
	//�������ȼ�����ʱ��Ч������ʹ�ã�
	void SetPriority(Priority priority);

	//��ȡ���ȼ�
	Priority GetPriority() const;

	//�����̣߳�����߳��Ѿ���������״̬����ά������״̬
	void Start();

	//ǿ����ֹ�̣߳�������ʹ�ã�
	void Quit();

	//�߳��Ƿ�������״̬
	bool IsRunning();

	//
	bool Wait(unsigned long nTime = 1);

	//��Ҫ��д���߳�ִ�к������ڵ���Start�����д˺���
	virtual void Run();

protected:
	//������/����/΢��
	static void Sleep(unsigned long seconds);
	static void MSleep(unsigned long milliSeconds);
	static void USleep(unsigned long uSeconds);

protected:
	//����һ���µ��̣߳�������δ����״̬
	Thread();
	virtual ~Thread();

private:
	NativeThread	*m_pNative;
};

}}
