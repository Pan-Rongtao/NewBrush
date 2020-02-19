#pragma once
#include "newbrush/gui/Setter.h"
#include "newbrush/core/Binding.h"
#include "TriggerAction.h"

namespace nb{
namespace gui{

class Condition
{
public:
	Condition();
	Condition(const DependencyProperty &dp, const Var &v);
	Condition(const DependencyProperty &dp, const Var &v, BindingPtr bd);

	DependencyProperty		property;	//��������
	Var						value;		//��������ֵ
	BindingPtr				binding;	//������MultiDataTrigger
};

class NB_API TriggerBase
{
public:
	std::vector<TriggerActionPtr>	enterActions;
	std::vector<TriggerActionPtr>	exitActions;
};

//��ͨ������
class NB_API Trigger : public TriggerBase
{
public:
	Trigger();
	Trigger(const DependencyProperty &dp, const Var &v);

	DependencyProperty			property;	//��������������
	Var							value;		//����������ֵ
	std::vector<SetterBasePtr>	setters;	//����������ִ�е�setters
};

//������������
class NB_API MultiTrigger : public TriggerBase
{
public:
	std::vector<Condition>		conditions;	//����������
	std::vector<SetterBasePtr>	setters;	//����������ִ�е�setters
};

class DataTrigger : public TriggerBase
{
public:
	BindingPtr					binding;	//��
	Var							value;		//�����İ�ֵ
	std::vector<SetterBasePtr>	setters;	//����������ִ�е�setters
};

class MultiDataTrigger : public TriggerBase
{
public:
	std::vector<Condition>		conditions;	//����������
	std::vector<SetterBasePtr>	setters;	//����������ִ�е�setters
};

//�¼�����������Ҫ���ڶ���
class EventTrigger : public TriggerBase
{
public:
	RoutedEvent						event;
	std::vector<TriggerActionPtr>	actions;
};

using TriggerBasePtr = std::shared_ptr<TriggerBase>;

}}