#include "TestBase.h"
#include "TestWindow.h"
#include "TestApp.h"

template <class T>
class TestHandle
{
public:
	TestHandle<T>() {m_pInter = new T();}
	~TestHandle() {delete m_pInter;}

	T * operator ->() {return (T *)m_pInter;}

private:
	void *m_pInter;
};

int main(int argc, char *argv[])
{
	try{
		TestHandle<TestApp> test;
		test->Test();
	}
	catch(nb::Core::ExceptionPtr e)
	{
		printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\r\n\r\n");
		printf("�쳣: %s\r\n", e->GetErrorMessageData());
		printf("�ļ�: %s\r\n", e->GetFileNameData());
		printf("����: %d\r\n\r\n", e->GetFileLine());
		printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\r\n\r\n");
	}
	catch(...)
	{


	}

	return 0;
}
