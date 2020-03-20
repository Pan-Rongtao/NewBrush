#include "newbrush/gui/Application.h"
#include "newbrush/core/Timer.h"
#include "newbrush/gui/Window.h"
#include "newbrush/core/Log.h"
#include <GLES2/gl2.h>
#include "newbrush/core/Singleton.h"

using namespace nb;

Application *Application::g_app = nullptr;
Application::Application()
	: m_shutdownMode(ShutdownModeE::OnLastWindowClose)
	, m_exitFlag(false)
{
	if (g_app)
	{
		nbThrowException(std::logic_error, "create two application");
	}
	g_app = this;
	Singleton<WindowCollection>::get()->WindowClosed += std::bind(&Application::onWindowClosed, this, std::placeholders::_1);
	Singleton<WindowCollection>::get()->WindowFocus += std::bind(&Application::onWindowFocused, this, std::placeholders::_1);
}

Application::~Application()
{
}

Application *Application::current()
{
	return g_app;
}

void Application::setShutdownMode(ShutdownModeE mode)
{
	m_shutdownMode = mode;
}

ShutdownModeE Application::shutdownMode() const
{
	return m_shutdownMode;
}

const WindowCollection &Application::windows() const
{
	return *Singleton<WindowCollection>::get();
}

void Application::setMainWindow(Window * w)
{
	Singleton<WindowCollection>::get()->setMainWindow(w);
}

Window * Application::mainWindow()
{
	return Singleton<WindowCollection>::get()->mainWindow();
}

int Application::run(int argc, char *argv[])
{
	std::vector<std::string> args;
	for (int i = 0; i < argc; ++i)
	{
		args.push_back(argv[i]);
	}
	onStartUp({ args });

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(250 / 255.0f, 235 / 255.0f, 215 / 255.0f, 1.0f);
	try
	{
		while (!m_exitFlag)
		{
			auto msg = pickMessage();
			if (msg.first != -1)
			{
				UserMessage.invoke({ (uint32_t)msg.first, msg.second });
			}
			for (auto const w : Singleton<WindowCollection>::get()->windows())
			{
				w->render();
			}
			Timer::driveInLoop();
			Window::pollEvents();
		}
	}
	catch (std::exception &e)	{ UnhandledException.invoke({ e }); }
	catch (...)					{ UnhandledExtraException.invoke({}); }
	return 0;
}

void Application::shutdown()
{
	shutdown(0);
}

void Application::shutdown(int exitCode)
{
	m_exitFlag = true;
	for (auto const &w : Singleton<WindowCollection>::get()->windows())
	{
		w->_close(false);
	}

	Singleton<WindowCollection>::get()->windows().clear();
	onExit({ exitCode });
}

void nb::Application::sendMessage(uint32_t msg, const std::string &data)
{
	m_mutex.lock();
	m_msgQueue.push({ msg,data });
	m_mutex.unlock();
}

void Application::onActivated(const EventArgs & args)
{
	Activated.invoke(args);
}

void Application::onDeactivated(EventArgs & args)
{
	Deactivated.invoke(args);
}

void Application::onExit(const ExitEventArgs & args)
{
	Exit.invoke(args);
}

void Application::onLoadCompleted(const EventArgs & args)
{
	LoadCompleted.invoke(args);
}

void Application::onSessionEnding(const SessionEndingCancelEventArgs & args)
{
	SessionEnding.invoke(args);
}

void Application::onStartUp(const StartupEventArgs & args)
{
	Startup.invoke(args);
}

void Application::onWindowClosed(const WindowCollection::WindowClosedEventArgs & args)
{
	auto mode = shutdownMode();
	if ((mode == ShutdownModeE::OnLastWindowClose && Singleton<WindowCollection>::get()->windows().empty())
		|| (mode == ShutdownModeE::OnMainWindowClose && args.isMain)
		|| (mode == ShutdownModeE::OnExplicitShutdown && Singleton<WindowCollection>::get()->windows().empty() && m_exitFlag))
	{
		shutdown();
	}
}

void Application::onWindowFocused(const WindowCollection::WindowFocusEventArgs & args)
{
	if (args.focused)
	{

	}
	else
	{

	}
}

std::pair<uint32_t, std::string> Application::pickMessage()
{
	m_mutex.lock();
	std::pair<uint32_t, std::string> ret = { -1,"" };
	if (!m_msgQueue.empty())
	{
		ret = m_msgQueue.front();
		m_msgQueue.pop();
	}
	m_mutex.unlock();
	return ret;
}
