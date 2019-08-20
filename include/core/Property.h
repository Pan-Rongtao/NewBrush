/*******************************************************
**	Property_rw, Property_r, Property_w
**
**	������
**		���Ը��ⲿ�ṩ����ķ���Ȩ�޿��Ƶ�������ʹ��һ��
**	���Ծ���ʹ��һ������һ�����㡣��ͬ�������ṩ��ͬ�ķ���
**	������Property_rw����д��Property_r��ֻ������Ӧ�Ķ�д����Ϊ
**	setter��getter��std::function�����Է���һ�������������һ�����ԣ���
**	һ����ִ�к������lambda���ʽ��
**	
**
********************************************************/
#pragma once
#include <functional>
#include "../core/Def.h"

namespace nb{namespace core{
	
template<class T>
class Property_rw
{
public:
	Property_rw(std::function<void(T v)> setter, std::function<T()> getter) 
		: m_setter(new std::function<void(T)>(setter))
		, m_getter(new std::function<T()>(getter))
	{ }
	~Property_rw()								{ delete m_setter; delete m_getter; }
	void operator =(const T &v)					{ (*m_setter)(v); }
	bool operator == (const T &v) const			{ return v == operator()(); }
	bool operator != (const T &v) const			{ return !operator==(v); }
	T operator()() const						{ return (*m_getter)(); }
	void operator =(const Property_rw<T> &other) = delete;
	
private:
	std::function<void(T)>	*m_setter{ nullptr };
	std::function<T()>		*m_getter{ nullptr };
};

template<typename T>
class Property_r
{
public:
	explicit Property_r(std::function<T()> getter)
		: m_getter(new std::function<T()>(getter))
	{ }
	~Property_r()								{ delete m_getter; }
	bool operator == (const T &v) const			{ return v == operator()(); }
	bool operator != (const T &v) const			{ return !operator==(v); }
	T operator()() const						{ return (*m_getter)(); }
	void operator = (const Property_r<T> &v)	= delete;
	void operator = (const T &v)				= delete;

private:
	std::function<T()>		*m_getter{ nullptr };
};


}}