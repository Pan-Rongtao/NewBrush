#pragma once
#include <functional>
#include "../core/Any.h"
#include "../core/EventArgs.h"

namespace nb {

class PropertyMetadata
{
public:
	//����һ��PropertyMetadata
	//defaulValue��Ĭ��ֵ
	//propertyChangedCallback�������Ѹı�ص�
	//coerceValueCallback������ֵ�����ص�
	PropertyMetadata(const Any &defaulValue, PropertyChangedCallback propertyChangedCallback = nullptr, CoerceValueCallback coerceValueCallback = nullptr);

	void setDefaultValue(const Any &value) &;
	Any defaultValue() const;
	bool isSealed() const;
	PropertyChangedCallback propertyChangedCallback();
	CoerceValueCallback coerceValueCallback();
	
private:
	Any						m_defaultValue;
	PropertyChangedCallback	m_propertyChangedCallback;
	CoerceValueCallback		m_coerceValueCallback;
};

}