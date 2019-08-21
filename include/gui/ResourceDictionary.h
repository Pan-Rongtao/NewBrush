#pragma once
#include <unordered_map>
#include "../core/Def.h"
#include "../core/Any.h"

namespace nb {
namespace gui{

class NB_API ResourceDictionary
{
public:
	//���һ����Դ
	//�쳣��std::logic_error���Ѿ�����ͬkey����Դ
	template<class resT>
	void add(const std::string &key, const resT &v);

	//�Ƴ�һ����Դ
	void remove(const std::string &key);

	//�����Դ
	void clear();

	//������Դ
	Any &find(const std::string &key);
	const Any &find(const std::string &key) const;

private:
	std::unordered_map<std::string, Any>	m_resmap;
};

template<class resT>
inline void ResourceDictionary::add(const std::string & key, const resT & v)
{
	if (m_resmap.find(key))
		nbThrowException(std::logic_error, "[%s] already exists.", key.data());
	else
		m_resmap[key] = v;
}

}
}