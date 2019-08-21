#pragma once
#include "ContentControl.h"

namespace nb{ 
namespace gui{

enum class ClickModeE
{
	hover,	//�����ͣ�ڿؼ���ʱ����click�¼�
	press,	//ѹ��ʱ����click�¼�
	release,//ѹ�º��ͷŰ�ťʱ����click�¼�
};

class ButtonBase : ContentControl
{
public:
	ButtonBase();
	virtual ~ButtonBase() = default;

	//�����Է�������Ŀ���״̬
	virtual bool isEnableCore();


	Property_rw<ClickModeE>			ClickMode;		//ָ������ģʽ����click�ķ���
	Property_r<bool>				IsPressed;		//�Ƿ���ѹ��״̬

	struct ClickArgs {};
	Event<ClickArgs>				Click;			//����¼�

	static const DependencyProperty	ClickModeProperty();
	static const DependencyProperty	IsPressedProperty();

protected:
	virtual void onClick();
	virtual void onKeyDown();
	virtual void onKeyUp();
	virtual void onMouseEnter();
	virtual void onMouseMove();
	virtual void onMouseLeave();
	virtual void onLeftButtonDown();
	virtual void onLeftButtonUp();

};

}
}