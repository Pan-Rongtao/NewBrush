#pragma once
#include "newbrush/core/Def.h"
#include "newbrush/core/Point.h"

namespace nb{

class UIElement;
class NB_API VisualTreeHelper
{
public:
	//��ȡ�ӽڵ����
	static uint32_t getChildrenCount(UIElement *element);

	//��ȡ�±��ӽڵ�
	static UIElement * getChild(UIElement *element, uint32_t childIndex);

	//��ȡ���ڵ�
	static UIElement * getParent(UIElement *element);

	//���в���
	bool hitTest(UIElement *element, const Point &point);

	UIElement *findLogicalNode(UIElement *logicalTreeNode, const std::string &name);
};

}