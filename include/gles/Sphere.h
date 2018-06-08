#pragma once
#include "gles/Model3D.h"

namespace nb{ namespace gl{ namespace Gles{

class Sphere : public Model3D
{
public:
	//����һ�����壬����Բ����centerPoint�����İ뾶��R
	Sphere(const nb::Math::Vec3 &centerPoint, float R);

protected:
	virtual IndicesSequece VertextsSequenceOverride() const;

};

}}}
