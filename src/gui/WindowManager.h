#pragma once

namespace nb{ namespace gui{

class Window;
class WindowManager
{
public:
	//
	static void Push(nb::gui::Window *window);

	//
	static void Erease(nb::gui::Window *window);

	//��ȡ���ڸ���
	static int GetCount();

	//����һ������
	static nb::gui::Window *At(int index);
};

}}
