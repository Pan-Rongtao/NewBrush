/*******************************************************
**	Storage
**
**	�洢��
**		Storage�������洢uniform�Լ�ֵ�����ݽṹ
**
**
**		������
**
********************************************************/
#pragma once
#include <map>
#include <string>
#include "../core/Def.h"
#include "../core/Any.h"

namespace nb{ namespace gl{

class NB_API Storage
{
public:
	Storage() = default;
	~Storage() = default;

	template<class T>
	void insert(const std::string &name, const T &v)
	{
		m_uniforms.insert(std::make_pair(name, v));
	}

	const std::map<std::string, nb::core::Any> &uniforms() const;

	void clear();

private:
	std::map<std::string, nb::core::Any>	m_uniforms;
};

} }