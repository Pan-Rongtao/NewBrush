/*******************************************************
**	Buffer
**
**	�ڴ��
**	
**	������
**	�������ڶ����������Ĵ���
**
**		
**		
**		������
**	
********************************************************/
#pragma once
#include "Packet.h"

namespace nb{ namespace Network{

class NB_EXPORT Buffer
{
public:
	//��ȡ����ͷ��
	char *GetData();
	const char *GetData() const;

	//��ȡ�����ֽ���
	int GetSize() const;

public:
	//����һ��Buffer�� ��BufferΪ�գ�����Ϊ0
	Buffer();

	//����һ��Buffer������ΪnLenBytes
	Buffer(unsigned int nLenBytes);

	//����һ��Buffer������ΪnLenBytes������pData��ʼ��������������ڴ�
	Buffer(const char *pData, unsigned int nLenBytes);

	//������Buffer����һ��Buffer
	Buffer(const Buffer &other);

	~Buffer();

public:
	void operator = (const Buffer &other);

private:
	char			*m_pData;
	int				m_nLen;
};

class BufferDecoder
{
public:
	//����һ��Buffer��������������buffer���н���
	BufferDecoder(Buffer buffer);

	//���벢��ȡ��ͷ
	Header GetHeader() const;

	//���벢��ȡ��������
	const char *GetBodyData() const;


private:
	Buffer	m_buffer;
};

}}