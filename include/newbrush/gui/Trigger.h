#pragma once
#include "newbrush/gui/Setter.h"
#include "TriggerAction.h"

namespace nb{

class Binding;
using BindingPtr = std::shared_ptr<Binding>;
class Condition
{
public:
	Condition();
	Condition(DependencyPropertyPtr dp, const var &v);
	Condition(DependencyPropertyPtr dp, const var &v, BindingPtr bd);

	DependencyPropertyPtr	property;	//��������
	BindingPtr				binding;	//������MultiDataTrigger
	var						value;		//��������ֵ
};

class UIElement;
class NB_API TriggerBase
{
public:
	virtual ~TriggerBase() = default;

	virtual void attach(UIElement *uie);

	virtual void onElementPropertyChanged(UIElement * uie);

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
	Trigger(DependencyPropertyPtr dp, const var &v);

	virtual void attach(UIElement *uie) override;

	virtual void onElementPropertyChanged(UIElement * uie) override;

	void setProperty(DependencyPropertyPtr dp);
	DependencyPropertyPtr property() const;

	void setValue(const var &value);
	const var &value() const;

	std::vector<SetterBasePtr> &setters();

private:
	DependencyPropertyPtr		m_property;	//��������������
	var							m_value;	//����������ֵ
	std::vector<SetterBasePtr>	m_setters;	//����������ִ�е�setters
};

//������������
class NB_API MultiTrigger : public TriggerBase
{
public:
	MultiTrigger();
	MultiTrigger(const std::vector<Condition> &conditions, const std::vector<SetterBasePtr> setters);

	virtual void attach(UIElement *uie) override;

	virtual void onElementPropertyChanged(UIElement * uie) override;

	bool match(UIElement *uie) const;

	std::vector<Condition> &conditions();
	std::vector<SetterBasePtr> &setters();

private:
	std::vector<Condition>		m_conditions;	//����������
	std::vector<SetterBasePtr>	m_setters;		//����������ִ�е�setters
};

class DataTrigger : public TriggerBase
{
public:
	DataTrigger();
	DataTrigger(BindingPtr bd, const var &value);

	void setBinding(BindingPtr bd);
	BindingPtr binding() const;

	std::vector<SetterBasePtr> &setters();

	virtual void attach(UIElement *uie) override;

	bool match() const;

private:
	BindingPtr					m_binding;	//��
	var							m_value;	//�����İ�ֵ
	std::vector<SetterBasePtr>	m_setters;	//����������ִ�е�setters
};

class MultiDataTrigger : public TriggerBase
{
public:
	virtual void attach(UIElement *uie) override;

	bool match() const;

	std::vector<Condition>		conditions;	//����������
	std::vector<SetterBasePtr>	setters;	//����������ִ�е�setters
};

//�¼�����������Ҫ���ڶ���
class EventTrigger : public TriggerBase
{
public:
	virtual void attach(UIElement *uie) override;

	RoutedEvent						routedEvent;
	std::vector<TriggerActionPtr>	actions;
};

using TriggerBasePtr = std::shared_ptr<TriggerBase>;

}