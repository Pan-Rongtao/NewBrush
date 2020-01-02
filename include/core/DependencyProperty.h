#pragma once
#include <functional>
#include <string>
#include <map>
#include <typeindex>
#include "../core/Any.h"

namespace nb{

class DependencyObject;
class PropertyMetadata;
using ValidateValueCallback = std::function<bool(const Any &value)>;
class NB_API DependencyProperty final
{
public:
	//��������
	const std::string &name() const;

	//��������
	std::type_index ownerType() const;

	//��������
	std::type_index propertyType() const;

	//Ԫ����
	std::shared_ptr<PropertyMetadata> defaultMetadata() const;

	//�Ƿ�ɸ�д
	bool readOnly() const;

	//Ψһ��ʶֵ
	size_t globalIndex() const;

	//����ص�
	ValidateValueCallback validateValueCallback() const;

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
	//propertyType������ֵ����
	//ownerType��������������
	//�쳣��std::logic_error�Ѿ�ע���ͬ��������
	template<class ownerType, class propertyType>
	static DependencyProperty registerDependency(const std::string & name, std::shared_ptr<PropertyMetadata> metadata, ValidateValueCallback validateValueCallback)
	{
		static_assert(std::is_base_of<DependencyObject, ownerType>::value, "registerDependency<ownerType, propertyType> : ownerType must be DependencyObject or a derived type.");

		std::hash<std::string> _shash;
		auto hash = typeid(ownerType).hash_code() ^ _shash(name);
		if (g_dependencyProperties.find(hash) != g_dependencyProperties.end())
			nbThrowException(std::logic_error, "[%s] has already been registered for [%s]", name.data(), typeid(ownerType).name());

		DependencyProperty dp(name, propertyType, ownerType, metadata, validateValueCallback);
		dp.m_hash = hash;
		g_dependencyProperties.insert({ hash, dp });
		return dp;
	}


	static Any unsetValue();

private:
	DependencyProperty(const std::string & name, std::type_index propertyType, std::type_index ownerType, std::shared_ptr<PropertyMetadata> metadata, ValidateValueCallback validateValueCallback);
	static DependencyProperty registerCommon(const std::string & name, std::type_index propertyType, std::type_index ownerType, std::shared_ptr<PropertyMetadata> metadata, ValidateValueCallback validateValueCallback);
	static std::shared_ptr<PropertyMetadata> autoGeneratePropertyMetadata(std::type_index propertyType, ValidateValueCallback validateValueCallback, const std::string &name, std::type_index ownerType);

	std::string							m_name;
	std::type_index						m_propertyType;
	std::type_index						m_ownerType;
	std::shared_ptr<PropertyMetadata>	m_metadata;
	ValidateValueCallback				m_validateValueCallback;
	size_t								m_hash;

	static std::map<std::size_t, DependencyProperty> g_dependencyProperties;
	static std::map<std::shared_ptr<DependencyObject>, std::map<std::string, Any>>	m_attProperties;
};

}