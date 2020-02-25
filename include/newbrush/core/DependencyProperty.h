#pragma once
#include <functional>
#include <string>
#include <map>
#include <typeindex>
#include "newbrush/core/Def.h"
#include "Poco/Dynamic/Var.h"

namespace nb{

using Poco::Dynamic::Var;

class DependencyObject;
class PropertyMetadata;
struct DependencyPropertyChangedEventArgs;
using PropertyChangedCallback = std::function<void(DependencyObject *, DependencyPropertyChangedEventArgs *)>;
using CoerceValueCallback = std::function<Var(DependencyObject *, Var)>;
using ValidateValueCallback = std::function<bool(const Var &value)>;

class NB_API PropertyMetadata
{
public:
	//����һ��PropertyMetadata
	//defaulValue��Ĭ��ֵ
	//propertyChangedCallback�������Ѹı�ص�
	//coerceValueCallback������ֵ�����ص�
	PropertyMetadata(const Var &defaulValue, PropertyChangedCallback propertyChangedCallback = nullptr, CoerceValueCallback coerceValueCallback = nullptr);

	void setDefaultValue(const Var &value) &;
	Var defaultValue() const;
	bool isSealed() const;
	PropertyChangedCallback propertyChangedCallback();
	CoerceValueCallback coerceValueCallback();

private:
	Var						m_defaultValue;
	PropertyChangedCallback	m_propertyChangedCallback;
	CoerceValueCallback		m_coerceValueCallback;
};


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

	bool isInvalid() const;

	bool operator == (const DependencyProperty &other) const;
	bool operator != (const DependencyProperty &other) const;

	//ע��һ���������ԣ�����������Ѵ��ڣ���ֻ�޸�����ֵ
	//element��Ŀ��Ԫ��
	//property_name��������
	//property_v������ֵ
	static void registerAttached(std::shared_ptr<DependencyObject> element, const std::string &property_name, const Var &property_v);

	
	//��ѯ��������ֵ�������ѯ������������һ���յ�Var
	//element��Ŀ��Ԫ��
	//property_name��������
	static Var findAttached(std::shared_ptr<DependencyObject> element, const std::string &property_name);

	//ע����������
	//name��������
	//propertyType������ֵ����
	//ownerType��������������
	//�쳣��std::invalid_argument [name]����Ϊ��
	//�쳣��std::logic_error�Ѿ�ע���ͬ��������
	template<class OwnerType, class PropertyType>
	static const DependencyProperty &registerDependency(const std::string &name, const PropertyType &defaultValue,
		PropertyChangedCallback propertyChangedCallback = nullptr, CoerceValueCallback coerceValueCallback = nullptr, ValidateValueCallback validateValueCallback = nullptr)
	{
		static std::map<std::size_t, DependencyProperty> g_dependencyProperties;
		static_assert(std::is_base_of<DependencyObject, OwnerType>::value, "[ownerType] must be DependencyObject type or DependencyObject derived type.");

		if (name.empty())
		{
			nbThrowException(std::invalid_argument, "'name' is empty.");
		}

		std::hash<std::string> _shash;
		auto _hash = typeid(OwnerType).hash_code() ^ _shash(name);
		auto metadata = std::make_shared<PropertyMetadata>(defaultValue, propertyChangedCallback, coerceValueCallback);
		DependencyProperty dp(name, typeid(OwnerType), typeid(PropertyType), metadata, validateValueCallback, _hash);
		auto p = g_dependencyProperties.insert({ _hash, dp });
		if (!p.second)
		{
			nbThrowException(std::logic_error, "[%s] has already been registered for [%s]", name.data(), typeid(OwnerType).name());
		}

		return p.first->second;
	}
	
	static Var unsetValue();
	static DependencyProperty invalidProperty();

private:
	DependencyProperty(const std::string & name, std::type_index ownerType, std::type_index propertyType, std::shared_ptr<PropertyMetadata> metadata, ValidateValueCallback validateValueCallback, size_t hash);

	std::string							m_name;
	std::type_index						m_propertyType;
	std::type_index						m_ownerType;
	std::shared_ptr<PropertyMetadata>	m_metadata;
	ValidateValueCallback				m_validateValueCallback;
	size_t								m_hash;

	static std::map<std::shared_ptr<DependencyObject>, std::map<std::string, Var>>	m_attProperties;
};

}