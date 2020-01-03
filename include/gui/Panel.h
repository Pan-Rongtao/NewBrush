#pragma once
#include "../gui/UIElement.h"
#include "../gui/UIElementCollection.h"

namespace nb{
class Brush;
namespace gui{

class NB_API Panel : public UIElement
{
public:
	virtual ~Panel() = default;

	Property_rw<std::shared_ptr<Brush>>	Background;				//����
	Property_rw<UIElementCollection>	Children;				//��Ԫ�ؼ���
	static DependencyProperty		BackgroundProperty();	//��������������

	void setZIndex(std::shared_ptr<UIElement> element, int index);
	int getZIndex(std::shared_ptr<UIElement> element);

	virtual void onRender(Viewport2D & drawContext) override;

protected:
	Panel();

	UIElementCollection	m_children;
};

}}