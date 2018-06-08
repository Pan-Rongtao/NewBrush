/*******************************************************
**	TcpServer
**
**	����Tcp�ķ����
**	
**	��������������TcpЭ��ķ����ģ�͵����ݽṹ
**	
**	���ṩ�����в�������ͬ����
**
**		
**		
**		������
**	
********************************************************/
#pragma once
#include <string>
#include "ReceivePacket.h"
#include "TcpConnection.h"

namespace nb{ namespace Network{

class TcpServerEvent;
class TcpServer_Internal;
class NB_EXPORT TcpServer
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

	//��ѯ������״̬�Ƿ�Ϊ������
	bool IsStartupped() const;

	//��ͻ���Conn�������ݣ����pDataΪNULL�������Դ˴β���
	//�쳣��nLenBytes < 0
	Packet SendData(TcpConnection *Conn, const char *pData, int nLenBytes);

	//������ȡ�ͻ��˵��ż����ݣ�����������������ݣ����ż����ǿյ�
	void PeekClientPackets(std::vector<ReceivePacket> &vtRpkgs);

	//����ͨ�ų�ʱʱ�䣬-1��ʾ������
	void SetTimeoutSpan(int ms);

	//��ȡͨ�ų�ʱʱ��
	int GetTimeoutSpan() const;

	void SetEventInterface(TcpServerEvent *pEventInterface);

	void RemoveConnection(TcpConnection *Conn);

public:
	TcpServer(const std::string &sIp, unsigned int nPort);
	~TcpServer();

private:
	TcpServer(const TcpServer &other) {}
	void operator = (const TcpServer &other) {}

	TcpServer_Internal	*m_pInternal;
};

class TcpServerEvent
{
public:
	virtual void TcpServer_OnUrgentPacketHandleNeeded(TcpConnection *Conn, const std::vector<Packet> &vtRequestPkgs, std::vector<Packet> &vtFeedbackPkgs) {(void)vtRequestPkgs; (void)vtFeedbackPkgs;}
};

}}