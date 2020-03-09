#pragma once
#include "newbrush/gui/ContentControl.h"

namespace nb{

enum class ClickModeE
{
	hover,	//�����ͣ�ڿؼ���ʱ����click�¼�
	press,	//ѹ��ʱ����click�¼�
	release,//ѹ�º��ͷŰ�ťʱ����click�¼�
};

class NB_API ButtonBase : public ContentControl
{
public:
	virtual ~ButtonBase() = default;

	static DependencyProperty	ClickModeProperty();	//���ģʽ���������ԣ�Ĭ��ΪClickModeE::release)
	static DependencyProperty	IsPressedProperty();	//�Ƿ�ѹ�µ���������

	Event<RoutedEventArgs>		Click;					//����¼�
	static RoutedEvent			ClickEvent();			//���·���¼�(RoutedEventArgs)

	virtual void onIsPressedChanged(const DependencyPropertyChangedEventArgs &args);

protected:
	ButtonBase();

	virtual bool isEnableCore();						//�����Է�������Ŀ���״̬

	virtual void onClick();
	virtual void onMouseEnter(const MouseEventArgs &args) override;
	virtual void onMouseLeave(const MouseEventArgs &args) override;
	virtual void onMouseMove(const MouseEventArgs &args) override;
	virtual void onMouseLeftButtonDown(const MouseButtonEventArgs &args) override;
	virtual void onMouseLeftButtonUp(const MouseButtonEventArgs &args) override;

private:
	void updateIsPress();
};

}