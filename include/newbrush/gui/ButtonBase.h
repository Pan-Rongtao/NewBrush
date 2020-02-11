#pragma once
#include "newbrush/gui/ContentControl.h"

namespace nb{ 
namespace gui{

enum class ClickModeE
{
	hover,	//�����ͣ�ڿؼ���ʱ����click�¼�
	press,	//ѹ��ʱ����click�¼�
	release,//ѹ�º��ͷŰ�ťʱ����click�¼�
};

class NB_API ButtonBase : public ContentControl
{
public:
	ButtonBase();
	virtual ~ButtonBase() = default;

	static DependencyProperty	ClickModeProperty();	//���ģʽ����������
	static DependencyProperty	IsPressedProperty();	//�Ƿ�ѹ�µ���������

	struct ClickArgs {};
	Event<ClickArgs>				Click;					//����¼�

															
protected:
	virtual bool isEnableCore();							//�����Է�������Ŀ���״̬

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