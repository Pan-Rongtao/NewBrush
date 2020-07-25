#pragma once
#include "newbrush/gui/UIElement.h"

namespace nb {

class ModeVisual3D : public DependencyObject
{
public:
	DependencyPropertyPtr TransformProperty();	//�任����������
	DependencyPropertyPtr ChildrenProperty();	//�ӽڵ���������ԣ�std::shared_ptr<MeshCollection>, Ĭ��ֵnullptr��

};

using ModeVisual3DPtr = std::shared_ptr<ModeVisual3D>;
}