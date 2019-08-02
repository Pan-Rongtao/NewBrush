#pragma once
#include <string>
#include <map>
#include "../core/Def.h"
#include "../core/Any.h"

namespace nb{ namespace gui{

class UIElement;
class NB_API DependencyProperty
{
public:
	//ע��һ���������ԣ�����������Ѵ��ڣ���ֻ�޸�����ֵ
	//element��Ŀ��Ԫ��
	//property_name��������
	//property_v������ֵ
	static void registerAttached(std::shared_ptr<UIElement> element, const std::string &property_name, const core::Any &property_v);

	//��ѯ��������ֵ�������ѯ������������һ���յ�Any
	//element��Ŀ��Ԫ��
	//property_name��������
	static core::Any findAttached(std::shared_ptr<UIElement> element, const std::string &property_name);

	template<class ownerType>
	static void setProperty(const std::string &name, const core::Any &v);

private:
	std::string	m_name;
	int			m_hash;

	static std::map<std::size_t, std::pair<std::string, core::Any>>					m_dependencyProperties;
	static std::map<std::shared_ptr<UIElement>, std::map<std::string, core::Any>>	m_attProperties;
};
template<class ownerType>
inline void DependencyProperty::setProperty(const std::string &name, const core::Any & v)
{
	auto h0 = typeid(ownerType).hash_code();
	auto h1 = std::hash<std::string>{}(name);
	auto _tHash = h0 ^ h1;
	auto iter = m_dependencyProperties.find(_tHash);
	if (iter == m_dependencyProperties.end())
	{
		m_dependencyProperties[_tHash] = {name, v};
	}
	else
	{
		iter->second.second = v;
	}
}
/*
template<class propertyType, class ownerType>
inline DependencyProperty DependencyProperty::registerDependency(const std::string & name)
{
	auto h0 = typeid(propertyType).hash_code();
	auto h1 = typeid(ownerType).hash_code();
	auto _tHash = h0 ^ h1;
	if (m_dependencyProperties.find(_tHash) != m_dependencyProperties.end())
		nbThrowException(std::logic_error, "property [%s] has already been registered for type[%s]", name.data(), typeid(ownerType).name());

	auto _instanceHash = _tHash;
	DependencyProperty dp;
	dp.m_name = name;
	dp.m_hash = _instanceHash;
	m_dependencyProperties[_tHash] = dp;
	return dp;
}
*/
}
}