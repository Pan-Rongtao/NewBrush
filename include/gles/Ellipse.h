#pragma once
#include "gles/Model2D.h"

namespace nb{ namespace gl{ namespace Gles{

class NB_EXPORT Ellipse : public Model2D
{
public:
	//����һ����Բ���������ĵ���center�������������᳤�ȷֱ�Ϊa��b
	Ellipse(const nb::Math::Vec2 &center, float a, float b);

protected:
	virtual IndicesSequece VertextsSequenceOverride() const;

};

}}}
