#pragma once
#include "grpcpp/grpcpp.h"

//����std::unique_ptr ģ�����Ҫ����ģ�����ʵ��ͷ�ļ�����grpc::Server
//�������RpcServiceImpl�Ѵ���������
namespace nb{

class RpcServiceImpl
{
public:
	RpcServiceImpl(const std::string &address);

	const std::string &address() const;

	void startup();

private:
	void runGrpcServer();

	std::string						m_address;
	std::unique_ptr<grpc::Server>	m_server;
};

}