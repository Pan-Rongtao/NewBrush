#pragma once
#include "../core/Def.h"

namespace nb{ namespace System{

class Thread_Internal;
class NB_API Thread
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
	void setPriority(Priority priority);

	//��ȡ���ȼ�
	Priority priority() const;

	//�����̣߳�����߳��Ѿ���������״̬����ά������״̬
	void start();

	//ǿ����ֹ�̣߳�������ʹ�ã�
	void quit();

	//�߳��Ƿ�������״̬
	bool isRunning();

	//
	bool wait(unsigned long nTime = 1);

	//��Ҫ��д���߳�ִ�к������ڵ���Start�����д˺���
	virtual void run();

protected:
	//������/����/΢��
	static void sleep(unsigned long seconds);
	static void msleep(unsigned long milliseconds);
	static void usleep(unsigned long useconds);

protected:
	//����һ���µ��̣߳�������δ����״̬
	Thread();
	virtual ~Thread();

private:
	Thread_Internal	*m_internal;
};

}}
