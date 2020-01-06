#pragma once
#include "../core/Event.h"
#include "../core/Any.h"
#include "../core/DependencyProperty.h"
#include "../core/EffectiveValueEntry.h"

namespace nb {

class NB_API DependencyObject
{
public:
	//��������ֵ
	//���δ�洢�и����Ե�ֵ����value��defaultValue�����ʱ�������´洢
	//��֮�Ѿ��洢�����Ե�ֵ����value��defaultValue��ȣ��Ƴ��ô洢��������¸�ֵ
	template<class T>
	void set(const DependencyProperty &dp, const T &value) &
	{
		if (dp.propertyType() != typeid(value))
		{
			nbThrowException(std::logic_error, "set value for [%s] must be a [%s] type instead of [%s]", dp.name().data(), dp.propertyType().name(), typeid(value).name());
		}

		auto defaultValue = dp.defaultMetadata()->defaultValue();
		auto iterFind = m_valueEntrys.find(dp.globalIndex());
		auto bValueEqualDefault = any_cast<T>(defaultValue) == value;
		if (iterFind == m_valueEntrys.end())
		{
			if (!bValueEqualDefault)
			{
				EffectiveValueEntry newEntry(dp);
				newEntry.setBaseValue(value);
				m_valueEntrys.insert({ dp.globalIndex(), newEntry });
				onPropertyChanged({dp, defaultValue, value });
			}
		}
		else
		{
			if (bValueEqualDefault)
			{
				m_valueEntrys.erase(iterFind);
			}
			else
			{
				iterFind->second.setBaseValue(value);
				onPropertyChanged({ dp, defaultValue, value });
			}
		}
	}

	template<>
	void set<const char *>(const DependencyProperty &dp, const char* const&value) &
	{
		auto defaultValue = dp.defaultMetadata()->defaultValue();
		auto bValueEqualDefault = false;
		if (dp.propertyType() == typeid(std::string))
		{
			bValueEqualDefault = any_cast<std::string>(defaultValue) == value;
		}
		else if (dp.propertyType() == typeid(const char *))
		{
			bValueEqualDefault = strcmp(any_cast<const char *>(defaultValue), value) == 1 ? true : false;
		}
		else
		{
			nbThrowException(std::logic_error, "set value for [%s] must be a [%s] type instead of [%s]", dp.name().data(), dp.propertyType().name(), typeid(value).name());
		}

		auto iterFind = m_valueEntrys.find(dp.globalIndex());
		if (iterFind == m_valueEntrys.end())
		{
			if (!bValueEqualDefault)
			{
				EffectiveValueEntry newEntry(dp);
				newEntry.setBaseValue(value);
				m_valueEntrys.insert({ dp.globalIndex(), newEntry });
				onPropertyChanged({ dp, defaultValue, value });
			}
		}
		else
		{
			if (bValueEqualDefault)
			{
				m_valueEntrys.erase(iterFind);
			}
			else
			{
				iterFind->second.setBaseValue(value);
				onPropertyChanged({ dp, defaultValue, value });
			}
		}
	}

	//���Ż���δ�Ƚ�ֵ�Ƿ����
	template<>
	void set<Any>(const DependencyProperty &dp, const Any &value) &
	{
		if (dp.propertyType() != typeid(value))
		{
			nbThrowException(std::logic_error, "value must be a [%s] type", dp.propertyType().name());
		}

		auto defaultValue = dp.defaultMetadata()->defaultValue();
		auto iterFind = m_valueEntrys.find(dp.globalIndex());
		if (iterFind == m_valueEntrys.end())
		{
			EffectiveValueEntry newEntry(dp);
			newEntry.setBaseValue(value);
			m_valueEntrys.insert({ dp.globalIndex(), newEntry });
			onPropertyChanged({ dp, defaultValue, value });
		}
		else
		{
			iterFind->second.setBaseValue(value);
			onPropertyChanged({ dp, defaultValue, value });
		}
	}


	//��ȡ����ֵ
	//���δ�洢�и����Ե�ֵ���򷵻�defaultValue
	//��֮�����ظô洢ֵ
	template<class T>
	T get(const DependencyProperty &dp) const
	{
		auto iter = m_valueEntrys.find(dp.globalIndex());
		if (iter == m_valueEntrys.end())
		{
			return any_cast<T>(dp.defaultMetadata()->defaultValue());
		}
		else
		{
			auto x = iter->second.baseValue();
			return any_cast<T>(x);
		}
	}

protected:
	virtual void onPropertyChanged(const DependencyPropertyChangedEventArgs &args);

private:
	
	std::map<size_t, EffectiveValueEntry>	m_valueEntrys;
};

}