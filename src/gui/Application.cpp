#include "gui/Application.h"
#include "core/Exception.h"
#include "gui/Window.h"
#include "core/ApplicationRealize.h"
#include "Application_Internal.h"

using nb::Gui::Application;
using nb::Core::ExceptionPtr;

NB_OBJECT_TYPE_IMPLEMENT(Application, nbObject, NULL, NULL);

Application::Application()
{
	m_internal = new nb::Gui::Application_Internal();
	nbCoreApplication::InitGlobal();
}

Application::~Application()
{
	delete m_internal;
}

int Application::Run()
{
	try
	{
		m_internal->Run();
		return 0;
	}
	catch(ExceptionPtr &ex)
	{
		printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\r\n\r\n");
		printf("�쳣: %s\r\n", ex->GetErrorMessageData());
		printf("�ļ�: %s\r\n", ex->GetFileNameData());
		printf("����: %d\r\n\r\n", ex->GetFileLine());
		printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\r\n\r\n");
	}
	catch(...)
	{
		printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\r\n\r\n");
		printf("δ������쳣: ����NewBrush�쳣��\r\n\r\n");
		printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\r\n\r\n");
	}
	return 1;
}
