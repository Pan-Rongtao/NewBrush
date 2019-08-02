/*******************************************************
**	Log
**
**	��־
**
**		�����̨�����Ϣ
**
**		������
**
********************************************************/
#pragma once
#include "Def.h"

namespace nb
{

class NB_API Log
{
public:
	//���һ��info��־
	static void info(const char *format, ...);

	//���һ��warn��־
	static void warn(const char *format, ...);

	//���һ��error��־
	static void error(const char *format, ...);

	//���һ��debug��־
	//ע�⣺����debugģʽ�²������
	static void debug(const char *format, ...);
};

}