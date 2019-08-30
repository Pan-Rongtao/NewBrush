#pragma once
#include "../gui/Property.h"
#include "../gui/DataContext.h"

namespace nb{
namespace gui{
	
class NB_API Binding
{
public:
	//��������
	enum class ModeE
	{
		OneTime,		//��һ��
		OneWayToTarget,	//����Ŀ��
		OneWayToSource,	//����Դ
		TwoWay,			//˫��
	};

	Binding();
	Binding(const std::string &path);
	Binding(DataContextPtr source, const std::string &path, ModeE mode = ModeE::OneWayToTarget);
	~Binding() = default;

	//����������ģʽ
	void setMode(ModeE mode);
	ModeE mode() const;

	//Դ
	void setSource(DataContextPtr source);
	DataContextPtr source() const;

	//����·��
	void setPath(const std::string &path);
	std::string path() const;

private:
	ModeE			m_mode;
	DataContextPtr	m_source;
	std::string		m_path;
};

using BindingPtr = std::shared_ptr<Binding>;

}}