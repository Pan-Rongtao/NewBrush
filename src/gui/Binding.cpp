#include "gui/Binding.h"
#include "gui/DataContext.h"

using namespace nb;
using namespace nb::gui;

Binding::Binding()
	: Binding(nullptr, "", BindingModeE::OneWayToTarget)
{
}

Binding::Binding(const std::string & path)
	: Binding(nullptr, path, BindingModeE::OneWayToTarget)
{
}

Binding::Binding(std::shared_ptr<DataContext> source, const std::string & path, BindingModeE mode)
	: m_source(source)
	, m_path(path)
	, m_mode(mode)
{
}

void Binding::setMode(BindingModeE mode) &
{
	m_mode = mode;
}

BindingModeE Binding::mode() const
{
	return m_mode;
}

void Binding::setSource(std::shared_ptr<DataContext> source) &
{
	m_source = source;
}

DataContextPtr Binding::source() const
{
	return m_source;
}

void Binding::setPath(const std::string & path) &
{
	m_path = path;
}

std::string Binding::path() const
{
	return m_path;
}
