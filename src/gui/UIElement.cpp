#include "gui/UIElement.h"

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
{
	DesiredSize.getter([&]()->Size& { return m_desiredSize; });
	ActualSize.getter([&]()->Size& {return m_actualSize; });
	Visibility.notify(std::bind(&UIElement::onVisibilityChanged, this, std::placeholders::_1, std::placeholders::_2));
	Opacity.notify(std::bind(&UIElement::onOpacityChanged, this, std::placeholders::_1, std::placeholders::_2));
	Focusable.notify(std::bind(&UIElement::onFocusableChanged, this, std::placeholders::_1, std::placeholders::_2));
	Margin.notify(std::bind(&UIElement::onMaginChanged, this, std::placeholders::_1, std::placeholders::_2));
}

UIElement::~UIElement()
{
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
	Width = nb::clamp<float>(MinWidth, MaxWidth, std::isnan(Width) ? desiredSizeTemp.width(): Width);
	Height = nb::clamp<float>(MinHeight, MaxHeight, std::isnan(Height) ? desiredSizeTemp.height() : Height);
	desiredSizeTemp.reset(Width, Height);

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
	Width = nb::clamp<float>(MinWidth, MaxWidth, std::isnan(Width) ? arrangeSize.width() : Width);
	Height = nb::clamp<float>(MinHeight, MaxHeight, std::isnan(Height) ? arrangeSize.height() : Height);
	arrangeSize.reset(Width(), Height());

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
	return Size();
}

Size UIElement::arrangeOverride(const Size & finalSize)
{
	return finalSize;
}

void UIElement::onRender(std::shared_ptr<nb::gl::Context> drawContext)
{
}

void UIElement::onVisibilityChanged(const nb::gui::VisibilityE & _old, const nb::gui::VisibilityE & _new)
{

}

void UIElement::onOpacityChanged(const float & _old, const float & _new)
{
}

void UIElement::onFocusableChanged(const bool & _old, const bool & _new)
{
}

void UIElement::onDesiredSizeChanged(const Size & _old, const Size & _new)
{
}

void UIElement::onMaginChanged(const Thickness & _old, const Thickness & _new)
{
}
