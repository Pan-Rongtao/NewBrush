#include "gui/UIElement.h"
#include "gui/Window.h"

using namespace nb::core;
using namespace nb::gl;
using namespace nb::gui;

UIElement::UIElement()
	: Visibility(VisibilityE::Visible)
	, Opacity(1.0)
	, Width(NAN)
	, Height(NAN)
	, MaxWidth(std::numeric_limits<float>::max())
	, MaxHeight(std::numeric_limits<float>::max())
	, HorizontalAlignment(HorizontalAlignmentE::Stretch)
	, VerticalAlignment(VerticalAlignmentE::Stretch)
	, FlowDirection(FlowDirectionE::LeftToRight)
	, Renderer(std::make_shared<nb::gl::RenderObject>())
	, StateMachine(std::make_shared<VisualStateMachine>())
{
	DesiredSize.getter([&]()->Size& { return m_desiredSize; });
	ActualSize.getter([&]()->Size& {return m_actualSize; });
	Width.notify([&](const float &_old, const float &_new) {updateLayout(); });
	Height.notify([&](const float &_old, const float &_new) {updateLayout(); });
	style.notify([&](const std::shared_ptr<Style> &_old, const std::shared_ptr<Style> &_new) {
		
	});
}

UIElement::~UIElement()
{
}

uint32_t UIElement::childCount() const
{
	return m_children.size();
}

void UIElement::addChild(std::shared_ptr<UIElement> child)
{
	m_children.push_back(child);
	child->parent() = shared_from_this();
}

void UIElement::insertChild(uint32_t index, std::shared_ptr<UIElement> child)
{
	if (index > childCount())
		nbThrowException(std::out_of_range, "index");

	m_children.insert(m_children.begin() + index, child);
	child->parent() = shared_from_this();
}

void UIElement::removeChild(std::shared_ptr<UIElement> child)
{
	auto iter = std::find(m_children.begin(), m_children.end(), child);
	if (iter != m_children.end())
	{
		m_children.erase(iter);
		return;
	}
}

void UIElement::removeChild(uint32_t index, uint32_t count)
{
	if(index >= childCount())
		nbThrowException(std::out_of_range, "index[%d] is out of range[0, %d]", index, childCount());
	auto end = index + count < childCount() ? m_children.begin() + index + count : m_children.end();
	m_children.erase(m_children.begin() + index, end);
}

void UIElement::clearChild()
{
	m_children.clear();
}

std::shared_ptr<UIElement> UIElement::parent()
{
	return std::shared_ptr<UIElement>();
}

void UIElement::updateLayout()
{
	measure({ Width, Height });
	arrage(Rect(0, 0, DesiredSize()));
	onRender(gui::Window::DrawContext());
}

void UIElement::measure(const Size & availabelSize)
{
	//������ɼ�������measure����һ�£�����
	if ((Visibility != VisibilityE::Visible))
		return;

	//��ȥmagin�����������constrainedSize
	auto constrainedSize = Size(availabelSize.width() - Margin().left() - Margin().right(), availabelSize.height() - Margin().top() - Margin().bottom());
	//����ֶ�������Width������Width��bound(MinWidth, MaxWidth, Width)
	//���򣬵���Width��(MinWidth, MaxWidth, constrainedSize.width())
	//ͬ���Ĺ���Ӧ����Height
	auto Widthx = nb::clamp<float>(MinWidth, MaxWidth, std::isnan(Width) ? constrainedSize.width() : Width);
	auto Heightx = nb::clamp<float>(MinHeight, MaxHeight, std::isnan(Height) ? constrainedSize.height() : Height);
	constrainedSize.reset(Widthx, Heightx);

	//measureOverride���ؿؼ�������СdesiredSizeTemp����Ҫ��������֤��(Min, Max)����
	//����ֶ�������Width������Width��(MinWidth, MaxWidth, Width)
	//���򣬵���Width��(MinWidth, MaxWidth, constrainedSize.width())
	//ͬ���Ĺ���Ӧ����Height
	auto desiredSizeTemp = measureOverride(constrainedSize);
	auto Widthxx = nb::clamp<float>(MinWidth, MaxWidth, std::isnan(Width) ? desiredSizeTemp.width(): Width);
	auto Heightxx = nb::clamp<float>(MinHeight, MaxHeight, std::isnan(Height) ? desiredSizeTemp.height() : Height);
	desiredSizeTemp.reset(Widthxx, Heightxx);

	//����child����ע�ͼ���magin�����������+margin
	desiredSizeTemp += Size(Margin().left() + Margin().right(), Margin().top() + Margin().bottom());
	//��֤�ڣ�0, availabelSize)����
	desiredSizeTemp.width() = nb::clamp<float>(0.0, availabelSize.width(), desiredSizeTemp.width());
	desiredSizeTemp.height() = nb::clamp<float>(0.0, availabelSize.height(), desiredSizeTemp.height());
	m_desiredSize = desiredSizeTemp;
}

void UIElement::arrage(const Rect & finalRect)
{
	//������ɼ�������arrage����һ�£�����
	if ((Visibility != VisibilityE::Visible))
		return;

	//��ȥmagin�����������arrangeSize�Լ�clientSize
	auto arrangeSize = Size(finalRect.width() - Margin().left() - Margin().right(), finalRect.height() - Margin().top() - Margin().bottom());
	auto clientSize = arrangeSize;
	//����arrange����DesiredSize
	arrangeSize.reset(std::max(DesiredSize().width(), arrangeSize.width()), std::max(DesiredSize().height(), arrangeSize.height()));
	//���Aligment����Stretch��ֱ�ӽ�arrangeSize����ΪDesiredSize���Ա�֤����arrangeOverride��arrangeSizeû��Stretch
	if (HorizontalAlignment != HorizontalAlignmentE::Stretch)
		arrangeSize.setWidth(DesiredSize().width());
	if (VerticalAlignment != VerticalAlignmentE::Stretch)
		arrangeSize.setHeight(DesiredSize().height());

	//����ֶ�������Width������Width��bound(MinWidth, MaxWidth, Width)
	//���򣬵���Width��(MinWidth, MaxWidth, arrangeSize.width())
	//ͬ���Ĺ���Ӧ����Height
	auto Widthx = nb::clamp<float>(MinWidth, MaxWidth, std::isnan(Width) ? arrangeSize.width() : Width);
	auto Heightx = nb::clamp<float>(MinHeight, MaxHeight, std::isnan(Height) ? arrangeSize.height() : Height);
	arrangeSize.reset(Widthx, Heightx);

	//arrangeOverride���RenderSize�ǲ���Ҫ�����ķǲü����򣬶��������յĿɼ�����
	auto innerInkSize = arrangeOverride(arrangeSize);
	RenderSize = innerInkSize;
	//�ü�����֤innerInkSize��Max֮��
	if (std::isnan(Width))
		if (innerInkSize.width() > MaxWidth)	innerInkSize.width() = MaxWidth;
	if (std::isnan(Height))
		if (innerInkSize.height() > MaxHeight)	innerInkSize.height() = MaxHeight;
	Size clipInkSize(std::min(innerInkSize.width(), Width()), std::min(innerInkSize.height(), Height()));

	switch (HorizontalAlignment)
	{
	case HorizontalAlignmentE::Left:	Offset().x() = finalRect.x() + Margin().left();														break;
	case HorizontalAlignmentE::Center:	Offset().x() = finalRect.x() + Margin().left() + (clientSize.width() - RenderSize().width()) / 2;	break;
	case HorizontalAlignmentE::Right:	Offset().x() = finalRect.width() - Margin().right() - RenderSize().width();							break;
	default:
	{
		if (RenderSize().width() >= clientSize.width())
		{
			Offset().x() = finalRect.left() + Margin().left();
		}
		else
		{
			Offset().x() = finalRect.x() + Margin().left() + (clientSize.width() - RenderSize().width()) / 2;
		}
	}
		break;
	}

	switch (VerticalAlignment)
	{
	case VerticalAlignmentE::Top:		Offset().y() = finalRect.top() + Margin().top();	break;
	case VerticalAlignmentE::Center:	Offset().y() = finalRect.top() + Margin().top() + (clientSize.height() - RenderSize().height()) / 2;	break;
	case VerticalAlignmentE::Bottom:	Offset().y() = finalRect.top() + (finalRect.height() - Margin().bottom() - RenderSize().height());		break;
	default:
	{
		if (RenderSize().height() >= clientSize.height())
		{
			Offset().y() = finalRect.top() + Margin().top();
		}
		else
		{
			Offset().y() = finalRect.y() + Margin().top() + (clientSize.height() - RenderSize().height()) / 2;
		}
	}
		break;
	}
	m_actualSize = RenderSize;
	//�ü�
//	if (m_actualSize.width() > finalRect.width())	m_actualSize.width() = finalRect.width();
//	if (m_actualSize.height() > finalRect.height())	m_actualSize.height() = finalRect.height();
}

Size UIElement::measureOverride(const Size & availableSize)
{
	return availableSize;
}

Size UIElement::arrangeOverride(const Size & finalSize)
{
	return finalSize;
}

void UIElement::onMouseEnter()
{
}

void UIElement::onMouseLeave()
{
}

void UIElement::onMouseDown()
{
}

void UIElement::onMouseUp()
{
}

void UIElement::onMouseLeftButtonDown()
{
}

void UIElement::onMouseLeftButtonUp()
{
}

void UIElement::onMouseRightButtonDown()
{
}

void UIElement::onMouseRightButtonUp()
{
}

void UIElement::onMouseMove()
{
}

void UIElement::onMouseWheel(int delta)
{
}

void UIElement::onRender(std::shared_ptr<nb::gl::Context> drawContext)
{
}
