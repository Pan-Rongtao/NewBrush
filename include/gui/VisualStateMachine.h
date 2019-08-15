#pragma once
#include <string>
#include "../core/Property.h"
#include "../core/Easing.h"
#include "Storyboard.h"

namespace nb{
namespace gui{

class UIElement;

class NB_API VisualState
{
public:
	VisualState();
	VisualState(const std::string &name, std::shared_ptr<Storyboard> sb = nullptr);

	core::Property_rw<std::string>					Name;		//����
	core::Property_rw<std::shared_ptr<Storyboard>>	Storyboard;	//���°�
};

class NB_API VisualTransition
{
public:
	core::Property_rw<std::string>					From;		//��ʼ״̬
	core::Property_rw<std::string>					To;			//Ŀ��״̬
	core::Property_rw<core::TimeSpan>				Duration;	//����ʱ��
	core::Property_rw<std::shared_ptr<Storyboard>>	Storyboard;	//���°�
	core::Property_rw<std::shared_ptr<core::EasingBase>>				Easing;		//��������

};

class NB_API VisualStateGroup
{
public:
	VisualStateGroup(const std::string &name);
	VisualStateGroup(const std::string &name, const std::vector<std::shared_ptr<VisualState>> &states);

	core::Property_rw<std::string>					Name;		//����
	core::Property_rw<std::vector<std::shared_ptr<VisualState>>>		States;		//״̬����
	core::Property_r<VisualState>					CurrentState;//��ǰ״̬
	core::Property_r<std::vector<VisualTransition>>	Transitions;
	struct StateChangedEventArgs {};
	core::Event<StateChangedEventArgs>				CurrentStateChanged;
	core::Event<StateChangedEventArgs>				CurrentStateChanging;
};

class NB_API VisualStateMachine
{
public:
	//���һ��״̬��
	//�쳣������name��ͬ��״̬��
	void addGroup(std::shared_ptr<VisualStateGroup> group);
	bool gotoState(const std::string &groupName, const std::string &stateName, bool useTransitions);

private:
	std::vector<std::shared_ptr<VisualStateGroup>>	m_groups;
};

}
}