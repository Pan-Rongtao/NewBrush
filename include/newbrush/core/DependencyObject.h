#pragma once
#include "newbrush/core/Event.h"
#include "newbrush/core/DependencyProperty.h"
#include "newbrush/core/EffectiveValueEntry.h"

namespace nb {

class NB_API DependencyObject : public Object
{
	RTTR_ENABLE(Object)
public:
	//��������ֵ���������������������Զ��󣬼�ʹDependencyObjectδע���и��������ԣ�
	//�쳣��std::logic_error
	void setValue(const DependencyProperty &dp, const variant &value);
	template<class T>
	void setValue(const DependencyProperty &dp, const T &value)
	{
		var v = value;
		setValue(dp, v);
	}

	//��ȡ����ֵ
	variant getValue(const DependencyProperty &dp) const;
	template<class T>
	T getValue(const DependencyProperty &dp) const
	{
		if(dp.propertyType() != rttr::type::get<T>())
		{
			nbThrowException(std::logic_error, "should use get<%s> instead of get<%s> for [%s]", dp.propertyType().get_name().data(), typeid(T).name(), dp.name().data()); 
		}
		return getValue(dp).get_value<T>();
	}

protected:
	virtual void onPropertyChanged(const DependencyPropertyChangedEventArgs &args);

private:
	void _set(const DependencyProperty & dp, const var &defaultValue, const var &setValue);
	void invokePropertyCallback(const DependencyPropertyChangedEventArgs & args);

	std::map<size_t, EffectiveValueEntry>	m_valueEntrys;
};

}