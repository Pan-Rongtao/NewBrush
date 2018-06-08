#pragma once
#include <vector>
#include "TcpServer.h"
#include "FarCallConnectionList.h"
#include "system/FarCallConnectObject.h"

namespace nb{ namespace Network{

class IpcServerEvent;
class FarCallConnectionListEvent;
class IpcServer_Internal : public TcpServerEvent
{
public:
	//��ȡ������Ip
	std::string GetIp() const;

	//��ȡ�������󶨵Ķ˿ں�
	unsigned int GetBindingPort() const;

	//��������
	bool Startup();

	//ֹͣ����
	void Shutdown();

	//��������
	//nb::System::FarCallSerial Send(const std::string &sClientName, nb::System::FarCallSerial &serial);

	//��ȡ�ռ����ż�������������������ݣ������������ǿյ�
	void Peek();

	//����ͨ�ų�ʱʱ�䣬-1��ʾ������
	void SetTimeoutSpan(int ms);

	//��ȡͨ�ų�ʱʱ��
	int GetTimeoutSpan() const;

	void SetEventInterface(IpcServerEvent *pInterface);

public:
	IpcServer_Internal(const std::string &sIp, unsigned int nPort);
	~IpcServer_Internal();

private:
	virtual void TcpServer_OnUrgentPacketHandleNeeded(TcpConnection *Conn, const std::vector<Packet> &vtRequests, std::vector<Packet> &vtFeedbacks);

	//����һ��pkg������ֵ��ʾ�Ƿ����˳�pkg
	bool HandlePeekedPackage(TcpConnection *Conn, const Packet &pkg, Packet &feedback);

private:
	TcpServer						m_TcpServer;
	FarCallConnectionList			m_FarCallConnections;
	IpcServerEvent					*m_pEventInterface;
};

}}
