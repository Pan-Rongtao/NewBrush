#pragma once
#include "../core/Event.h"
#include "../core/DependencyProperty.h"
#include "../core/EffectiveValueEntry.h"
#include "Poco/Dynamic/Var.h"

namespace nb {

class NB_API DependencyObject
{
public:
	//��������ֵ
	//���δ�洢�и����Ե�ֵ����value��defaultValue�����ʱ�������´洢
	//��֮�Ѿ��洢�����Ե�ֵ����value��defaultValue��ȣ��Ƴ��ô洢��������¸�ֵ
	void set(const DependencyProperty &dp, const Var &value);

	//��ȡ����ֵ
	//���δ�洢�и����Ե�ֵ���򷵻�defaultValue
	//��֮�����ظô洢ֵ
	Var get(const DependencyProperty &dp) const;
	template<class T>
	T get(const DependencyProperty &dp) const
	{
		return get(dp).extract<T>();
	}

protected:
	void _set(const DependencyProperty & dp, const Var &defaultValue, const Var &setValue, bool isValueChanged);
	virtual void onPropertyChanged(const DependencyPropertyChangedEventArgs &args);

private:
	
	std::map<size_t, EffectiveValueEntry>	m_valueEntrys;
};

}