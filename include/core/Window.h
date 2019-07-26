#pragma once
#include "../core/Def.h"
#include "../core/Event.h"
#include <string>

namespace nb{ namespace core{

enum class WindowStateE
{
	Normal,
	Maximized,
	Minimized,
	FullScreen,
};

enum class WindowStyleE
{
	None,
	Fixed,
	SizeBox,
};

enum class KeyCodeE
{
	Unknown = -1,
	Esc		= 0x00,
	F1		= 0x01, F2,F3,F4,F5,F6,F7,F8,F9,F10,F11,F12,
	Space	= 0x20,
	A		= 0x41, B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z,
	Left,Up,Right,Down,
	Add,Sub,
};

class Window_Internal;
class NB_API Window
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
	virtual ~Window();

	//���ô��ڱ���
	void setTitle(const std::string &title);

	//��ȡ���ڱ���
	std::string title() const;

	//���ô���λ��x�������win32�����£�Ϊ�߿����߾ࣩ
	void setX(int x);

	//��ȡ����x�������win32�����£�Ϊ�߿����߾ࣩ
	int x() const;

	//���ô���λ��y�������win32�����£�Ϊ�߿���ϱ߾ࣩ
	void setY(int y);

	//��ȡ����y�������win32�����£�Ϊ�߿���ϱ߾ࣩ
	int y() const;

	//���ô��ڿͻ��˿��width
	//�쳣��width < 0
	void setWidth(int width);

	//��ȡ���ڿͻ��˿��
	int width() const;

	//���ô��ڿͻ��˸߶�
	//�쳣��height < 0
	void setHeight(int height);

	//��ȡ���ڿͻ��˸߶�
	int height() const;	

	//��ȡ�ͻ���
	int clientWidth() const;
	int clientHeight() const;

	//��鴰���¼�
	void pending();

	//���ھ��
	long handle() const;

	//�����ö�����windows����Ч��
	void setTopMost(bool topMost);
	bool topMost() const;

	//����״̬
	void setWindowState(WindowStateE state);
	WindowStateE getWindowState() const;

	//������ʽ
	void setWindowStyle(WindowStyleE style);
	WindowStyleE getWindowStyle() const;

	//��ʾ���أ�����������ʾ���أ����Ǽ��ǰ̨
	void show(bool show);
	bool isShow() const;

	//����ڣ��������δ��ʾ������Ч
	void active();

	//�ߴ������¼�
	struct ResizeArgs { int width; int height; };
	nb::core::Event<ResizeArgs>			ResizeEvent;

	//�������¼�
	struct MouseEnterEventArgs { };
	nb::core::Event<MouseEnterEventArgs>		MouseEnterEvent;

	//����ƶ��¼�
	struct MouseMoveEventArgs { int x; int y; };
	nb::core::Event<MouseMoveEventArgs>			MouseMoveEvent;

	//����뿪�¼�
	struct MouseLeaveEventArgs { };
	nb::core::Event<MouseLeaveEventArgs>		MouseLeaveEvent;

	//�������¼�
	struct MouseLeftButtonEventArgs { bool pressed; int x; int y; };
	nb::core::Event<MouseLeftButtonEventArgs>	MouseLeftButtonEvent;

	//����Ҽ��¼�
	struct MouseRightButtonEventArgs { bool pressed; int x; int y; };
	nb::core::Event<MouseRightButtonEventArgs>	MouseRightButtonEvent;

	//����м��¼�
	struct MouseMiddleButtonEventArgs { bool pressed; int x; int y; };
	nb::core::Event<MouseMiddleButtonEventArgs>	MouseMiddleButtonEvent;

	//�������¼�
	struct MouseWheelEventArgs { int delta; };
	nb::core::Event<MouseWheelEventArgs>		MouseWheelEvent;

	//�����¼�
	struct KeyEventArgs { bool down; KeyCodeE key; int mask; };
	nb::core::Event<KeyEventArgs>				KeyEvent;

private:
	Window_Internal	*m_internal;
};

}}
