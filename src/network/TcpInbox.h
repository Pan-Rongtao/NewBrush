#pragma once
#include <vector>
#include "system/CriticalSection.h"
#include "Sync.h"
#include "TcpMesssageMonitor.h"
#include "Packet.h"

namespace nb{ namespace Network{

class TcpInboxEvent;
class TcpInbox : public TcpMessageMonitorEvent
{
public:
	TcpInbox();
	~TcpInbox();

	//
	void SetSocket(Socket *socket);

	//������Ϣ������ȡ�ż�
	void Work();

	//�ر���Ϣ����
	void UnWork();

	void PopPackets(std::vector<Packet> &vtPkgs);

	void PushPacket(const Packet &pkg);

	void SetEventInterface(TcpInboxEvent *pInterface);

private:
	TcpInbox(const TcpInbox &other);
	void operator = (const TcpInbox &other);

	virtual void TcpMessageMonitor_OnPacketArrived(const Packet &pkg);
	virtual void TcpMessageMonitor_OnErrorPacket();

	std::vector<Packet>				m_vtPkgs;
	nb::System::CriticalSection		m_PacketsLock;
	TcpMessageMonitor				m_MessageMonitor;
	TcpInboxEvent					*m_pEventInterface;

	std::vector<Packet>				m_vtHandling;
};

class TcpInboxEvent
{
public:
	//���µ�����
	virtual void TcpInbox_OnRequestArrived(const Packet &toRemoteFeedback) {(void)toRemoteFeedback;}

	//���µĻظ�
	virtual void TcpInbox_OnReplyArrived(const Packet &fromRemoteFeedback) {(void)fromRemoteFeedback;}

	//����δ֪ԭ��Ͽ���
	virtual void TcpInbox_OnRemoteUnknownReasonDisconnected() {}

};

}}
