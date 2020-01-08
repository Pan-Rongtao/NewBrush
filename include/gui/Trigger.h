#pragma once
#include "../gui/Setter.h"
#include "../gui/Binding.h"

namespace nb{
namespace gui{

class Condition
{
public:
	DependencyProperty		property;	//��������
	Var						value;		//��������ֵ
};

class TriggerBase
{

};

class NB_API Trigger : public TriggerBase
{
public:
	DependencyProperty		condition;	//��������������
	Var						value;		//����������ֵ
	std::vector<Setter>		setters;	//����������ִ�е�setters
};

class NB_API MultiTrigger : public TriggerBase
{
public:
	std::vector<Condition>	conditions;	//����������
	std::vector<Setter>		setters;	//����������ִ�е�setters
};

class DataTrigger : public TriggerBase
{
public:
	BindingPtr				binding;	//��
	Var						value;		//�����İ�ֵ
	std::vector<Setter>		setters;	//����������ִ�е�setters
};

class MultiDataTrigger : public TriggerBase
{
public:
	std::vector<Condition>	conditions;	//����������
	std::vector<Setter>		setters;	//����������ִ�е�setters
};

class EventTrigger : public TriggerBase
{
public:

};

}}