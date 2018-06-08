#include "TcpConnection.h"
#include <assert.h>
#include "core/Exception.h"

using nb::Network::TcpConnection;
using nb::Network::Socket;
using nb::Network::Packet;
using nb::Network::TcpConnectionEvent;

TcpConnection::TcpConnection(Socket *socket)
: m_pSocket(socket)
, m_bConnected(false)
, m_bTimeout(false)
, m_bUrgentReplyNeeded(false)
, m_bRequestWaitAgain(false)
, m_bNeedUnlock(true)
, m_nWaitTimeout(-1)
, m_pEventInterface(NULL)
{
	m_Inbox.SetSocket(m_pSocket);
	m_Inbox.SetEventInterface(this);
}

TcpConnection::~TcpConnection()
{
	//����ɾ��socket���Ǻܹ淶����Ϊnew socket����listen����ģ��������ǱȽϺõĵط���
	m_Lock.Lock();
	delete m_pSocket;
	m_pSocket = NULL;
	m_bConnected = false;
	m_Lock.Unlock();
}

bool TcpConnection::IsConnected() const
{
	return m_bConnected;
}

void TcpConnection::Work()
{
	m_bConnected = true;
	m_Inbox.Work();
}

void TcpConnection::UnWork()
{
	m_bConnected = false;
	m_Inbox.UnWork();
}

//������wait֮��ĵط����ü������Ա�֤request�ڼ�ͬ��
//Request���п���Ƕ�׵ģ������Ҫһ��Stack��������������
//Ƕ�׵ĳ���Ϊ����һ��Connection����Request�󣬽��յ�Client��������ʱ����Ҫ
//���ȴ���Client�����󣬵�����Client������Ϣ�У�Connection�ַ���һ��Request
//ע�⣺�����Request�����з���client�Ѿ��Ͽ�����Ҫ���ϰ�Connectionɾ����
//���ǵȵ���һ��peek�յ�logout��ɾ������Ȼ���Ѵ���
Packet TcpConnection::Request(const Packet &pkg)
{
	assert(IsConnected());

	m_Lock.Lock();
	m_bNeedUnlock = true;
	m_RequestSession.push(PacketPair((Packet *)(&pkg), NULL));
	int nSend = m_pSocket->SendData(pkg.GetData(), pkg.GetSize());
	//send�����ʾԶ���ѶϿ����򷵻ؿհ�
	if(nSend == -1)
	{
		m_Lock.Unlock();
		return Packet();
	}
	//����������reply����������ʾԶ���ѶϿ����򷵻ؿհ�
	if(CheckUrgentPackets() == false)
	{
		m_Lock.Unlock();
		return Packet();
	}
	//ע�����������Request������Ƕ�ף���Ҫ����ȫ�������̲߳��ܼ���ִ�У����ȫ������һ�μ��ɣ�
	if(m_bNeedUnlock)
	{
		for(int i = 0; i != m_RequestSession.size(); ++i)	
			m_Lock.Unlock();
		if(m_RequestSession.size() >= 2)
			m_bNeedUnlock = false;
	}


loop:
	bool b = m_RequestSync.Wait(m_nWaitTimeout);
	if(b)
	{
		m_Lock.Lock();
		m_bTimeout = true;
		m_RequestSession.pop();
		m_Lock.Unlock();
		printf("[%d]TcpConnection::Request---wait timeout!!! m_RequestSession.pop->size[%d]\r\n", nb::System::Platform::GetCurrentProcessId(), m_RequestSession.size());
		NB_THROW_EXCEPTION("server request timeout!!!");
	}

	m_Lock.Lock();
	if(m_bUrgentReplyNeeded) CheckUrgentPackets();
	m_Lock.Unlock();

	if(m_bRequestWaitAgain)
		goto loop;

	m_Lock.Lock();
	Packet *p = m_RequestSession.top().Ack;
	Packet ret = p ? *p : Packet();
	delete p;
	m_RequestSession.pop();
	m_Lock.Unlock();

	return ret;
}

int TcpConnection::Reply(const Packet &pkg)
{
	assert(IsConnected());

	m_Lock.Lock();
	int nSend = m_pSocket->SendData(pkg.GetData(), pkg.GetSize());
	m_Lock.Unlock();
	return nSend;
}

void TcpConnection::PeekPacket(std::vector<Packet> &vtPkgs)
{
	m_Lock.Lock();
	m_Inbox.PopPackets(vtPkgs);
	for(int i = 0; i != vtPkgs.size(); ++i)
		m_PeekSession.push(PacketPair(&(vtPkgs[i]), NULL));
	m_Lock.Unlock();
}

bool TcpConnection::PeekFeedback(std::vector<Packet> &feedbackPkgs)
{
	for(int i = 0; i != feedbackPkgs.size(); ++i)
	{
		Packet &pkg = feedbackPkgs[i];
		if(pkg.GetHeader().GetMessageType() == Header::Message_Signal_Account_Logout)
		{
			m_pEventInterface->TcpConnection_OnDisconnected(this);
			return true;
		}
		else
		{
			m_Lock.Lock();
			int nSend = Reply(pkg);
			m_bRequestWaitAgain = (m_RequestSession.size() >= 1) && (nSend != -1);
			if(!m_PeekSession.empty())
				m_PeekSession.pop();
			m_Lock.Unlock();
			return nSend != -1;
		}

	}
	return true;
}

void TcpConnection::SetTimeoutSpan(int ms)
{
	m_nWaitTimeout = ms;
}

int TcpConnection::GetTimeoutSpan() const
{
	return m_nWaitTimeout;
}

bool TcpConnection::IsSessioning() const 
{
	((TcpConnection *)this)->m_Lock.Lock();
	bool b = !m_RequestSession.empty() || !m_PeekSession.empty();
	((TcpConnection *)this)->m_Lock.Unlock();
	return b;
}

void TcpConnection::SetEventInterface(TcpConnectionEvent *pInterface)
{
	m_pEventInterface = pInterface;
}

void TcpConnection::TcpInbox_OnRequestArrived(const Packet &pkg)
{
	HandlePacket(pkg);
}

//�����̼߳���
void TcpConnection::TcpInbox_OnReplyArrived(const Packet &pkg)
{
	m_Lock.Lock();
	//�����ʱ�������Դ˴�client�˵�ack��
	if(m_bTimeout && (m_RequestSession.empty() || pkg.GetHeader().GetID() != m_RequestSession.top().Request->GetHeader().GetID()))
	{
		printf("TcpConnection::TcpInbox_OnReplyArrived timeout reply packet, ignore.");
		m_bTimeout = false;
		m_Lock.Unlock();
		return;
	}
	if(pkg.GetHeader().GetID() != m_RequestSession.top().Request->GetHeader().GetID())
	{
		printf("[%d]m_RequestSession.top().Request.id[%d], reply pkg.id[%d]\r\n", nb::System::Platform::GetCurrentProcessId(), m_RequestSession.top().Request->GetHeader().GetID(), pkg.GetHeader().GetID());
		assert(0);
	}

	while(!m_RequestSync.IsWaiting())	
		;

	m_RequestSession.top().Ack = new Packet(pkg);
	m_bUrgentReplyNeeded = false;
	m_bRequestWaitAgain = false;

	m_RequestSync.Release();

	m_Lock.Unlock();
}

void TcpConnection::TcpInbox_OnRemoteUnknownReasonDisconnected()
{
	HandlePacket(SignalLogout(-1, Header::Priority_Normal));
}

//�����̼߳���
void TcpConnection::HandlePacket(const Packet &pkg)
{
	m_Lock.Lock();
	m_Inbox.PushPacket(pkg);
	//�������Request���һ�δ�յ�ack������Request release�����ñ�־
	if(!m_RequestSession.empty() && !(m_RequestSession.top().Ack))
	{
		while(!m_RequestSync.IsWaiting())
			;

		bool bLogout = pkg.GetHeader().GetMessageType() == Header::Message_Signal_Account_Logout;
		m_bUrgentReplyNeeded = !bLogout;
		m_bRequestWaitAgain = !bLogout;

		m_RequestSync.Release();
	}
	m_Lock.Unlock();
}

bool TcpConnection::CheckUrgentPackets()
{
	bool bRet = true;
	std::vector<Packet> vtPkgs;
	m_Inbox.PopPackets(vtPkgs);
	if(!vtPkgs.empty())
	{
		std::vector<Packet> vtFeedbackPkgs;
		//�˴�����m_pEventInterface�ж��ˣ�Ҫ��һ����Ϊ�գ����Ч��
		m_pEventInterface->TcpConnection_OnUrgentPacketHandleNeeded(this, vtPkgs, vtFeedbackPkgs);
		bRet = PeekFeedback(vtFeedbackPkgs);
	}
	m_bUrgentReplyNeeded = false;
	return bRet;
}
