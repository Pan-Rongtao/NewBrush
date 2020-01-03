#include "gui/Panel.h"
#include "gles/Viewport2D.h"

using namespace nb;
using namespace nb::gui;

Panel::Panel()
	: Background([&](std::shared_ptr<Brush> v) {set(BackgroundProperty(), v); }, [&]()->std::shared_ptr<Brush>& {return get<std::shared_ptr<Brush>>(BackgroundProperty()); })
	, Children([&](UIElementCollection v) {m_children = v; }, [&]()->UIElementCollection & {return m_children; })
	, m_children(this)
{
}

void Panel::setZIndex(std::shared_ptr<UIElement> element, int index)
{
}

int Panel::getZIndex(std::shared_ptr<UIElement> element)
{
	return 0;
}

DependencyProperty Panel::BackgroundProperty()
{
	static auto dp = DependencyProperty::registerDependency<Panel, std::shared_ptr<Brush>>("Background", nullptr);
	return dp;
}

void Panel::onRender(Viewport2D & drawContext)
{
	for (auto i = 0u; i < m_children.count(); ++i)
	{
		auto child = m_children.childAt(i);
		child->onRender(drawContext);
	}
}
