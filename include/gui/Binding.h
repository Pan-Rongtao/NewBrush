#pragma once
#include "../core/Def.h"

namespace nb{
namespace gui{

//����������
enum class BindingModeE
{
	OneTime,		//��һ��
	OneWayToTarget,	//����Ŀ��
	OneWayToSource,	//����Դ
	TwoWay,			//˫��
};

class DataContext;
class NB_API Binding
{
public:
	Binding();
	Binding(const std::string &path);
	Binding(std::shared_ptr<DataContext> source, const std::string &path, BindingModeE mode = BindingModeE::OneWayToTarget);
	~Binding() = default;

	//����������ģʽ
	void setMode(BindingModeE mode) &;
	BindingModeE mode() const;

	//Դ
	void setSource(std::shared_ptr<DataContext> source) &;
	std::shared_ptr<DataContext> source() const;

	//����·��
	void setPath(const std::string &path) &;
	std::string path() const;

private:
	BindingModeE					m_mode;
	std::shared_ptr<DataContext>	m_source;
	std::string						m_path;
};

}}