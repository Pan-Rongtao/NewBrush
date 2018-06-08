#pragma once
#include "gles/Model3D.h"

namespace nb{ namespace gl{ namespace Gles{

class NB_EXPORT Cube : public Model3D
{
public:
	//����һ�������壬����������(0.0, 0.0, 0.0)�����ĳ���߶���0.0
	Cube();

	//����һ�������壬�������ĵ���centerPosition�����ĳ������lenght, wide, height
	Cube(const nb::Math::Vec3 &centerPosition, float lenght, float width, float height);

protected:
	virtual IndicesSequece VertextsSequenceOverride() const;
};

}}}
