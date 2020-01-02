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
	void set(const DependencyProperty &dp, const T &value)
	{
		auto metadata = dp.defaultMetadata();
		if (metadata.type() != typeid(value))
		{
			nbThrowException(std::logic_error, "value must be type of [%s]", dp.defaultValue().type().name());
		}

		auto iter = m_valueEntrys.find(dp.globalIndex());
		bool bValueEqualDefault = any_cast<T>(metadata->defaultValue());
		if (iter == m_valueEntrys.end())
		{
			if (!bValueEqualDefault)
			{
				EffectiveValueEntry newEntry(dp);
				newEntry.setBaseValue(value);
				m_valueEntrys[dp.globalIndex()] = newEntry;
				onPropertyChanged({dp, metadata->defaultValue(), value });
			}
		}
		else
		{
			if (bValueEqualDefault)
			{
				m_valueEntrys.erase(iter);
			}
			else
			{
				iter->second.setBaseValue(value);
				onPropertyChanged({ dp, metadata->defaultValue(), value });
			}
		}
	}

	//��ȡ����ֵ
	//���δ�洢�и����Ե�ֵ���򷵻�defaultValue
	//��֮�����ظô洢ֵ
	template<class T>
	T getValue(const DependencyProperty &dp) const
	{
		auto iter = m_valueEntrys.find(dp.globalIndex());
		if (iter == m_valueEntrys.end())
		{
			return dp.defaultValue();
		}
		else
		{
			return any_cast<T>(iter->second.baseValue());
		}
	}

protected:
	virtual void onPropertyChanged(const DependencyPropertyChangedEventArgs &args);

private:
	
	std::map<size_t, EffectiveValueEntry>	m_valueEntrys;
};

}