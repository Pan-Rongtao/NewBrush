/*******************************************************
**	Any������ֵ��
**
**	Any��һ�ֿ���װ����������ֵ�����ͣ��������ڹ����в�����
**	�͸�������������ֵ��Ҫ���Ǹ�����ʵ����=�������͸��ƹ��캯��
**
**		������
**
********************************************************/
#pragma once
#include <typeinfo>
#include "Def.h"

namespace nb{

class Any
{
public:
	class Holder
	{
	public:
		virtual ~Holder() {}
		virtual const std::type_info &type() const = 0;
		virtual Holder *clone() const = 0;
	};

	template<typename T>
	class HolderImp : public Holder
	{
	public:
		HolderImp(const T &v) 
			: m_v(v) 
		{}

		virtual const std::type_info &type() const override
		{ 
			return typeid(T); 
		}

		virtual Holder *clone() const override 
		{
			return new HolderImp(m_v);
		}

	public:
		T m_v;
	};

public:
	Any() : m_holder(nullptr) {}

	template<typename T>
	Any(const T &v) 
		: m_holder(new HolderImp<T>(v)) 
	{}

	Any(const Any &other) 
		: m_holder(other.m_holder ? other.m_holder->clone() : nullptr) 
	{}

	Any &operator=(const Any &other)
	{
		Any(other).swap(*this);
		return *this;
	}

	template<typename T>
	Any & operator=(const T &other)
	{
		Any(other).swap(*this);
		return *this;
	}

	~Any() 
	{
		delete m_holder;
	}

	Any &swap(Any &other)
	{
		std::swap(m_holder, other.m_holder);
		return *this;
	}

	bool empty() const
	{
		return !m_holder;
	}

	const std::type_info &type() const
	{
		return m_holder ? m_holder->type() : typeid(void);
	}

private:
	Holder	*m_holder;
	template<typename T> friend T any_cast(const Any &any);
};

template<typename T>
T any_cast(const Any &any)
{
	if (any.type() != typeid(T))	throw std::bad_cast();
	return static_cast<Any::HolderImp<T> *>(any.m_holder)->m_v;
}

}