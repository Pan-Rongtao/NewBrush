#pragma once
#include <unordered_map>
#include "../core/Def.h"
#include "../core/Any.h"

namespace nb {
namespace gui{

class NB_API ResourceDictionary
{
public:
	ResourceDictionary() = default;
	static ResourceDictionary fromFile(const std::string &path);

	//���һ����Դ
	//�쳣��std::logic_error���Ѿ�����ͬkey����Դ
	void add(const std::string &key, const Any &v);

	//�Ƴ�һ����Դ
	void remove(const std::string &key);

	//�����Դ
	void clear();

	//������Դ
	Any &find(const std::string &key);
	const Any &find(const std::string &key) const;

	//����
	int count() const;
	

private:
	std::unordered_map<std::string, Any>	m_resmap;
};

}
}