#pragma once
#include "newbrush/gui/Setter.h"
#include "newbrush/core/Binding.h"
#include "TriggerAction.h"

namespace nb{

class Condition
{
public:
	Condition();
	Condition(const DependencyProperty &dp, const var &v);
	Condition(const DependencyProperty &dp, const var &v, BindingPtr bd);

	DependencyProperty		property;	//��������
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
	Trigger(const DependencyProperty &dp, const var &v);

	virtual void attach(UIElement *uie) override;

	virtual void onElementPropertyChanged(UIElement * uie) override;

	void setProperty(const DependencyProperty &dp);
	const DependencyProperty property() const;

	void setValue(const var &value);
	const var &getValue() const;

	std::vector<SetterBasePtr> &setters();

private:
	DependencyProperty			m_property;	//��������������
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
	DataTrigger(std::shared_ptr<Binding> bd, const var &value);

	void setBinding(std::shared_ptr<Binding> bd);
	std::shared_ptr<Binding> binding() const;

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