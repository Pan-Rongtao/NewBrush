#pragma once

namespace nb{ namespace Gui{

class Window;
class WindowManager
{
public:
	//
	static void Push(nb::Gui::Window *window);

	//
	static void Erease(nb::Gui::Window *window);

	//��ȡ���ڸ���
	static int GetCount();

	//����һ������
	static nb::Gui::Window *At(int index);
};

}}
