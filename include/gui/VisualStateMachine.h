#pragma once
#include <string>
#include "../core/Property.h"
#include "../core/TimeSpan.h"
#include "../core/Easing.h"
#include "Storyboard.h"
#include "../core/DependencyObject.h"

namespace nb{
namespace gui{

class UIElement;
class NB_API VisualState : public DependencyObject
{
public:
	VisualState();
	VisualState(const std::string &name, std::shared_ptr<Storyboard> sb = nullptr);

	Property_rw<std::string>			Name;					//����
	Property_rw<shared_ptr<Storyboard>>	Storyboard;				//���°�
	static DependencyProperty			NameProperty();			//���ֵ���������
	static DependencyProperty			StoryboardProperty();	//���°����������
};

class NB_API VisualTransition : public DependencyObject
{
public:
	VisualTransition();

	Property_rw<std::string>			From;				//��ʼ״̬
	Property_rw<std::string>			To;					//Ŀ��״̬
	Property_rw<TimeSpan>				Duration;			//����ʱ��
	Property_rw<shared_ptr<Storyboard>>	Storyboard;			//���°�
	//Property_rw<shared_ptr<EasingBase>>	Easing;			//��������

	static DependencyProperty			FromProperty();		//��ʼ״̬����������
	static DependencyProperty			ToProperty();		//Ŀ��״̬����������
	static DependencyProperty			DurationProperty();	//����ʱ�����������
	static DependencyProperty			StoryboardProperty();//���°����������
	static DependencyProperty			EasingProperty();	//������������������
};

class NB_API VisualStateGroup : public DependencyObject
{
public:
	VisualStateGroup(const std::string &name);
	VisualStateGroup(const std::string &name, const std::vector<std::shared_ptr<VisualState>> &states);

	Property_rw<std::string>							Name;					//����
	Property_rw<std::vector<shared_ptr<VisualState>>>	States;					//״̬����
	Property_r<shared_ptr<VisualState>>					CurrentState;			//��ǰ״̬
	Property_r<std::vector<VisualTransition>>			Transitions;			//����
	static DependencyProperty							NameProperty();			//���ֵ���������
	static DependencyProperty							StatesProperty();		//״̬���ϵ���������
	static DependencyProperty							CurrentStateProperty();	//��ǰ״̬����������
	static DependencyProperty							TransitionsProperty();	//���ȵ���������

	struct StateChangedEventArgs {};
	Event<StateChangedEventArgs>						CurrentStateChanged;	//��ǰ״̬�ı�����¼�
	Event<StateChangedEventArgs>						CurrentStateChanging;	//��ǰ״̬���ڸı��¼�

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