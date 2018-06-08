#pragma once
#include "Socket.h"
#include "Packet.h"
#include "Sync.h"
#include "system/Thread.h"
#include "system/CriticalSection.h"
#include "TcpInbox.h"
#include <stack>
#include "PacketPair.h"

namespace nb{ namespace Network{

class TcpConnectionEvent;
class TcpConnection : public TcpInboxEvent
{
public:
	TcpConnection(Socket *socket);
	~TcpConnection();

	//����״̬
	bool IsConnected() const;

	//����/ֹͣ��Ϣ����
	void Work();
	void UnWork();

	//Requst����������
	//pkg:Request����������
	//����Packet()�հ���ʾԶ���Ѿ��Ͽ�
	Packet Request(const Packet &pkg);

	//�ظ����첽
	//�������-1����ʾ����ʧ��
	int Reply(const Packet &pkg);

	//ʰȡ������ż�
	void PeekPacket(std::vector<Packet> &vtPkgs);

	//ʰȡ�ż��ظ�
	//feedback������Client���ݺ�ķ�������
	//����false��ʾclient���ѶϿ�
	bool PeekFeedback(std::vector<Packet> &feedbackPkgs);

	//����ͨ�ų�ʱʱ�䣬-1��ʾ������
	void SetTimeoutSpan(int ms);

	//��ȡͨ�ų�ʱʱ��
	int GetTimeoutSpan() const;

	//�Ƿ���������һ�λỰ����
	bool IsSessioning() const;

	void SetEventInterface(TcpConnectionEvent *pInterface);

private:
	TcpConnection(const TcpConnection &other) {}
	void operator = (const TcpConnection &other) {}

	virtual void TcpInbox_OnRequestArrived(const Packet &pkg);
	virtual void TcpInbox_OnReplyArrived(const Packet &pkg);
	virtual void TcpInbox_OnRemoteUnknownReasonDisconnected();

	void HandlePacket(const Packet &pkg);

	//���͹����������client����������ȴ���
	//����false��ʾclient�Ѿ��Ͽ�
	bool CheckUrgentPackets();

	bool							m_bConnected;
	bool							m_bTimeout;
	Socket							*m_pSocket;

	Sync							m_RequestSync;
	bool							m_bUrgentReplyNeeded;
	bool							m_bRequestWaitAgain;
	bool							m_bNeedUnlock;
	int								m_nWaitTimeout;

	TcpInbox						m_Inbox;
	nb::System::CriticalSection		m_Lock;
	TcpConnectionEvent				*m_pEventInterface;

	std::stack<PacketPair>			m_RequestSession;
	std::stack<PacketPair>			m_PeekSession;
};


class TcpConnectionEvent
{
public:
	virtual void TcpConnection_OnUrgentPacketHandleNeeded(TcpConnection *Conn, const std::vector<Packet> &vtRequestPkg, std::vector<Packet> &vtFeedbacks) {(void)vtRequestPkg; (void)vtFeedbacks;}
	virtual void TcpConnection_OnDisconnected(TcpConnection *Conn) {(void)Conn;}
};

}}
