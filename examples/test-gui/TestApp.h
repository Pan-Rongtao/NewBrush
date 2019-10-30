#pragma once
#include "../TestBase.h"
#include "gui/Application.h"
#include "gui/Window.h"
#include "gui/Shape.h"

using namespace nb;
using namespace nb::gui;

class TestApp : public TestBase
{
public:
	virtual void test();

private:
	std::shared_ptr<nb::gui::Window> m_window;
};
