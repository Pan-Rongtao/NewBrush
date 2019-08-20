#pragma once
#include <string>
#include <map>
#include "../core/Def.h"
#include "../core/Any.h"

namespace nb{ namespace gui{

class UIElement;
class DependencyObject;
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

	//ע����������
	//�쳣��std::logic_error�Ѿ�ע���ͬ��������
	template<class ownerType, class propertyType>
	static DependencyProperty registerDependency(const std::string & name, const propertyType &defaultValue = propertyType())
	{
		static std::map<std::size_t, DependencyProperty> g_dependencyProperties;
		static_assert(std::is_base_of<DependencyObject, ownerType>::value, "registerDependency<ownerType, propertyType> : ownerType must be DependencyObject or it's derived type.");

		auto h0 = typeid(ownerType).hash_code();
		std::hash<std::string> shash;
		auto h1 = shash(name);
		auto hs = h0 ^ h1;
		if (g_dependencyProperties.find(hs) != g_dependencyProperties.end())
			nbThrowException(std::logic_error, "[%s] has already been registered for [%s]", name.data(), typeid(ownerType).name());

		DependencyProperty dp;
		dp.m_name = name;
		dp.m_hash = hs;
		dp.m_defaultV = defaultValue;
		g_dependencyProperties[hs] = dp;
		return dp;
	}

	//����
	std::string name() const;

	//��ϣֵ��Ψһ
	size_t hash() const;

	//�Ƿ�ɸ�д
	bool isSealed() const;

	//Ĭ��ֵ
	core::Any defaultValue() const;

	bool operator == (const DependencyProperty &other) const;

private:
	std::string	m_name;
	size_t		m_hash{0};
	bool		m_isSealed{ true };
	core::Any	m_defaultV;

	static std::map<std::shared_ptr<UIElement>, std::map<std::string, core::Any>>	m_attProperties;
};

}
}