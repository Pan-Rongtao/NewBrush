﻿#pragma once
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

class NB_API Range
{
public:
	Range(Var lowerBound, Var upperBound, Var step);

	Var lowerBound() const;
	Var upperBound() const;
	Var step() const;

private:
	Var m_lowerBound;
	Var m_upperBound;
	Var m_step;
};

enum class PropertyCategoryE
{
	Brush = 0,	//画笔
	Appearance,	//外观
	Public,		//公共
	Automation,	//自动化
	Layout,		//布局
	Text,		//文本
	Transform,	//转换
	Misc,		//杂项
	Custom,		//自定义
};

class NB_API PropertyMetadata
{
public:
	//构建一个PropertyMetadata
	//defaulValue：默认值
	//propertyChangedCallback：属性已改变回调
	//coerceValueCallback：属性值矫正回调
	PropertyMetadata(const Var &defaultValue, PropertyChangedCallback propertyChangedCallback = nullptr, CoerceValueCallback coerceValueCallback = nullptr, const std::string &category = "", const std::string &description = "", std::shared_ptr<Range> range = nullptr);

	void setDefaultValue(const Var &value) &;
	Var defaultValue() const;
	bool isSealed() const;
	PropertyChangedCallback propertyChangedCallback();
	CoerceValueCallback coerceValueCallback();
	const std::string &category() const;
	const std::string &description() const;
	std::shared_ptr<Range> range() const;
	
private:
	Var						m_defaultValue;
	PropertyChangedCallback	m_propertyChangedCallback;
	CoerceValueCallback		m_coerceValueCallback;
	std::string				m_category;
	std::string				m_description;
	std::shared_ptr<Range>	m_range;
};


class NB_API DependencyProperty final
{
public:
	//属性名字
	const std::string &name() const;

	//宿主类型
	std::type_index ownerType() const;

	//宿主类型
	std::type_index propertyType() const;

	//元数据
	std::shared_ptr<PropertyMetadata> defaultMetadata() const;

	//是否可改写
	bool readOnly() const;

	//唯一标识值
	size_t globalIndex() const;

	//检验回调
	ValidateValueCallback validateValueCallback() const;

	bool isInvalid() const;

	bool operator == (const DependencyProperty &other) const;
	bool operator != (const DependencyProperty &other) const;

	//注册一个依赖属性，如果此属性已存在，则只修改属性值
	//element：目标元素
	//property_name：属性名
	//property_v：属性值
	static void registerAttached(std::shared_ptr<DependencyObject> element, const std::string &property_name, const Var &property_v);

	
	//查询依赖属性值，如果查询不到，将返回一个空的Var
	//element：目标元素
	//property_name：属性名
	static Var findAttached(std::shared_ptr<DependencyObject> element, const std::string &property_name);

	//注册依赖属性
	//name：属性名
	//propertyType：属性值类型
	//ownerType：属性宿主类型
	//异常：std::invalid_argument [name]参数为空
	//异常：std::logic_error已经注册过同类型属性
	template<class OwnerType, class PropertyType>
	static const DependencyProperty &registerDependency(const std::string &name, const PropertyType &defaultValue, PropertyChangedCallback propertyChangedCallback = nullptr, 
		CoerceValueCallback coerceValueCallback = nullptr, ValidateValueCallback validateValueCallback = nullptr, const std::string &category = "", const std::string &description = "",
		std::shared_ptr<Range> range = nullptr)
	{
		static_assert(std::is_base_of<DependencyObject, OwnerType>::value, "[ownerType] must be DependencyObject type or DependencyObject derived type.");
		auto metadata = std::make_shared<PropertyMetadata>(defaultValue, propertyChangedCallback, coerceValueCallback, category, description, range);
		return registerCommon(name, typeid(OwnerType), typeid(PropertyType), metadata, validateValueCallback);
	}

	static std::vector<DependencyProperty> getTypePropertys(std::type_index ownerType);
	
	static Var unsetValue();
	static const DependencyProperty &invalidProperty();
	static const DependencyProperty &find(size_t globalIndex);

private:
	DependencyProperty(const std::string & name, std::type_index ownerType, std::type_index propertyType, std::shared_ptr<PropertyMetadata> metadata, ValidateValueCallback validateValueCallback, size_t hash);

	static const DependencyProperty &registerCommon(const std::string &name, std::type_index ownerType, std::type_index propertyType, std::shared_ptr<PropertyMetadata> metadata, ValidateValueCallback validateValueCallback);

	//如果不适用std::shared_ptr<DependencyProperty>而是DependencyProperty，会发现studio插件在FreeLibrary时挂死
	//后续要处理这个事情，把DependencyProperty改为std::shared_ptr<DependencyProperty>
	static std::map<std::size_t, DependencyProperty> &dependencyProperties();

	std::string							m_name;
	std::type_index						m_propertyType;
	std::type_index						m_ownerType;
	std::shared_ptr<PropertyMetadata>	m_metadata;
	ValidateValueCallback				m_validateValueCallback;
	size_t								m_hash;

	static std::map<std::shared_ptr<DependencyObject>, std::map<std::string, Var>>	m_attProperties;
};

}