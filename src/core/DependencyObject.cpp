#include "newbrush/core/DependencyObject.h"
#include "newbrush/core/DependencyProperty.h"

using namespace nb;
using namespace rttr;

//���ʹ��Poco::Var�����δ�洢�и����Ե�ֵ����value��defaultValue�����ʱ�������´洢
//��֮�Ѿ��洢�����Ե�ֵ����value��defaultValue��ȣ��Ƴ��ô洢��������¸�ֵ
//wchar_t��chart16_t��long double����Щ������Ϊnumber�������޷�ת��number���ͣ�bool��char��int��short��float��double�ȣ�
//���wchar_t��Щ���Ͷ�����extract������convert
void DependencyObject::setValue(DependencyPropertyPtr dp, const var &value)
{
	auto propertyType = dp->propertyType();
	auto valueType = value.get_type();
	var fixSetValue = value;
	bool isDerived = (valueType.get_wrapped_type().is_valid() && propertyType.get_wrapped_type().is_valid())
		&& (valueType.get_wrapped_type().is_derived_from(propertyType.get_wrapped_type()));
	if (propertyType != valueType && !isDerived)
	{
		bool ok = fixSetValue.convert(type(propertyType));
		if (!ok)
		{
			nbThrowException(std::logic_error, "set value for [%s] must be a [%s] type instead of [%s]", dp->name().data(), dp->propertyType().get_name().data(), valueType.get_name().data());
		}
	}

	auto defaultValue = dp->defaultMetadata()->defaultValue();
	_set(dp, defaultValue, fixSetValue);
}

//���δ�洢�и����Ե�ֵ���򷵻�defaultValue
//��֮�����ظô洢ֵ
const var &DependencyObject::getValue(DependencyPropertyPtr dp) const
{
	auto iter = m_valueEntrys.find(dp->globalIndex());
	if (iter == m_valueEntrys.end())
	{
		return dp->defaultMetadata()->defaultValue();
	}
	else
	{
		return iter->second.baseValue();
	}
}

void DependencyObject::_set(DependencyPropertyPtr dp, const var & defaultValue, const var & setValue)
{
	auto coerceValue = setValue;
	auto coerce = dp->defaultMetadata()->coerceValueCallback();
	if (coerce)
	{
		coerceValue = coerce(this, setValue);
	}

	bool equalDefault = false;
	try {
		equalDefault = coerceValue == defaultValue;
	}
	catch (...) {}	//�쳣��ʾ�޷��Ƚϣ�����Ϊ����ͨ����
	
	auto iterFind = m_valueEntrys.find(dp->globalIndex());
	if (iterFind == m_valueEntrys.end())
	{
		if (!equalDefault)
		{
			EffectiveValueEntry newEntry(dp);
			newEntry.setBaseValue(coerceValue);
			m_valueEntrys.insert({ dp->globalIndex(), newEntry });
			DependencyPropertyChangedEventArgs args{ dp, defaultValue, coerceValue };
			invokePropertyCallback(args);
			onPropertyChanged(args);
		}
	}
	else
	{
		auto changed = true;
		auto oldValue = iterFind->second.baseValue();
		try {
			changed = oldValue != coerceValue;
		}
		catch (...) {}	//�쳣��ʾ�޷��Ƚϣ�����Ϊ����ͨ����

		if (equalDefault)
		{
			m_valueEntrys.erase(iterFind);
		}
		else
		{
			iterFind->second.setBaseValue(coerceValue);
		}

		if (changed)
		{
			DependencyPropertyChangedEventArgs args{ dp, oldValue, coerceValue };
			invokePropertyCallback(args);
			onPropertyChanged(args);
		}
	}
}

void DependencyObject::_checkType(DependencyPropertyPtr dp, rttr::type getType) const
{
	if (dp->propertyType() != getType)
	{
		nbThrowException(std::logic_error, "should use get<%s> instead of get<%s> for [%s]", dp->propertyType().get_name().data(), getType.get_name().data(), dp->name().data());
	}
}

void DependencyObject::invokePropertyCallback(const DependencyPropertyChangedEventArgs & args)
{
	auto metadata = args.property()->defaultMetadata();
	if (metadata->propertyChangedCallback())
	{
		metadata->propertyChangedCallback()(this, args);
	}
}

void DependencyObject::onPropertyChanged(const DependencyPropertyChangedEventArgs & args)
{
}
