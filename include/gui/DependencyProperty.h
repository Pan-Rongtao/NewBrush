#pragma once
#include <string>
#include <map>
#include "../core/Any.h"

namespace nb{
namespace gui{

class UIElement;
class DependencyObject;
class NB_API DependencyProperty
{
public:
	//ע��һ���������ԣ�����������Ѵ��ڣ���ֻ�޸�����ֵ
	//element��Ŀ��Ԫ��
	//property_name��������
	//property_v������ֵ
	static void registerAttached(std::shared_ptr<UIElement> element, const std::string &property_name, const Any &property_v);

	
	//��ѯ��������ֵ�������ѯ������������һ���յ�Any
	//element��Ŀ��Ԫ��
	//property_name��������
	static Any findAttached(std::shared_ptr<UIElement> element, const std::string &property_name);

	//ע����������
	//�쳣��std::logic_error�Ѿ�ע���ͬ��������
	template<class ownerType, class propertyType>
	static const DependencyProperty &registerDependency(const std::string & name, const propertyType &defaultValue, bool isSealed = false)
	{
		static std::map<std::size_t, DependencyProperty> g_dependencyProperties;
		static_assert(std::is_base_of<DependencyObject, ownerType>::value, "registerDependency<ownerType, propertyType> : ownerType must be DependencyObject or it's derived type.");

		std::hash<std::string> _shash;
		auto hash = typeid(ownerType).hash_code() ^ _shash(name);
		if (g_dependencyProperties.find(hash) != g_dependencyProperties.end())
			nbThrowException(std::logic_error, "[%s] has already been registered for [%s]", name.data(), typeid(ownerType).name());

		DependencyProperty dp;
		dp.m_name = name;
		dp.m_hash = hash;
		dp.m_isSealed = isSealed;
		dp.m_defaultV = defaultValue;
		g_dependencyProperties[hash] = dp;
		return g_dependencyProperties[hash];
	}

	//����
	std::string name() const;

	//��ϣֵ��Ψһ
	size_t hash() const;

	//�Ƿ�ɸ�д
	bool isSealed() const;

	//Ĭ��ֵ
	Any &defaultValue();
	const Any &defaultValue() const;

	bool operator == (const DependencyProperty &other) const;
	bool operator != (const DependencyProperty &other) const;

private:
	std::string	m_name;
	size_t		m_hash{0};
	bool		m_isSealed{ true };
	Any			m_defaultV;

	static std::map<std::shared_ptr<UIElement>, std::map<std::string, Any>>	m_attProperties;
};

}
}