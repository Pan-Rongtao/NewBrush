﻿#pragma once
#include "newbrush/core/Def.h"
#include "rttr/registration.h"

namespace nb {

//请勿修改枚举值的顺序和定向指定值
enum class RttrClassMetadataIndex
{
	AsVisual = 0,	//是否注册为可在STUDIO上创建的UI元素（如果该class不是继承于UIElement，将自动判定为false；该字段如果为false，Category、DisplayName、Description将无意义）
	Category,		//分类
	DisplayName,	//是否可视
	Description,	//是否可视

	Property0 = 5,
	Property1,
	Property2,
	Property3,
	Property4,
	Property5,
	Property6,
	Property7,
	Property8,
	Property9,
	Property10,
	Property11,
	Property12,
	Property13,
	Property14,
	Property15,
	Property16,
	Property17,
	Property18,
	Property19,
	Property20,
	Property21,
	Property22,
	Property23,
	Property24,
	Property25,
	Property26,
	Property27,
	Property28,
	Property29,
	Property30,
	Property31,
	Property32,
	Property33,
	Property34,
	Property35,
	Property36,
	Property37,
	Property38,
	Property39,
	Property40,
	Property41,
	Property42,
	Property43,
	Property44,
	Property45,
	Property46,
	Property47,
	Property48,
	PropertyMax,

};

class DependencyProperty;
using DependencyPropertyPtr = std::shared_ptr<DependencyProperty>;
class NB_API RttrRegistration
{
public:
	//获取类型的自身属性（不包括继承的属性）
	static std::vector<DependencyPropertyPtr> getTypeSelfPropertys(rttr::type t);

	//获取类型的所有属性（包括继承的属性）
	static std::vector<DependencyPropertyPtr> getTypeAllPropertys(rttr::type ownerType);
};


}