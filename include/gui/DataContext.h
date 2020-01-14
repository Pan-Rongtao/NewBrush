#pragma once
#include <map>
#include "../core/Def.h"
#include "../core/Event.h"
#include "Poco/JSON/Object.h"
#include "Poco/JSON/Array.h"
#include "Poco/Dynamic/Var.h"

namespace nb{ 
namespace gui{

class NB_API DataContext
{
public:
	virtual ~DataContext() = default;

	virtual void set(const Var &value) &;
	virtual Var get() const;
	virtual std::shared_ptr<DataContext> lookup(const std::string &path) const;
	virtual const std::type_info &type() const;

	struct ValueChangedArgs { DataContext *root; std::string path; };
	Event<ValueChangedArgs>		ValueChanged;		//ֵ�ı��¼�
	
protected:
	DataContext(const std::string &_name);

private:
	DataContext *getRoot() const;
	std::string getAbsPath() const;
	std::string getPath() const;

	std::string	name;
	DataContext *parent;
	friend class DataObject;
	template<class T> friend class VarData;
};

class NB_API DataObject : public DataContext
{
public:
	DataObject(const std::string &name);

	//���һ���ӽڵ�
	void add(std::shared_ptr<DataContext> child) &;

	//ɾ��һ���ӽڵ�
	void remove(const std::string & childName) &;

	//�Ƿ����ӽڵ�
	bool has(const std::string & childName) const;

	//��ȡ�ӽڵ㣬�����ڷ��ؿ�
	std::shared_ptr<DataContext> get(const std::string &childName) const;
	std::shared_ptr<DataObject> getObject(const std::string &childName) const;

	//��·����ѯ�ڵ�
	//path������"a.b.c"����ʾ���һ��ڵ�ǰ�ڵ��µ�a/b/c�ڵ�
	//�Ҳ������ؿ�
	virtual std::shared_ptr<DataContext> lookup(const std::string &path) const override;

	virtual const std::type_info &type() const;

	static std::shared_ptr<DataObject> gen(const std::string &name);

private:
	std::map<std::string, std::shared_ptr<DataContext>>	m_children;
};

template<class T>
class VarData : public DataContext
{
public:
	VarData(const std::string &name, const T &v = T())
		: DataContext(name)
		, m_v(v)
	{
	}

	void set(const T &v)
	{
		set(Var(T));
	}

	virtual void set(const Var &v) &
	{
		auto root = getRoot();
		auto path = getPath();
		if (m_v.type() == v.type())
		{
			m_v = v;
			root->ValueChanged.invoke({ root, path });
		}
		else
		{
			bool bEqual = false;
			try {
				bEqual = m_v == v;
			}
			catch (...) {
				nbThrowException(std::logic_error, "should set for [%s] with [%s] but not [%s].", getAbsPath().data(), m_v.type().name(), v.type().name());
			}

			if (!bEqual)
			{
				m_v = v;
				root->ValueChanged.invoke({ root, path });
			}
		}
	}
	virtual Var get() const override { return m_v; }

	virtual const std::type_info &type() const override { return typeid(T); }

	static std::shared_ptr<VarData<T>> gen(const std::string &name, const T &v = T())
	{
		return std::make_shared<VarData<T>>(name, v);
	}

private:
	Var	m_v;
};


}}
