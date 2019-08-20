#include "gui/ButtonBase.h"

using namespace nb::gui;

ButtonBase::ButtonBase()
	: ClickMode([&](ClickModeE mode) {set(ClickModeProperty(), mode); }, [&]() {return get<ClickModeE>(ClickModeProperty()); })
	, IsPressed([&]() {return get<bool>(IsPressedProperty()); })
{
}

bool ButtonBase::isEnableCore()
{
	return true;
}

const DependencyProperty ButtonBase::ClickModeProperty()
{
	static const DependencyProperty dp = DependencyProperty::registerDependency<ButtonBase, ClickModeE>("ClickMode", ClickModeE::release);
	return dp;
}

const DependencyProperty ButtonBase::IsPressedProperty()
{
	static const DependencyProperty dp = DependencyProperty::registerDependency<ButtonBase, bool>("IsPressed", false);
	return dp;
}

void ButtonBase::onClick()
{
}

void ButtonBase::onKeyDown()
{
}

void ButtonBase::onKeyUp()
{
}

void ButtonBase::onMouseEnter()
{
}

void ButtonBase::onMouseMove()
{
}

void ButtonBase::onMouseLeave()
{
}

void ButtonBase::onLeftButtonDown()
{
}

void ButtonBase::onLeftButtonUp()
{
}