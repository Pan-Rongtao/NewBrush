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

namespace nb{

template<class T>
class Property_rw
{
public:
	Property_rw(std::function<void(T v)> setter, std::function<T&()> getter)  : m_setter(std::move(setter)) , m_getter(std::move(getter)) { }
	void operator =(const T &v) &				{ try { m_setter(v); } catch (std::bad_function_call &e) { (void)e; nbThrowException(std::runtime_error, "null setter"); } }
	bool operator == (const T &v) const			{ return !operator!=(v);  }
	bool operator != (const T &v) const			{ return v != operator()(); }
	const T&operator()() const					{ return const_cast<Property_rw *>(this)->operator()(); }
	T &operator()()								{ try { return m_getter(); } catch (std::bad_function_call &e) { (void)e; nbThrowException(std::runtime_error, "null getter"); } }
	operator T() const							{ return operator()(); }
	const std::type_info &type() const			{ return typeid(T); }
	
private:
	std::function<void(T)>	m_setter;
	std::function<T&()>		m_getter;
};

template<typename T>
class Property_r
{
public:
	explicit Property_r(std::function<T()> getter) : m_getter(std::move(getter)) { }
	bool operator == (const T &v) const			{ return !operator!=(v); }
	bool operator != (const T &v) const			{ return v != operator()();  }
	T operator()() const						{ try { return m_getter(); } catch (std::bad_function_call &e) { (void)e; nbThrowException(std::runtime_error, "null getter"); } }
	void operator = (const Property_r<T> &v)	= delete;
	void operator = (const T &v)				= delete;
	operator T() const							{ return operator()(); }
	const std::type_info &type() const			{ return typeid(T); }

private:
	std::function<T()>		m_getter;
};

}