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
	BindingPtr				binding;	//������MultiDataTrigger
	Var						value;		//��������ֵ
};

class UIElement;
class NB_API TriggerBase
{
public:
	virtual ~TriggerBase() = default;

	void processSetters(UIElement *uie, std::vector<SetterBasePtr> setters);

	std::vector<TriggerActionPtr>	enterActions;
	std::vector<TriggerActionPtr>	exitActions;

protected:
	TriggerBase() = default;
};

//��ͨ������
class NB_API Trigger : public TriggerBase
{
public:
	Trigger();
	Trigger(const DependencyProperty &dp, const Var &v);

	bool match(const DependencyProperty &dp, const Var &v) const;

	DependencyProperty			property;	//��������������
	Var							value;		//����������ֵ
	std::vector<SetterBasePtr>	setters;	//����������ִ�е�setters
};

//������������
class NB_API MultiTrigger : public TriggerBase
{
public:
	bool match(UIElement *uie) const;

	std::vector<Condition>		conditions;	//����������
	std::vector<SetterBasePtr>	setters;	//����������ִ�е�setters
};

class DataTrigger : public TriggerBase
{
public:
	bool match(const Var &v) const;

	BindingPtr					binding;	//��
	Var							value;		//�����İ�ֵ
	std::vector<SetterBasePtr>	setters;	//����������ִ�е�setters
};

class MultiDataTrigger : public TriggerBase
{
public:
	bool match(const Var &v) const;

	std::vector<Condition>		conditions;	//����������
	std::vector<SetterBasePtr>	setters;	//����������ִ�е�setters
};

//�¼�����������Ҫ���ڶ���
class EventTrigger : public TriggerBase
{
public:
	RoutedEvent						routedEvent;
	std::vector<TriggerActionPtr>	actions;
};

using TriggerBasePtr = std::shared_ptr<TriggerBase>;

}}