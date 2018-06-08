/*******************************************************
**	Packet
**
**	
**	����Ⱥ����������ͨ�ŵ����ݰ����ݽṹ��Header��������
**	���ݰ�ͷ�����ĽṹΪ
**
	��ͷ���ݣ� id  +	�������� + �������� + ���ȼ� + ���峤��
	�ֽ�ռλ��  4	    	1	 +	  1		+    1   +	 4
		
**		��Packet�Ķ������������������������ȷ�ϰ�����
**
**		
**		
**		������
**	
********************************************************/
#pragma once
#include <stdio.h>
#include "core/NewBrushDef.h"

namespace nb{ namespace Network {

class NB_EXPORT Header
{
public:
	//��������
	enum ActionProperty : char
	{
		Property_Unknow,												//δ֪
		Property_Request,												//����
		Property_Reply,													//��
		Property_Max,
	};

	//����Ϣ����
	enum MessageType : char
	{
		Message_Unknow,
		Message_Signal_Hello,											//���к�
		Message_Signal_Account_Login,									//�ͻ�������
		Message_Signal_Account_Logout,									//�ͻ�������
		Message_Signal_Server_Shutdown,									//�������ر�
		Message_Binary_Stream,											//����������
		Message_Signal_Max,												//signal����
	};

	//���Ĵ������ȼ�
	enum Priority : char
	{
		Priority_Unknow,
		Priority_Normal,												//��ͨ
		Priority_Urgent,												//����
		Priority_Max,
	};

public:
	//��ȡ����ָ��
	char *GetData() const;

	//��ȡID
	unsigned int GetID() const;

	//��ȡ��������
	ActionProperty GetActionProperty() const;

	//��ȡ��Ϣ����
	MessageType GetMessageType() const;

	//��ȡ���ȼ�
	Priority GetPriority() const;

	//��ȡ���峤��
	unsigned int GetBodySize() const;

public:
	//����һ�����ݰ�ͷ�����Ķ�������ΪProperty_Request�����İ���Ϣ������Message_Unknow�����ȼ�Ϊ��ͨ�����İ��峤��Ϊ0��һ��ӵ�������ͷ��Packet����������
	Header();

	//����һ�����ݰ�ͷ�� ID Ϊ id�����Ķ�������Ϊap�����İ���Ϣ������msgType�����ȼ�Ϊpriority�����İ��峤��ΪbodySize
	Header(unsigned int id, ActionProperty ap, MessageType msgType, Priority priority, unsigned int bodySize);

	//������Header������������һ��Header
	Header(const Header &other);

	~Header();

public:
	void operator = (const Header &other);

public:
	//��ͷ���ֽڳ��ȣ���̬���ɱ䣬������11
	static unsigned int Size();

private:
	char	*m_pData;
};


//�����һ�����������ͷ�Ͱ��岿��
class NB_EXPORT Packet
{
public:
	//��ȡ��ͷ
	Header GetHeader() const;

	//��ȡװ������
	const char *GetData() const;

	//��ȡBody����
	const char *GetBodyData() const;

	//���Body���ݣ�����ΪHeader::BodySize
	void FillBodyData(const char *pData);

	//��ȡ���ܳ���
	int GetSize() const;


public:
	void operator = (const Packet &other);

public:
	//����һ������ֻ�а�ͷ���֣����峤��Ϊ0
	Packet();

	//����һ��������ͷΪheader����������ΪpBody
	Packet(const Header &header, const char *pBody);

	//������Packet����һ����
	Packet(const Packet &other);

	~Packet();


public:
	//��������ȣ�������ͷ�ĵĳ��ȣ�������3 * 1024 * 1024�ֽ�
	static unsigned int MaxSize();

private:
	Header			m_Header;
	char			*m_pData;
};

//���������
class Request : public Packet
{
public:
	Request(unsigned int id, Header::MessageType reqMsgType, Header::Priority priority, const char *pBodyData, int nBodySize);
};
//�����������
class SignalHello : public Request
{
public:
	SignalHello(unsigned int id, Header::Priority priority);
};
class SignalLogin : public Request
{
public:
	SignalLogin(unsigned int id, Header::Priority priority, const std::string &name);
};
class SignalLogout : public Request
{
public:
	SignalLogout(unsigned int id, Header::Priority priority);
};
class SignalServerShutdown : public Request
{
public:
	SignalServerShutdown(unsigned int id, Header::Priority priority);
};
class SignalBinaryStream : public Request
{
public:
	SignalBinaryStream(unsigned int id, Header::Priority priority, const char *pBodyData, int nBodySize);
};

//////////////////////
//��ִ������
class Ack : public Packet
{
public:
	Ack(unsigned int id, Header::MessageType reqMsgType, Header::Priority priority, const char *pBodyData, int nBodySize);
};
//��ִ��������
class AckHello : public Ack
{
public:
	AckHello(unsigned int id, Header::Priority priority);
};
class AckLogin : public Ack
{
public:
	AckLogin(unsigned int id, Header::Priority priority);
};
class AckLogout : public Ack
{
public:
	AckLogout(unsigned int id, Header::Priority priority);
};
class AckServerShutdown : public Ack
{
public:
	AckServerShutdown(unsigned int id, Header::Priority priority);
};
class AckBinaryStream : public Ack
{
public:
	AckBinaryStream(unsigned int id, Header::Priority priority, const char *pBodyData, int nLenBytes);
};

}}
