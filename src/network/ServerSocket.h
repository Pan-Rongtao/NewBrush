#pragma once
#include "Socket.h"

namespace nb{ namespace Network{

class ServerSocket : public Socket
{
public:
	//��
	bool Bind();

	//������������
	Socket *Listen() const;

public:
	ServerSocket(const std::string &sIp, unsigned int nPort);
	virtual ~ServerSocket();
};

}}