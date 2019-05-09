/*******************************************************
**	Property_rw, Property_r, Property_w
**
**	������
**		���Ը��ⲿ�ṩ����ķ���Ȩ�޿��Ƶ�������ʹ��һ��
**	���Ծ���ʹ��һ������һ�����㡣��ͬ�������ṩ��ͬ�ķ���
**	������Property_rw����д��Property_r��ֻ����Property_w��
**	ֻд��
**
**		ֻ�п�д���������Ͳ��ܰ��ⲿ����������һ��
**	std::function�����Է���һ�������������һ�����ԣ���
**	һ����ִ�к������lambda���ʽ��
**
**
********************************************************/
#pragma once
#include <functional>
#include "../core/Def.h"

namespace nb{namespace core{

template<typename T>
class Property_rw
{
public:
	Property_rw() : m_v(T())  {}
	Property_rw(T v) : m_v(v) {}

	//����֪ͨ����
	void notify(std::function<void(const T &, const T &)> notify)
	{
		m_notify = std::move(notify);
	}

	//�󶨣����������ⷵ��T&�ĺ��������ʽ���󶨺����Է���ֵ���ܰ󶨺���Ӱ�죬�������nullptr��ʾȡ����
	void bind(std::function<T&(void)> binder)
	{
		m_binder = std::move(binder);
	}

	void operator =(const Property_rw<T> &other)
	{
		operator=(other.m_binder ? other.m_binder() : other.m_v);
	}

	void operator =(const T &v)
	{
		if (m_v != v)
		{
			T old = m_v;
			m_v = v;
			if (m_notify)
				m_notify(old, m_v);
		}
	}

	bool operator == (const T &v) const { return v == operator()(); }
	bool operator != (const T &v) const { return !operator==(v); }

	operator const T&() const
	{
		return m_binder ? m_binder() : m_v;
	}

	T & operator()()
	{
		return m_binder ? m_binder() : m_v;
	}

	const T & operator()() const
	{
		return m_binder ? m_binder() : m_v;
	}

private:
	std::function<void(const T &, const T &)>	m_notify;
	std::function<T&(void)>						m_binder;
	T											m_v;
};

template<typename T>
class Property_r
{
public:
	Property_r() : m_v(T()) {}
	explicit Property_r(T v) : m_v(v) {}
	void operator = (const T &v) = delete;
	void operator = (const Property_r<T> &v) = delete;

	//�󶨣����������ⷵ��T&�ĺ��������ʽ���󶨺����Է���ֵ���ܰ󶨺���Ӱ�죬�������nullptr��ʾȡ����
	void getter(std::function<T&(void)> getter)
	{
		m_getter = getter;
	}

	operator const T&() const
	{
		return m_getter ? m_getter() : m_v;
	}
	const T & operator()() const
	{
		return m_getter ? m_getter() : m_v;
	}

private:
	std::function<T &(void)>	m_getter;
	T								m_v;
};


template<typename T>
class Property_w
{
public:
	Property_w() : m_v(T()) {}
	Property_w(const T &v) : m_v(v) {}

	void notify(std::function<void(const T &, const T &)> notify)
	{
		m_notify = std::move(notify);
	}

	void operator =(const Property_w<T> &other)
	{
		operator=(other.m_v);
	}

	void operator =(const T &v)
	{
		if (m_v != v)
		{
			T old = m_v;
			m_v = v;
			if (m_notify)
				m_notify(old, m_v);
		}
	}

private:
	std::function<void(const T &, const T &)>	m_notify;
	T											m_v;
};

}}