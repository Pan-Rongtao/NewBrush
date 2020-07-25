#pragma once
#include "newbrush/core/Event.h"
#include "newbrush/core/data/DataContext.h"
#include "newbrush/core/DependencyProperty.h"

namespace nb{

//����������
enum class BindingModeE
{
	OneTime,		//��һ��
	OneWayToTarget,	//����Ŀ��
	OneWayToSource,	//����Դ
	TwoWay,			//˫��
};

class NB_API Binding
{
public:
	Binding();
	Binding(const std::string &path);
	Binding(DataContextPtr source, const std::string &path, BindingModeE mode = BindingModeE::OneWayToTarget);
	~Binding() = default;

	//����������ģʽ
	void setMode(BindingModeE mode) &;
	BindingModeE mode() const;

	//Դ
	void setSource(DataContextPtr source) &;
	DataContextPtr source() const;

	//����·��
	void setPath(const std::string &path) &;
	std::string path() const;

	struct BindDataChangedEventArgs { var value; };
	Event<BindDataChangedEventArgs> BindDataChanged;

private:
	BindingModeE	m_mode;
	DataContextPtr	m_source;
	std::string		m_path;
};

using BindingPtr = std::shared_ptr<Binding>;
}