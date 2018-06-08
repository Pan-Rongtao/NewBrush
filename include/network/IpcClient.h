/*******************************************************
**	IpcClient
**
**	���̼�ͨ��Client��
**	
**	����������Ipc�ͻ��˵����ݽṹ
**	�������ڶ����������Ĵ���
**
**		
**		
**		������
**	
********************************************************/

#pragma once
#include "system/String.h"

namespace nb{ namespace System{

	class FarCallClient;
}}

namespace nb{ namespace Network{

class IpcClient_Internal;
class NB_EXPORT IpcClient
{
public:
	//��¼�����
	bool Login(const nb::System::String &sHostIp, unsigned int nHostPort);

	//�ǳ�
	void Logout();

	//��ȡ����
	nb::System::String GetName() const;

	//��ȡ������ip��ַ
	nb::System::String GetHostIp() const;

	//��ȡ�˿�
	unsigned int GetHostPort() const;

	//����FarCallConnectionͨ�ŻỰʹ�õľ��
	nb::System::FarCallClient *GetFarCallClient() const;

	//��ȡ�ż�
	void Peek();

	//����ͨ�ų�ʱʱ�䣬-1��ʾ������
	void SetTimeoutSpan(int ms);

	//��ȡͨ�ų�ʱʱ��
	int GetTimeoutSpan() const;

public:
	//����һ��IpcClient����
	IpcClient();
	IpcClient(const nb::System::String &name);
	~IpcClient();

private:
	IpcClient(const IpcClient &other) {}
	void operator = (const IpcClient &other) {}

	IpcClient_Internal		*m_pInternal;
};

}}
