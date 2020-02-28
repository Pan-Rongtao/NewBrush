#pragma once
#include "newbrush/core/Event.h"
#include "newbrush/core/DependencyProperty.h"
#include "newbrush/core/EffectiveValueEntry.h"
#include "Poco/Dynamic/Var.h"

namespace nb {

class NB_API DependencyObject : public Object
{
public:
	//��������ֵ���������������������Զ��󣬼�ʹDependencyObjectδע���и��������ԣ�
	//�쳣��std::logic_error
	void set(const DependencyProperty &dp, const Var &value);

	//��ȡ����ֵ
	Var get(const DependencyProperty &dp) const;
	template<class T>
	T get(const DependencyProperty &dp) const
	{
		try {
			return get(dp).extract<T>();
		}
		catch (...) { nbThrowException(std::logic_error, "should use get<%s> instead of get<%s> for [%s]", dp.propertyType().name(), typeid(T).name(), dp.name().data()); }
	}

protected:
	void _set(const DependencyProperty & dp, const Var &defaultValue, const Var &setValue);
	void invokePropertyCallback(const DependencyPropertyChangedEventArgs & args);
	virtual void onPropertyChanged(const DependencyPropertyChangedEventArgs &args);

private:
	
	std::map<size_t, EffectiveValueEntry>	m_valueEntrys;
};

}