#include "gui/Application.h"
#include "core/Exception.h"
#include "gui/Window.h"
#include "WindowCollections.h"

using namespace nb::core;
using namespace nb::gui;

static std::shared_ptr<Application> g_app;
Application::Application()
{
	if (g_app)	throw std::logic_error("create tow application");
	g_app = std::shared_ptr<Application>(this);
}

Application::~Application()
{
}

std::shared_ptr<Application> Application::current()
{
	return g_app;
}

int Application::run()
{
	try 
	{
		for (auto w : WindowCollections::Windows())
		{
			w->onRender(w->DrawContext());
			w->measure(Size((float)w->Width, (float)w->Height));
		}
		return nb::gl::Application::run();
	}
	catch(Exception &e)
	{
		printf("exception: %s\r\n", e.what().data());
	}
	catch(...)
	{
		printf("other exception\r\n");
	}
	return 1;
}
