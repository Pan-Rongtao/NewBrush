/*******************************************************
**	TcpClient
**
**	����Tcp�Ŀͻ���
**	
**	��������������TcpЭ��Ŀͻ���ģ�͵����ݽṹ
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
#include <vector>
#include "Packet.h"

namespace nb{ namespace Network{

class TcpClientEvent;
class TcpClient_Internal;
class NB_EXPORT TcpClient
{
public:
	//��¼���ò������������ӷ�������������ipΪsHostIp���������˿ں�ΪnPort
	//�쳣�����������ɴ�
	//�쳣�����ؿͻ��������ڷ��������Ѵ���
	bool Login(const std::string &sHostIp, int nPort);

	//�ǳ����ò�����������֪�������Լ���������Ϊ
	void Logout();

	//��ѯ�Ƿ�������״̬
	bool IsConnected() const;

	std::string GetName() const;

	//��ȡ��������ַ
	std::string GetHostIp() const;
	unsigned int GetHostPort() const;

	//�����������һ�鳤��ΪnLenBytes�ֽڵ�����pData
	//���pDataΪNULL�����������Ͷ���
	//�쳣��nLenBytes < 0
	Packet SendData(const char *pData, int nLenBytes);

	//������ȡ����˵��ż����ݣ�����������������ݣ����ż����ǿյ�
	void PeekPacket(std::vector<Packet> &vtPkgs);

	void PeekFeedback(std::vector<Packet> &feedbackPkgs);

	void SetTimeoutSpan(int ms);

	int GetTimeoutSpan() const;

	void SetEventInterface(TcpClientEvent *pInterface);


public:
	//����һ��TcpClient����
	TcpClient();
	TcpClient(const std::string &name);
	~TcpClient();

private:
	TcpClient(const TcpClient &other) {}
	void operator = (const TcpClient &other) {}

	TcpClient_Internal		*m_pInternal;
	unsigned int			m_PacketID;
};

class TcpClientEvent
{
public:
	//�������账������
	virtual void TcpClient_OnUrgentPacketHandleNeeded(const std::vector<Packet> &vtRequestPkg, std::vector<Packet> &vtFeedbacks) {(void)vtRequestPkg; (void)vtFeedbacks;}
};

}}
