#pragma once
#include "Packet.h"
#include "ClientSocket.h"
#include "TcpInbox.h"
#include <stack>
#include "PacketPair.h"

namespace nb{ namespace Network{

class TcpClientEvent;
class TcpClient_Internal : public TcpInboxEvent
{
public:
	TcpClient_Internal();
	TcpClient_Internal(const std::string &name);
	~TcpClient_Internal();

	bool Login(const std::string &sHostIp, int nPort);

	void Logout();

	bool IsConnected() const;

	std::string GetName() const;
	std::string GetHostIp() const;
	unsigned int GetHostPort() const;

	//Requst����������
	//pkg:Request����������
	Packet Request(const Packet &pkg);

	//�ظ����첽
	void Reply(const Packet &pkg);

	//ʰȡ������ż�
	void PeekPacket(std::vector<Packet> &vtPkgs);

	//ʰȡ�ż��ظ�
	//feedback������server���ݺ�ķ�������
	void PeekFeedback(std::vector<Packet> &feedbackPkgs);

	void SetTimeoutSpan(int ms);

	int GetTimeoutSpan() const;

	void SetEventInterface(TcpClientEvent *pEvent);

private:
	TcpClient_Internal(const TcpClient_Internal &other) {}
	void operator = (const TcpClient_Internal &other) {}

	virtual void TcpInbox_OnRequestArrived(const Packet &pkg);
	virtual void TcpInbox_OnReplyArrived(const Packet &pkg);
	virtual void TcpInbox_OnRemoteUnknownReasonDisconnected();

	//���͹����������client����������ȴ���
	void CheckUrgentPackets();

	bool							m_bConnected;
	ClientSocket					*m_pSocket;
	std::string						m_Name;

	Sync							m_RequestSync;
	nb::System::CriticalSection		m_Lock;
	TcpInbox						m_Inbox;
	TcpClientEvent					*m_pEventInterface;

	bool							m_bUrgentReplyNeeded;
	bool							m_bRequestWaitAgain;
	int								m_nWaitTimeout;
	std::vector<Packet>				m_UrgentPackets;
	std::stack<PacketPair>			m_RequestSession;
};

}}