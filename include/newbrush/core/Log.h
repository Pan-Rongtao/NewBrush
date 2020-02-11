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
#include "newbrush/core/Def.h"

namespace nb
{

class NB_API Log
{
public:
	//���һ��info��־
	template<class... ARGS>
	static void info(const char *format, ARGS... args)
	{
		printf((std::string("[INFO] ") + format + "\n").data(), args...);
	}

	//���һ��warn��־
	template<class... ARGS>
	static void warn(const char *format, ARGS... args)
	{
		printf((std::string("[WARN] ") + format + "\n").data(), args...);
	}

	//���һ��error��־
	template<class... ARGS>
	static void error(const char *format, ARGS... args)
	{
		printf((std::string("[ERROR] ") + format + "\n").data(), args...);
	}

	//���һ��debug��־
	//ע�⣺����debugģʽ�²������
	template<class... ARGS>
	static void debug(const char *format, ARGS... args)
	{
#ifndef NDEBUG
		printf((std::string("[DEBUG] ") + format + "\n").data(), args...);
#endif
	}
};

}