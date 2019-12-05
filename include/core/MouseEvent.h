#pragma once
#include "../core/InputEvent.h"
#include "../core/Point.h"

namespace nb {

enum class MouseButtonE : uint8_t
{
	Left,		//��ť
	Middle,		//�м䰴ť
	Right,		//�Ұ�ť
};

enum class MouseButtonStateE : uint8_t
{
	Released,	//���ͷ�
	Pressed,	//��ѹ��
};

class InputElement;
class NB_API MouseEventArgs : public InputEventArgs
{
public:
	MouseEventArgs(int timestamp);

	nb::Point getPosition(std::shared_ptr<InputElement> relativeTo);			//��ȡ��������ָ��Ԫ�ص�λ��

	MouseButtonStateE	LeftButton;		//��ť״̬
	MouseButtonStateE	MiddleButton;	//�м䰴ť״̬
	MouseButtonStateE	RightButton;	//�Ұ�ť״̬
};

class NB_API MouseButtonEventArgs : public MouseEventArgs
{
public:
	MouseButtonEventArgs(int timestamp, MouseButtonE button);

	MouseButtonE		ChangedButton;	//�����İ�ť
	MouseButtonStateE	ButtonState;	//��ť״̬
	int					ClickCount;		//����������ɴ�������˫�����������ж�
};

class NB_API MouseWheelEventArgs : public MouseEventArgs
{
public:
	MouseWheelEventArgs(int timestamp, int delta);

	int	Delta;							//����ֵ
};

}