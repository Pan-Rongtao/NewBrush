#include "TestIpcServer.h"
#include "core/Exception.h"

using namespace nb::Core;
using namespace nb::Network;
using namespace nb::System;

int main(int argc, char *argv[])
{
	TestIpcServer sv;
//	try
	{
	//	xx.Peek();
		sv.SendEvents();
	}
// 	catch(ExceptionPtr ex)
// 	{
// 		printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\r\n\r\n");
// 		printf("�쳣: %s\r\n", ex->GetErrorMessageData());
// 		printf("�ļ�: %s\r\n", ex->GetFileNameData());
// 		printf("����: %d\r\n\r\n", ex->GetFileLine());
// 		printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\r\n\r\n");
// 	}

	return 0;
}