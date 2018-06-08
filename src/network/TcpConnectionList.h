#pragma once
#include <vector>
#include "TcpConnection.h"
#include "ReceivePacket.h"
#include "core/Object.h"
#include "system/CriticalSection.h"

namespace nb{ namespace Network{

class TcpConnectionListEvent;
class TcpConnectionEvent;
class TcpConnectionList : public TcpConnectionEvent
{
	friend class TcpConnection;
public:
	TcpConnectionList();
	~TcpConnectionList();

	//���б�β��׷��һ��Connection
	void Append(Socket *socket);

	//�Ƴ�һ��Connection
	void Remove(TcpConnection *Conn);

	//�������Connection
	void Clear();

	//��ȡ��������
	int GetCount();

	//��ȡ�±�Ϊindex��Connection
	TcpConnection *GetAt(int index);

	//��ĳ��Connection������
	Packet Send(TcpConnection *Conn, const Packet &pkg);

	//�㲥
	void Broadcast(const Packet &pkg);

	//�Ӷ�����ʰȡ����Connection��Packet
	void PeekClientPackets(std::vector<ReceivePacket> &vtRpkgs);

	//����ͨ�ų�ʱʱ�䣬-1��ʾ������
	void SetTimeoutSpan(int ms);

	//��ȡͨ�ų�ʱʱ��
	int GetTimeoutSpan() const;

	void SetEventInterface(TcpConnectionListEvent *pInterface);

private:
	virtual void TcpConnection_OnUrgentPacketHandleNeeded(TcpConnection *Conn, const std::vector<Packet> &vtRequestPkgs, std::vector<Packet> &vtFeedbackPkgs);
	virtual void TcpConnection_OnDisconnected(TcpConnection *Conn);

	int									m_nWaitTimeout;
	std::vector<TcpConnection *>		m_vtConnection;
	nb::System::CriticalSection			m_Lock;
	TcpConnectionListEvent				*m_pEventInterface;
};

class TcpConnectionListEvent
{
public:
	virtual void TcpConnectionList_OnUrgentPacketHandleNeeded(TcpConnection *Conn, const std::vector<Packet> &vtRequestPkg, std::vector<Packet> &vtFeedbackPkgs) {}
};

}}
