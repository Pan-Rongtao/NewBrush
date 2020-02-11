#pragma once
#include <string>
#include "newbrush/core/Property.h"
#include "newbrush/core/TimeSpan.h"
#include "newbrush/core/Easing.h"
#include "newbrush/media/Storyboard.h"
#include "newbrush/core/DependencyObject.h"

namespace nb{
namespace gui{

class UIElement;
class NB_API VisualState : public DependencyObject
{
public:
	VisualState();
	VisualState(const std::string &name, std::shared_ptr<Storyboard> sb = nullptr);

	static DependencyProperty			NameProperty();			//���ֵ���������
	static DependencyProperty			StoryboardProperty();	//���°����������
};

class NB_API VisualTransition : public DependencyObject
{
public:
	VisualTransition();

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