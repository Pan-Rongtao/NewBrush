#pragma once
#include <map>
#include "../core/Def.h"
#include "../core/Event.h"
#include "Poco/Dynamic/Var.h"

namespace nb{ 
namespace gui{

class NB_API DataContext
{
public:
	virtual ~DataContext() = default;

	//����
	void setName(const std::string &name);
	std::string name() const;

	std::weak_ptr<DataContext>	m_parent;
protected:
	DataContext(const std::string &name);

private:
	std::string					m_name;
};
using DataContextPtr = std::shared_ptr<DataContext>;

class ObjectData;
using ObjectDataPtr = std::shared_ptr<ObjectData>;
using ChildernContainer = std::map<std::string, DataContextPtr>;
using ChildConstIterator = ChildernContainer::const_iterator;

class NB_API ObjectData : public DataContext, public std::enable_shared_from_this<ObjectData>
{
public:
	ObjectData(const std::string &name);
	virtual ~ObjectData() = default;

	//���һ���ӽڵ�
	void insertChild(DataContextPtr child);

	//ɾ��һ���ӽڵ�
	void removeChild(const std::string & childName);

	//�Ƿ����ӽڵ�
	bool hasChild(const std::string & childName) &;

	//��ȡ�ӽڵ㣬�����ڷ��ؿ�
	DataContextPtr getChild(const std::string &childName);

	//��·����ѯ�ڵ�
	//path������"a.b.c"����ʾ���һ��ڵ�ǰ�ڵ��µ�a/b/c�ڵ�
	//�Ҳ������ؿ�
	DataContextPtr lookup(const std::string &path);

	DataContextPtr operator [](const std::string &name);

private:
	ChildernContainer	m_children;
};

class NB_API ValueDataBase : public DataContext, public std::enable_shared_from_this<ValueDataBase>
{
public:
	virtual const std::type_info &type() const { return typeid(void); }
	virtual Var getAny() const { return Var(); }

	struct ValueChangedArgs { std::shared_ptr<DataContext> root; std::string path; };
	Event<ValueChangedArgs>		ValueChanged;		//ֵ�ı��¼�
	
protected:
	ValueDataBase(const std::string &name) : DataContext(name) {}
};
using ValueDataBasePtr = std::shared_ptr<ValueDataBase>;

template<class T>
class ValueData : public ValueDataBase
{
public:
	ValueData(const std::string &name, const T &v = T())
		: ValueDataBase(name)
		, m_v(v)
	{
	}

	void set(const T &v)
	{
		if (v != m_v.extract<T>())
		{
			m_v = v;
			std::string path = name();
			std::weak_ptr<DataContext> p = shared_from_this();
			while (p.lock()->m_parent.lock())
			{
				p = p.lock()->m_parent;
				if(p.lock()->m_parent.lock())
					path = p.lock()->name() + "." + path;
			}
			ValueChanged.invoke({ p.lock() , path });
		}
	}
	T get() { return m_v.extract<T>(); }
	const T get() const { return m_v.extract<T>(); }

	virtual Var getAny() const override { return m_v; }

	virtual const std::type_info &type() const override { return typeid(T); }

	void operator = (const T &v)	{ set(v); }
	bool operator != (const T &v) const { return m_v != v; }
	bool operator == (const T &v) const { return !(operator!=(v)); }

private:
	Var	m_v;
};


}}
