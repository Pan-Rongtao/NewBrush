#pragma once
#include "newbrush/gui/UIElement.h"
#include "newbrush/gui/UIElementCollection.h"

namespace nb{
class Brush;
class NB_API Panel : public UIElement
{
public:
	Panel(const Panel &other);
	Panel(const Panel &&other);
	Panel &operator =(const Panel &other);
	Panel &operator =(const Panel &&other);
	virtual ~Panel() = default;

	static DependencyProperty BackgroundProperty();	//��������������

	UIElementCollection &children();

	void setZIndex(std::shared_ptr<UIElement> element, int index);
	int getZIndex(std::shared_ptr<UIElement> element);

	virtual void onRender(Viewport2D & drawContext) override;

	virtual uint32_t childrenCount() const;

	virtual UIElement *getChild(uint32_t index);

protected:
	Panel();

	UIElementCollection	m_children;
};

}