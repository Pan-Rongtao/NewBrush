#pragma once
#include <unordered_map>
#include "newbrush/Object.h"

namespace nb 
{

class NB_API ResourceDictionary
{
public:
	ResourceDictionary() = default;
	static ResourceDictionary fromFile(const std::string &path);

	//���һ����Դ
	//�쳣��std::logic_error���Ѿ�����ͬkey����Դ
	void add(const std::string &key, const var &v);

	//�Ƴ�һ����Դ
	void remove(const std::string &key);

	//�����Դ
	void clear();

	//������Դ
	var &find(const std::string &key);
	const var &find(const std::string &key) const;

	//����
	int count() const;
	

private:
	std::unordered_map<std::string, var>	m_resmap;
};

NB_API ref<ResourceDictionary> globalResources();

}