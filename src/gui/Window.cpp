﻿#include "gui/Window.h"
#include "GLFW/glfw3.h"
#include "gles/Egl.h"
#include "gles/Projection.h"
#include "gui/Application.h"
#include "gui/VisualTreeHelper.h"
#include "media/ImageSource.h"
#include "gui/WindowCollection.h"
#include "core/Singleton.h"

using namespace nb;
using namespace gl;
using namespace gui;

std::shared_ptr<gl::Context> Window::drawContext = nullptr;
static bool	g_windowSystemInitialized = false;

Window::Window()
	: WindowState([&](WindowStateE v) {set(WindowStateProperty(), v); }, [&]()->WindowStateE& {return get<WindowStateE>(WindowStateProperty()); })
	, WindowStyle([&](WindowStyleE v) {set(WindowStyleProperty(), v); }, [&]()->WindowStyleE& {return get<WindowStyleE>(WindowStyleProperty()); })
	, Topmost([&](bool v) {set(TopmostProperty(), v); }, [&]()->bool& {return get<bool>(TopmostProperty()); })
	, Left([&](float v) {set(LeftProperty(), v); }, [&]()->float& {return get<float>(LeftProperty()); })
	, Top([&](float v) {set(TopProperty(), v); }, [&]()->float& {return get<float>(TopProperty()); })
	, Title([&](std::string v) {set(TitleProperty(), v); }, [&]()->std::string& {return get<std::string>(TitleProperty()); })
	, Icon([&](shared_ptr<ImageSource> v) {set(IconProperty(), v); }, [&]()->shared_ptr<ImageSource>& {return get<shared_ptr<ImageSource>>(IconProperty()); })
	, m_implWindow(nullptr)
{
	init();

	drawContext = std::make_shared<gl::Context>();
	m_implWindow = glfwCreateWindow(800, 600, "newbrush", nullptr, nullptr);
	int x, y, w, h;
	glfwGetWindowPos(m_implWindow, &x, &y);
	glfwGetWindowSize(m_implWindow, &w, &h);
	//一定不能去掉下面四句（需要在回调生效前设置）以便不触发回调，否则会更新layout，而此时Width或Height是NAN
	Left = (float)x;
	Top = (float)y;
	Width = (float)w;
	Height = (float)h;
	glfwSetWindowUserPointer(m_implWindow, this);
	glfwSetWindowPosCallback(m_implWindow, [](GLFWwindow*w, int x, int y) { static_cast<Window *>(glfwGetWindowUserPointer(w))->posCallback(x, y); });
	glfwSetWindowSizeCallback(m_implWindow, [](GLFWwindow*w, int width, int height) { static_cast<Window *>(glfwGetWindowUserPointer(w))->sizeCallback(width, height); });
	glfwSetFramebufferSizeCallback(m_implWindow, [](GLFWwindow*w, int width, int height) { static_cast<Window *>(glfwGetWindowUserPointer(w))->sizeCallback(width, height); });
	glfwSetMouseButtonCallback(m_implWindow, [](GLFWwindow*w, int button, int action, int mods) { static_cast<Window *>(glfwGetWindowUserPointer(w))->mouseButtonCallback(button, action, mods); });
	glfwSetCursorPosCallback(m_implWindow, [](GLFWwindow*w, double x, double y) { static_cast<Window *>(glfwGetWindowUserPointer(w))->cusorPosCallback(x, y); });
	glfwSetCursorEnterCallback(m_implWindow, [](GLFWwindow*w, int entered) { static_cast<Window *>(glfwGetWindowUserPointer(w))->cusorPosEnterCallback(entered); });
	glfwSetScrollCallback(m_implWindow, [](GLFWwindow*w, double x, double y) { static_cast<Window *>(glfwGetWindowUserPointer(w))->scrollCallback(x, y); });
	glfwSetKeyCallback(m_implWindow, [](GLFWwindow*w, int key, int scancode, int action, int mods) { static_cast<Window *>(glfwGetWindowUserPointer(w))->keyCallback(key, scancode, action, mods); });
	glfwSetWindowFocusCallback(m_implWindow, [](GLFWwindow*w, int focused) { static_cast<Window *>(glfwGetWindowUserPointer(w))->focusCallback(focused); });
	glfwSetWindowRefreshCallback(m_implWindow, [](GLFWwindow*w) { static_cast<Window *>(glfwGetWindowUserPointer(w))->refreshCallback(); });
	glfwSetWindowCloseCallback(m_implWindow, [](GLFWwindow*w) { static_cast<Window *>(glfwGetWindowUserPointer(w))->closeCallback(); });
	glfwSetWindowIconifyCallback(m_implWindow, [](GLFWwindow*w, int iconified) { static_cast<Window *>(glfwGetWindowUserPointer(w))->iconifyCallback(iconified); });
	glfwSetWindowMaximizeCallback(m_implWindow, [](GLFWwindow*w, int iconified) { static_cast<Window *>(glfwGetWindowUserPointer(w))->iconifyCallback(iconified); });

	sizeCallback((int)Width(), (int)Height());
	Singleton<WindowCollection>::get()->push(this);

	PropertyChanged += std::bind(&Window::onPropertyChanged, this, std::placeholders::_1);
}

Window::~Window()
{
	destroyWindow();
	Singleton<WindowCollection>::get()->erase(this);
}

void Window::active()
{
	glfwFocusWindow(m_implWindow);
}

void Window::show()
{
	glfwShowWindow(m_implWindow);
}

void Window::hide()
{
	glfwHideWindow(m_implWindow);
}

void Window::close()
{
	if (m_onDispatching)	return;
	m_onDispatching = true;
	closeCallback();
	m_onDispatching = false;
}

Size Window::measureOverride(const Size & availableSize)
{
	if (Content())
	{
		Content()->measure({ Width(), Height() });
		//return Content()->DesiredSize;
		return availableSize;
	}
	else
	{
		return ContentControl::measureOverride(availableSize);
	}
}

Size Window::arrangeOverride(const Size & finalSize)
{
	if (Content())
	{
		Content()->arrage(Rect(0.0, 0.0, Width(), Height()));
	}
	return finalSize;
}

void loopTest(int x, int y, std::shared_ptr<Window> w, UIElement *e, std::vector<UIElement *> &hits)
{
	auto hit = [x, y, w](std::shared_ptr<RenderObject> obj)
	{
		if (!obj || obj->model() == nullptr)	return false;
		return obj->model()->orthoHitTest((float)x, (float)y);
	};

	auto count = VisualTreeHelper::getChildCount(e);
	for (int i = 0; i != count; ++i)
	{
		auto child = VisualTreeHelper::getChild(e, i);
		if (!child)	continue;
		if (hit(child->Renderer()))
			hits.push_back(child);
		if (VisualTreeHelper::getChildCount(child) > 0)
		{
			loopTest(x, y, w, child, hits);
		}
	}
};

std::vector<UIElement *> Window::hitElements(int x, int y) const
{
	std::vector<UIElement *> hits;
	//loopTest(x, y, m_glWindow, const_cast<Window *>(this), hits);
	return hits;
}

void Window::onPropertyChanged(const PropertyChangedArgs & arg)
{
	if (arg.dp == WindowStateProperty())
	{
		auto state = any_cast<WindowStateE>(arg.value);
		switch (state)
		{
		case WindowStateE::Normal:		glfwRestoreWindow(m_implWindow);	break;
		case WindowStateE::Maximized:	glfwMaximizeWindow(m_implWindow);	break;
		case WindowStateE::Minimized:	glfwIconifyWindow(m_implWindow);	break;
		default:															break;
		}
	}
	else if (arg.dp == WindowStyleProperty())
	{
	}
	else if (arg.dp == TopmostProperty())
	{
		glfwSetWindowAttrib(m_implWindow, GLFW_FLOATING, any_cast<bool>(arg.value));
	}
	else if (arg.dp == LeftProperty() || arg.dp == TopProperty())
	{
		glfwSetWindowPos(m_implWindow, (int)Left(), (int)Top());
	}
	else if (arg.dp == TitleProperty())
	{
		glfwSetWindowTitle(m_implWindow, any_cast<std::string>(arg.value).data());
	}
	else if (arg.dp == IconProperty())
	{
		auto bm = any_cast<std::shared_ptr<ImageSource>>(arg.value)->Bm();
		GLFWimage img;
		img.width = bm->width();
		img.height = bm->height();
		img.pixels = (unsigned char *)bm->data();
		glfwSetWindowIcon(m_implWindow, 1, &img);
	}
}

void Window::posCallback(int x, int y)
{
	LocationChanged.invoke({});
}

void Window::sizeCallback(int width, int height)
{
	gl::getProjection()->ortho(0.0f, (float)width, (float)height, 0.0f, 1000.0f, -1000.0f);
	gl::viewport(0, 0, width, height);
	Width = (float)width;
	Height = (float)height;
	updateLayout();
}

void Window::frameBufferSizeCallback(int width, int height)
{
}

void Window::mouseButtonCallback(int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_1)
	{
		double x, y;
		glfwGetCursorPos(m_implWindow, &x, &y);
		auto hits = hitElements((int)x, (int)y);
		for (auto e : hits)
		{
			e->MouseEnter.invoke({});
			e->onMouseEnter();
			e->MouseMove.invoke({});
			e->onMouseMove();
		}
	}
}

void Window::cusorPosCallback(double x, double y)
{
}

void Window::cusorPosEnterCallback(int entered)
{
}

void Window::scrollCallback(double x, double y)
{
}

void Window::keyCallback(int key, int scancode, int action, int mods)
{
}

void Window::focusCallback(int focused)
{
}

void Window::refreshCallback()
{
}

void Window::closeCallback()
{
	CancelEventArgs args;
	onClosing(args);
	if (!args.cancel)
	{
		destroyWindow();                                                                 
		onClosed(args);
		Singleton<WindowCollection>::get()->erase(this);
	}
}

void Window::iconifyCallback(int iconified)
{
	StateChanged.invoke({});
}

void Window::maximizeCallback(GLFWwindow * window, int maximized)
{
	StateChanged.invoke({});
}

void Window::init()
{
	if (g_windowSystemInitialized)	return;

	glfwSetErrorCallback([](int error, const char*str) {printf("error:%s\n", str); });
	glfwInit();
	glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
	glfwWindowHint(GLFW_CONTEXT_CREATION_API, GLFW_EGL_CONTEXT_API);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	g_windowSystemInitialized = true;
}

void Window::deinit()
{
	glfwTerminate();
	g_windowSystemInitialized = false;
}

void Window::destroyWindow()
{
	if (!m_implWindow)
		return;
	glfwDestroyWindow(m_implWindow);
	m_implWindow = nullptr;
	if (Singleton<WindowCollection>::get()->windows().empty())
		deinit();
}

void Window::swapBuffers() const
{
	glfwMakeContextCurrent(m_implWindow);
	glfwSwapBuffers(m_implWindow);
}

void Window::waitEvent()
{
	if (g_windowSystemInitialized)
		glfwWaitEvents();
}

DependencyProperty Window::WindowStateProperty()
{
	static auto dp = DependencyProperty::registerDependency<Window, WindowStateE>("WindowState", WindowStateE::Normal);
	return dp;
}

DependencyProperty Window::WindowStyleProperty()
{
	static auto dp = DependencyProperty::registerDependency<Window, WindowStyleE>("WindowStyle", WindowStyleE::SizeBox);
	return dp;
}

DependencyProperty Window::TopmostProperty()
{
	static auto dp = DependencyProperty::registerDependency<Window, bool>("Topmost", false);
	return dp;
}

DependencyProperty Window::LeftProperty()
{
	static auto dp = DependencyProperty::registerDependency<Window, float>("Left", 0.0);
	return dp;
}

DependencyProperty Window::TopProperty()
{
	static auto dp = DependencyProperty::registerDependency<Window, float>("Top", 0.0);
	return dp;
}

DependencyProperty Window::TitleProperty()
{
	static auto dp = DependencyProperty::registerDependency<Window, std::string>("Title", std::string());
	return dp;
}

DependencyProperty Window::IconProperty()
{
	static auto dp = DependencyProperty::registerDependency<Window, shared_ptr<ImageSource>>("Icon", std::make_shared<ImageSource>());
	return dp;
}

void Window::onActivated(const EventArgs & args)
{
	Activated.invoke({ args });
}

void Window::onDeactivated(const EventArgs & args)
{
	Deactivated.invoke({ args });
}

void Window::onClosed(const EventArgs & args)
{
	Closed.invoke({ args });
}

void Window::onClosing(const CancelEventArgs & args)
{
	Closing.invoke({ args });
}

void Window::onLocationChanged(const EventArgs & args)
{
	LocationChanged.invoke({ args });
}

void Window::onStateChanged(const EventArgs & args)
{
	StateChanged.invoke({ args });
}

void Window::onSourceInitiallized(const EventArgs & args)
{
	SourceInitiallized.invoke({ args });
}

void Window::onContentRendered(const EventArgs & args)
{
	ContentRendered.invoke({ args });
}
