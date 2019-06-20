#pragma once
#include "../core/Def.h"
#include "../core/Event.h"
#include <string>

namespace nb{ namespace core{

class Window_Internal;
class NB_API Window
{
public:
	enum KeyAction
	{
		KeyAction_Down,
		KeyAction_Up,
		KeyAction_LongPress,
	};

	enum KeyCode
	{
		VKey_Unknown = -1,

		VKey_Esc = 0x00,

		VKey_F1 = 0x01,
		VKey_F2 = 0x02,
		VKey_F3 = 0x03,
		VKey_F4 = 0x04,
		VKey_F5 = 0x05,
		VKey_F6 = 0x06,
		VKey_F7 = 0x07,
		VKey_F8 = 0x08,
		VKey_F9 = 0x09,
		VKey_F10 = 0x0A,
		VKey_F11 = 0x0B,
		VKey_F12 = 0x0C,

		VKey_Space = 0x20,

		VKey_A = 0x41,
		VKey_B,
		VKey_C,
		VKey_D,
		VKey_E,
		VKey_F,
		VKey_G,
		VKey_H,
		VKey_I,
		VKey_J,
		VKey_K,
		VKey_L,
		VKey_M,
		VKey_N,
		VKey_O,
		VKey_P,
		VKey_Q,
		VKey_R,
		VKey_S,
		VKey_T,
		VKey_U,
		VKey_V,
		VKey_W,
		VKey_X,
		VKey_Y,
		VKey_Z,

		VKey_Left,
		VKey_Up,
		VKey_Right,
		VKey_Down,

		VKey_Add,
		VKey_Sub,
	};

	enum PointerAction
	{
		PointerAction_Down,
		PointerAction_Move,
		PointerAction_Up,
		PointerAction_Click,
		PointerAction_LongPress,
	};

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

public:
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

	//��鴰���¼�
	void pending();

	//���ھ��
	long handle() const;

	//�ö�����windows����Ч��
	void setTopMost(bool topMost);
	bool topMost() const;

	//�ߴ������¼�
	struct ResizeArgs { int width; int height; };
	nb::core::Event<ResizeArgs>			ResizeEvent;

	//����¼�
	struct PointerEventArgs { PointerAction action; int x; int y; };
	nb::core::Event<PointerEventArgs>	PointerEvent;

	//�����¼�
	struct KeyEventArgs { KeyAction action; KeyCode key; int mask; };
	nb::core::Event<KeyEventArgs>		KeyEvent;

private:
	Window_Internal	*m_internal;
};

}}
