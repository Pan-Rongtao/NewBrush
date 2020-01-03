﻿#pragma once
#include "Control.h"

namespace nb{
namespace gui{

class NB_API ContentControl : public Control
{
public:
	explicit ContentControl();
	virtual ~ContentControl() = default;

	Property_rw<std::shared_ptr<UIElement>>	Content;			//内容
	static DependencyProperty			ContentProperty();	//内容依赖属性
	
	virtual void onRender(Viewport2D & drawContext) override;

protected:
	virtual void onPropertyChanged(const DependencyPropertyChangedEventArgs &args) override;

	virtual Size measureOverride(const Size &availableSize) override;
	virtual Size arrangeOverride(const Size &finalSize) override;

};

}}
