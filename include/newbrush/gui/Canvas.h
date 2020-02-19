﻿/******************************************************************************

 * Copyright (c) 2016，德赛西威汽车电子有限公司

 * All rights reserved

 * 编写者: 苏志飞

 * 编写日期: 2016-04

 * 简要描述: 通过SetTop()和SetLeft()来设置Canvas控件下面的元素放置的位置
		

 * 修改记录:

 *****************************************************************************/
#pragma once
#include "newbrush/gui/Panel.h"
#include "newbrush/core/Size.h"

namespace nb{
namespace gui{

class NB_API Canvas : public Panel
{
public:
	Canvas();
	virtual ~Canvas() = default;

	static constexpr char *AttachedPropertyLeft		= "Canvas.Left";
	static constexpr char *AttachedPropertyRight	= "Canvas.Right";
	static constexpr char *AttachedPropertyTop		= "Canvas.Top";
	static constexpr char *AttachedPropertyBottom	= "Canvas.Bottom";
	
	void setLeft(std::shared_ptr<UIElement> element, float left);
	float getLeft(std::shared_ptr<UIElement> element);

	void setRight(std::shared_ptr<UIElement> element, float right);
	float getRight(std::shared_ptr<UIElement> element);

	void setTop(std::shared_ptr<UIElement> element, float top);
	float getTop(std::shared_ptr<UIElement> element);

	void setBottom(std::shared_ptr<UIElement> element, float bottom);
	float getBottom(std::shared_ptr<UIElement> element);


protected:
	virtual Size measureOverride(const Size &availableSize) override;
	virtual Size arrangeOverride(const Size &finalSize) override;
};

}}