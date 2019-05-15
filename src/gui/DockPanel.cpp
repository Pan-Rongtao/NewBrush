﻿#include "gui/DockPanel.h"
#include "gui/AttachedProperty.h"

using namespace nb::core;
using namespace nb::gui;

#define DOCKPANEL_ATTACHED_PROPERTY_DOCK	"DockPanel.Dock"

DockPanel::DockPanel()
{
}

DockPanel::~DockPanel()
{
}

void DockPanel::setDock(std::shared_ptr<UIElement> element, DockE dock)
{
	if (std::find(Children().begin(), Children().end(), element) != Children().end())
	{
		AttachedProperties::registerAttached(element, DOCKPANEL_ATTACHED_PROPERTY_DOCK, dock);
	}
}

DockE DockPanel::getDock(std::shared_ptr<UIElement> element)
{
	auto v = AttachedProperties::findAttached(element, DOCKPANEL_ATTACHED_PROPERTY_DOCK);
	return v.empty() ? DockE::Left : any_cast<DockE>(v);
}

//当测量一个子元素时，遵循这样的原则：如果该子元素已经是最后一个元素，它的分配将受到LastChildFill的影响；
//如果LastChildFill为true，将所有的remainSize供给它测量；否则走另一个分支：
//当Dock是在左右停靠，它的measure宽为它Width（未指定时为0），高为它的Height（未指定时为remainSize.height)
//每一个子元素measure后，将留下remainSize，供余下的子元素测量，一直到所有的子元素测量完成。
Size DockPanel::measureOverride(const Size & availableSize)
{
	Size remainSize = availableSize;
	for (int i = 0; i != Children().size(); ++i)
	{
		auto const &child = Children().at(i);
		Size childMeasureSize;
		if (LastChildFill() && (i == Children().size() - 1))
		{
			childMeasureSize = remainSize;
		}
		else
		{
			auto dock = getDock(child);
			if (dock == DockE::Left || dock == DockE::Right)
			{
				double width = child->Width == NB_DOUBLE_NAN ? 0.0 : child->Width;
				double height = child->Height == NB_DOUBLE_NAN ? remainSize.height() : child->Height;
				childMeasureSize.reset((float)width, (float)height);
			}
			else
			{
				double width = child->Width == NB_DOUBLE_NAN ? remainSize.width() : child->Width;
				double height = child->Height == NB_DOUBLE_NAN ? 0.0 : child->Height;
				childMeasureSize.reset((float)width, (float)height);
			}
		}
		child->measure(childMeasureSize);
		remainSize -= childMeasureSize;
	}
	return availableSize;
}

Size DockPanel::arrangeOverride(const Size & finalSize)
{
	Rect remainRect(0.0f, 0.0f, finalSize);
	for (int i = 0; i != Children().size(); ++i)
	{
		auto child = Children().at(i);
		Size childDesiredSize = child->DesiredSize();
		Rect childArrageRect;
		if (LastChildFill() && (i == Children().size() - 1))
		{
			childArrageRect = remainRect;
		}
		else
		{
			auto dock = getDock(child);
			switch (dock)
			{
			case nb::gui::DockE::Left:	
				childArrageRect = Rect(remainRect.leftTop(), childDesiredSize);
				remainRect.moveOffsetLeft(childDesiredSize.width());
				break;
			case nb::gui::DockE::Right:	
				childArrageRect = Rect(remainRect.right() - childDesiredSize.width(), remainRect.y(), childDesiredSize);
				remainRect.moveOffsetRight(-childDesiredSize.width());
				break;
			case nb::gui::DockE::Top:	
				childArrageRect = Rect(remainRect.leftTop(), childDesiredSize);
				remainRect.moveOffsetTop(childDesiredSize.height());
				break;
			case nb::gui::DockE::Bottom:
				childArrageRect = Rect(remainRect.x(), remainRect.bottom() - childDesiredSize.height(), childDesiredSize);
				remainRect.moveOffsetBottom(-childDesiredSize.height());
				break;
			default:
				break;
			}
		}
	}
	return finalSize;
}
