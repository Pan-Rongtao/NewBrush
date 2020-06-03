#pragma once
#include "newbrush/core/Def.h"

namespace nb {

class StudioPlugin
{
public:
	virtual void getMetametaObjectsOverride() = 0;

};

struct CPropertyInfo
{
	uint64_t	typeID = 0;			//����ID��Ψһ��
	char	valueTypeName[128] = {};//ֵ����
	char	category[64] = {};		//����
	char	displayName[64] = {};	//��ʾ��
	char	description[256] = {};	//����
	char	enumSource[512] = {};	//ö��ֵ�ַ�����ϣ������ö�����ͣ������� "Enum0|Enum1|Enum2"����'|'��Ϊ�ָ���
};

struct CClassInfo
{
	char	typeName[64] = {};
	char	category[64] = {};
	char	displayName[64] = {};
	char	description[256] = {};
	CPropertyInfo propertys[100] = {};
};

}