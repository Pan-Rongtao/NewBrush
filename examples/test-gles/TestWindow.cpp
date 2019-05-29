#include "TestWindow.h"
#include "gles/Display.h"
#include "gles/Egl.h"

#include "core/Exception.h"

using namespace nb::core;
using namespace nb::gl;

void TestWindow::test()
{
	auto display = std::make_shared<Display>(Display::defaultx());
	auto configure = std::make_shared<Configure>(Configure::fromSystemRecommend(display, 0))/*Configure((int *)NULL)*/;
	nb::gl::initialize(display, configure);
	m_window = new Window(200, 200, 800, 480);
	m_window1 = new Window(200, 200, 800, 480);
	m_window->ResizeEvent.addHandler(std::bind(&TestWindow::OnResize, this, std::placeholders::_1));
	m_window->PointerEvent.addHandler(std::bind(&TestWindow::OnPointerAction, this, std::placeholders::_1));
	m_window->KeyEvent.addHandler(std::bind(&TestWindow::OnKeyAction, this, std::placeholders::_1));
	m_window1->ResizeEvent.addHandler(std::bind(&TestWindow::OnResize, this, std::placeholders::_1));
	m_window1->PointerEvent.addHandler(std::bind(&TestWindow::OnPointerAction, this, std::placeholders::_1));
	m_window1->KeyEvent.addHandler(std::bind(&TestWindow::OnKeyAction, this, std::placeholders::_1));

	m_window->setTitle("1111");

	m_window->setX(100);
	int x = m_window->x();

	m_window->setY(100);
	int y = m_window->y();

	m_window->setWidth(200);
	int w = m_window->width();

	m_window->setHeight(200);
	int h = m_window->height();

	while(1) 
	{
		m_window->pending();
		m_window1->pending();
	}
}

void TestWindow::OnResize(const nb::core::Window::ResizeArgs & args)
{
	printf("TestWindow::OnResize--width[%d], height[%d]\r\n", args.width, args.height);
}

void TestWindow::OnPointerAction(const nb::core::Window::PointerEventArgs & args)
{
	printf("TestWindow::OnPointerAction--action[%d], x[%d], y[%d]\r\n", args.action, args.x, args.y);
}

void TestWindow::OnKeyAction(const nb::core::Window::KeyEventArgs & args)
{
	printf("TestWindow::OnKeyAction---action[%d], key[%d],mask[%d]\r\n", args.action, args.key, args.mask);
}
