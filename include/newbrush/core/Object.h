#pragma once
#include "newbrush/core/Def.h"
#include "rttr/registration.h"

namespace nb {

class MetaObject;
class DependencyProperty;
using DependencyPropertyPtr = std::shared_ptr<DependencyProperty>;
using rttr::variant;

class NB_API Object
{
	RTTR_ENABLE()
public:
	Object() = default;
	virtual ~Object() = default;

	//����Ӧ����д�˺��������Լ���MetaObject��Ϣ
	static std::shared_ptr<MetaObject> getMetaObject();

	//������д����getMetaObject()����
	virtual std::shared_ptr<MetaObject> metaObject();

};

#define NB_OBJECT \
public:\
	static std::shared_ptr<MetaObject> getMetaObject();\
	virtual std::shared_ptr<MetaObject> metaObject() override\
	{\
		return getMetaObject();\
	}

}