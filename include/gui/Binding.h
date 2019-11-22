#pragma once
#include "../core/Def.h"

namespace nb{
namespace gui{
	
class DataContext;
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
	Binding(std::shared_ptr<DataContext> source, const std::string &path, ModeE mode = ModeE::OneWayToTarget);
	~Binding() = default;

	//����������ģʽ
	void setMode(ModeE mode);
	ModeE mode() const;

	//Դ
	void setSource(std::shared_ptr<DataContext> source);
	std::shared_ptr<DataContext> source() const;

	//����·��
	void setPath(const std::string &path);
	std::string path() const;

private:
	ModeE							m_mode;
	std::shared_ptr<DataContext>	m_source;
	std::string						m_path;
};

using BindingPtr = std::shared_ptr<Binding>;

}}