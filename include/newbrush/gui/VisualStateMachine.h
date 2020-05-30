#pragma once
#include <string>
#include "newbrush/core/TimeSpan.h"
#include "newbrush/media/Easing.h"
#include "newbrush/media/Storyboard.h"
#include "newbrush/core/DependencyObject.h"

namespace nb{

class UIElement;
class NB_API VisualState : public DependencyObject
{
public:
	VisualState();
	VisualState(const std::string &name, std::shared_ptr<Storyboard> sb = nullptr);

	static DependencyPropertyPtr NameProperty();			//���ֵ���������
	static DependencyPropertyPtr StoryboardProperty();	//���°����������
};

class NB_API VisualTransition : public DependencyObject
{
public:
	VisualTransition();

	static DependencyPropertyPtr FromProperty();		//��ʼ״̬����������
	static DependencyPropertyPtr ToProperty();			//Ŀ��״̬����������
	static DependencyPropertyPtr DurationProperty();	//����ʱ�����������
	static DependencyPropertyPtr StoryboardProperty();	//���°����������
	static DependencyPropertyPtr EasingProperty();		//������������������
};

class NB_API VisualStateGroup : public DependencyObject
{
public:
	VisualStateGroup(const std::string &name);
	VisualStateGroup(const std::string &name, const std::vector<std::shared_ptr<VisualState>> &states);

	static DependencyPropertyPtr NameProperty();		//���ֵ���������
	static DependencyPropertyPtr StatesProperty();		//״̬���ϵ���������
	static DependencyPropertyPtr CurrentStateProperty();//��ǰ״̬����������
	static DependencyPropertyPtr TransitionsProperty();	//���ȵ���������

	struct StateChangedEventArgs {};
	Event<StateChangedEventArgs> CurrentStateChanged;	//��ǰ״̬�ı�����¼�
	Event<StateChangedEventArgs> CurrentStateChanging;	//��ǰ״̬���ڸı��¼�

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