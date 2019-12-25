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
	static const DependencyProperty &registerDependency(const std::string & name, std::type_index propertyType, std::type_index ownerType);
	static const DependencyProperty &registerDependency(const std::string & name, std::type_index propertyType, std::type_index ownerType, std::shared_ptr<PropertyMetadata> metadata);
	static const DependencyProperty &registerDependency(const std::string & name, std::type_index propertyType, std::type_index ownerType, std::shared_ptr<PropertyMetadata> metadata, ValidateValueCallback validateValueCallback);

private:
	DependencyProperty(const std::string & name, std::type_index propertyType, std::type_index ownerType, std::shared_ptr<PropertyMetadata> metadata, ValidateValueCallback validateValueCallback);
	static const DependencyProperty &registerCommon(const std::string & name, std::type_index propertyType, std::type_index ownerType, std::shared_ptr<PropertyMetadata> metadata, ValidateValueCallback validateValueCallback);
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