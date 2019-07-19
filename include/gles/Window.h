#pragma once
#include "../core/Def.h"
#include "../core/Window.h"

namespace nb{ namespace gl{

class NB_API Window : public nb::core::Window
{
public:	
	//����һ��Window�������ı���Ϊ�գ�����Ϊ(x-middle, y-middle, 800, 480)
	Window();

	//����һ��Window�������ı���Ϊ�գ�����Ϊ(x-middle, y-middle, width, height)
	Window(int width, int height);

	//����һ��Window�������ı���Ϊ�գ�����Ϊ(x, y, width, height)
	Window(int x, int y, int width, int height);

	//����һ��Window�������ı���Ϊtitle������Ϊ(x-middle, y-middle, 800, 480)
	explicit Window(const std::string &title);

	//����һ��Window�������ı���Ϊtitle������Ϊ(x-middle, y-middle, width, height)
	Window(const std::string &title, int width, int height);

	//����һ��Window�������ı���Ϊtitle������Ϊ(x-middle, y-middle, width, height)
	Window(const std::string &title, int x, int y, int width, int height);

	~Window();
};

}}
