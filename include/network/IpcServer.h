#pragma once
#include "core/Object.h"
#include "system/FarCallConnectObject.h"
#include "system/String.h"

namespace nb{ namespace Network{

class IpcServerEvent;
class IpcServer_Internal;
class NB_EXPORT IpcServer
{
public:
	//��ȡ������Ip
	nb::System::String GetIp() const;

	//��ȡ�������󶨵Ķ˿ں�
	unsigned int GetBindingPort() const;

	//��������
	bool Startup();

	//ֹͣ����
	void Shutdown();

	//������ȡ�ͻ��˵��ż����ݣ�����������������ݣ����ż����ǿյ�
	void Peek();

	//����ͨ�ų�ʱʱ�䣬-1��ʾ������
	void SetTimeoutSpan(int ms);

	//��ȡͨ�ų�ʱʱ��
	int GetTimeoutSpan() const;

	void SetEventInterface(IpcServerEvent *pInterface);

public:
	IpcServer(const nb::System::String &sIp, unsigned int nPort);
	~IpcServer();
	
private:
	IpcServer(const IpcServer &other) {}
	void operator = (const IpcServer &other) {}

	IpcServer_Internal	*m_pInternal;
};

class IpcServerEvent
{
public:
	//�µ��������
	virtual void IpcServer_OnNewConnection(const nb::System::String &name, nb::System::FarCallServer *pFarCallServer) {(void)name, (void)pFarCallServer;}

	//�����ѶϿ�
	virtual void IpcServer_OnConnectionDisconnected(nb::System::FarCallServer *pFarCallServer) {(void)pFarCallServer;}
};

}}
