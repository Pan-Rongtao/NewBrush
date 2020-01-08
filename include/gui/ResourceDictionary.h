#pragma once
#include <unordered_map>
#include "../core/Def.h"
#include "Poco/Dynamic/Var.h"

namespace nb {
namespace gui{

using Poco::Dynamic::Var;
class NB_API ResourceDictionary
{
public:
	ResourceDictionary() = default;
	static ResourceDictionary fromFile(const std::string &path);

	//���һ����Դ
	//�쳣��std::logic_error���Ѿ�����ͬkey����Դ
	void add(const std::string &key, const Var &v);

	//�Ƴ�һ����Դ
	void remove(const std::string &key);

	//�����Դ
	void clear();

	//������Դ
	Var &find(const std::string &key);
	const Var &find(const std::string &key) const;

	//����
	int count() const;
	

private:
	std::unordered_map<std::string, Var>	m_resmap;
};

}
}