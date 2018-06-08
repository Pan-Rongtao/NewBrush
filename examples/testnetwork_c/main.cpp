#include <stdlib.h>
#include "TestIpcClient.h"
#include "core/Exception.h"

using namespace nb::Core;
using namespace nb::Network;

int main(int argc, char *argv[])
{
	TestIpcClient xx;
	try{
	xx.Send();
	}
	catch(ExceptionPtr ex)
	{
		printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\r\n\r\n");
		printf("�쳣: %s\r\n", ex->GetErrorMessageData());
		printf("�ļ�: %s\r\n", ex->GetFileNameData());
		printf("����: %d\r\n\r\n", ex->GetFileLine());
		printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\r\n\r\n");
	}
	return 0;
}
