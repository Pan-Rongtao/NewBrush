#pragma once
#include "Socket.h"

namespace nb{ namespace Network{

class ClientSocket : public Socket
{
public:
	//����
	bool Connect();

public:
	ClientSocket(const std::string &sIp, unsigned int nPort);

};

}}