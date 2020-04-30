#pragma once
#include "newbrush/core/Def.h"
#include "newbrush/core/MetaObject.h"

namespace nb {

class MetaObject;
class NB_API Object
{
public:
	Object() = default;
	virtual ~Object() = default;

	//����Ӧ����д�˺��������Լ���MetaObject��Ϣ
	static MetaObject *getMetaObject();

	//������д����getMetaObject()����
	virtual MetaObject *metaObject();
};

#define NB_OBJECT\
	static MetaObject *getMetaObject();\
	virtual MetaObject *metaObject() override\
	{\
		return getMetaObject();\
	}

}