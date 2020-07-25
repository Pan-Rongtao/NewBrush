#pragma once
#include "newbrush/core/Object.h"
#include "newbrush/core/EffectiveValueEntry.h"
#include "newbrush/core/DependencyProperty.h"

namespace nb {
	
class NB_API DependencyObject : public Object
{
	RTTR_ENABLE(Object)
public:
	//��������ֵ���������������������Զ��󣬼�ʹDependencyObjectδע���и��������ԣ�
	//�쳣��std::logic_error
	void setValue(DependencyPropertyPtr dp, const var &value);

	template<class T>
	void setValue(DependencyPropertyPtr dp, const T &value)
	{
		setValue(dp, var(value));
	}

	//��ȡ����ֵ
	const var &getValue(DependencyPropertyPtr dp) const;
	template<class T>
	const T &getValue(DependencyPropertyPtr dp) const
	{
		_checkType(dp, rttr::type::get<T>());
		return getValue(dp).get_value<T>();
	}

protected:
	virtual void onPropertyChanged(const DependencyPropertyChangedEventArgs &args);

private:
	void _set(DependencyPropertyPtr dp, const var &defaultValue, const var &setValue);
	void _checkType(DependencyPropertyPtr dp, rttr::type getType) const;
	void invokePropertyCallback(const DependencyPropertyChangedEventArgs & args);

	std::map<size_t, EffectiveValueEntry>	m_valueEntrys;
};

using DependencyObjectPtr = std::shared_ptr<DependencyObject>;
}