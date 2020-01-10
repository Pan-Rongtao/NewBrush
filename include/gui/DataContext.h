#pragma once
#include <map>
#include "../core/Def.h"
#include "../core/Event.h"
#include "Poco/JSON/Object.h"
#include "Poco/JSON/Array.h"
#include "Poco/Dynamic/Var.h"

namespace nb{ 
namespace gui{

class NB_API DataVar : public Poco::Dynamic::Var
{
public:
	DataObject *parent;
};

class NB_API DataObject
{
public:
	DataObject(const std::string &name);
	virtual ~DataObject() = default;

	//��������
	//�쳣�����ֵܽڵ�����
	void setName(const std::string &name) &;
	std::string name() const;

	//��ȡֵ
	DataVar get(const std::string &key) const;

	//��ȡ�����ӽڵ�ļ�ֵ
	void getKeys(std::vector<std::string> &keys) const;
	std::vector<std::string> getKeys() const;

	//�Ƿ�����Ϊkey���ӽڵ�
	bool has(const std::string &key) const;

	//�ӽڵ����
	std::size_t childCount() const;

	//�����ӽڵ��ֵ��������ӽڵ㲻���ڣ��Զ�����
	void set(const std::string &key, const DataVar &value) &;

	//�Ƴ��ӽڵ�
	void remove(const std::string &key) &;

	struct ValueChangedArgs { std::shared_ptr<DataContext> root; std::string path; };
	Event<ValueChangedArgs>		ValueChanged;		//ֵ�ı��¼�

private:
	std::string			m_name;
	DataObject			*m_parent;
	Poco::JSON::Object	m_obj;
};

}}
