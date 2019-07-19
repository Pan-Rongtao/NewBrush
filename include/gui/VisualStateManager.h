#pragma once
#include <string>
#include "../core/Property.h"
#include "../core/Easing.h"
#include "Storyboard.h"

namespace nb{
namespace gui{

class UIElement;

class VisualState
{
public:
	core::Property_rw<std::string>					Name;		//����
	core::Property_rw<std::shared_ptr<Storyboard>>	Storyboard;	//���°�
};

class VisualTransition
{
public:
	core::Property_rw<std::string>					From;		//��ʼ״̬
	core::Property_rw<std::string>					To;			//Ŀ��״̬
	core::Property_rw<core::TimeSpan>				Duration;	//����ʱ��
	core::Property_rw<std::shared_ptr<Storyboard>>	Storyboard;	//���°�
	core::Property_rw<core::EasingBase>				Easing;		//��������

};

class VisualGroup
{
public:
	core::Property_rw<std::string>					Name;		//����
	core::Property_rw<std::vector<VisualState>>		States;		//״̬����

};

class VisualStateManager
{
public:
	static std::vector<VisualGroup>	getVisualStateGroups(std::shared_ptr<UIElement> element);
	static bool gotoElementState(std::shared_ptr<UIElement> element, const std::string &state, bool useTransitions);
};

}
}