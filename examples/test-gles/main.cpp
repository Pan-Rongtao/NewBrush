﻿#include "TestEgl.h"
#include "TestApplication.h"
#include "TestConfigure.h"
#include "TestModel.h"
#include "TestTexture2D.h"
#include "TestSoureDecoder.h"

int main(int argc, char* argv[])
{
	std::vector<int> vt0;
	std::vector<int> vt1;
	bool b = vt0 == vt1;
	try{
		TestHandle<TestApplication> test;
		test->test();
	}
	catch (std::exception &e)
	{
		printf("exception: %s\r\n", e.what());
	}
	catch(...)
	{
		printf("other exception.\r\n");
	}
}
