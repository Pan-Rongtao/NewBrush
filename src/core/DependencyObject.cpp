#include "newbrush/core/DependencyObject.h"

using namespace nb;
using namespace rttr;

//���ʹ��Poco::Var�����δ�洢�и����Ե�ֵ����value��defaultValue�����ʱ�������´洢
//��֮�Ѿ��洢�����Ե�ֵ����value��defaultValue��ȣ��Ƴ��ô洢��������¸�ֵ
//wchar_t��chart16_t��long double����Щ������Ϊnumber�������޷�ת��number���ͣ�bool��char��int��short��float��double�ȣ�
//���wchar_t��Щ���Ͷ�����extract������convert
void DependencyObject::setValue(const DependencyProperty & dp, const var &value)
{
	auto propertyType = dp.propertyType();
	var fixSetValue;
	if (dp.propertyType() != value.get_type())
	{
		bool ok = value.convert(propertyType);
		if (!ok)
		{
			nbThrowException(std::logic_error, "set value for [%s] must be a [%s] type instead of [%s]", dp.name().data(), dp.propertyType().get_name().data(), value.get_type().get_name().data());
		}
	}
	fixSetValue = value;

	auto defaultValue = dp.defaultMetadata()->defaultValue();
	_set(dp, defaultValue, fixSetValue);
}

//���δ�洢�и����Ե�ֵ���򷵻�defaultValue
//��֮�����ظô洢ֵ
var DependencyObject::getValue(const DependencyProperty & dp) const
{
	auto iter = m_valueEntrys.find(dp.globalIndex());
	if (iter == m_valueEntrys.end())
	{
		return dp.defaultMetadata()->defaultValue();
	}
	else
	{
		auto x = iter->second.baseValue();
		return x;
	}
}

void DependencyObject::_set(const DependencyProperty & dp, const var & defaultValue, const var & setValue)
{
	auto coerceValue = setValue;
	auto coerce = dp.defaultMetadata()->coerceValueCallback();
	if (coerce)
	{
		coerceValue = coerce(this, setValue);
	}

	bool equalDefault = false;
	try {
		equalDefault = coerceValue == defaultValue;
	}
	catch (...) {}	//�쳣��ʾ�޷��Ƚϣ�����Ϊ����ͨ����
	
	auto iterFind = m_valueEntrys.find(dp.globalIndex());
	if (iterFind == m_valueEntrys.end())
	{
		if (!equalDefault)
		{
			EffectiveValueEntry newEntry(dp);
			newEntry.setBaseValue(coerceValue);
			m_valueEntrys.insert({ dp.globalIndex(), newEntry });
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

void DependencyObject::invokePropertyCallback(const DependencyPropertyChangedEventArgs & args)
{
	auto metadata = args.property.defaultMetadata();
	if (metadata->propertyChangedCallback())
	{
		DependencyPropertyChangedEventArgs *p = const_cast<DependencyPropertyChangedEventArgs *>(&args);
		metadata->propertyChangedCallback()(this, p);
	}
}

void DependencyObject::onPropertyChanged(const DependencyPropertyChangedEventArgs & args)
{
}
