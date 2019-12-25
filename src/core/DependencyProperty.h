#pragma once
#include <string>
#include <map>
#include <typeindex>
#include "../core/Any.h"
#include "../core/PropertyMetadata.h"

namespace nb{

class DependencyObject;
using ValidateValueCallback = std::function<bool(const Any &value)>;
class NB_API DependencyProperty final
{
public:
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
	
	//ע��һ���������ԣ�����������Ѵ��ڣ���ֻ�޸�����ֵ
	//element��Ŀ��Ԫ��
	//property_name��������
	//property_v������ֵ
	static void registerAttached(std::shared_ptr<DependencyObject> element, const std::string &property_name, const Any &property_v);

	
	//��ѯ��������ֵ�������ѯ������������һ���յ�Any
	//element��Ŀ��Ԫ��
	//property_name��������
	static Any findAttached(std::shared_ptr<DependencyObject> element, const std::string &property_name);

	//ע����������
	//name��������
	static const DependencyProperty &registerDependency(const std::string & name, std::type_index propertyType, std::type_index ownerType)
	{
		registerDependency(name, propertyType, ownerType, nullptr, nullptr);
	}

	//ע����������
	//name��������
	static const DependencyProperty &registerDependency(const std::string & name, std::shared_ptr<PropertyMetadata> metadata)
	{
		registerDependency(name, metadata, nullptr);
	}
	
	//ע����������
	//name��������
	//propertyType������ֵ����
	//ownerType��������������
	//�쳣��std::logic_error�Ѿ�ע���ͬ��������
	static const DependencyProperty &registerDependency(const std::string & name, std::type_index propertyType, std::type_index ownerType, std::shared_ptr<PropertyMetadata> metadata, ValidateValueCallback validateValueCallback)
	{
		static std::map<std::size_t, DependencyProperty> g_dependencyProperties;

		std::hash<std::string> _shash;
		auto hash = typeid(ownerType).hash_code() ^ _shash(name);
		if (g_dependencyProperties.find(hash) != g_dependencyProperties.end())
		{
			nbThrowException(std::logic_error, "[%s] has already been registered for [%s]", name.data(), typeid(ownerType).name());
		}

		DependencyProperty dp;
		dp.m_name = name;
		dp.m_hash = hash;
		dp.m_isSealed = isSealed;
		dp.m_defaultV = defaultValue;
		g_dependencyProperties[hash] = dp;
		return g_dependencyProperties[hash];
	}

private:
	std::string							m_name;
	std::type_index						m_ownerType;
	std::type_index						m_propertyType;
	std::shared_ptr<PropertyMetadata>	m_metadata;
	size_t								m_hash{0};
	ValidateValueCallback				m_validateValueCallback;

	static std::map<std::shared_ptr<DependencyObject>, std::map<std::string, Any>>	m_attProperties;
};

}