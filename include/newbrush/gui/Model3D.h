/*******************************************************
**	Model3D
**
**	3D����Ļ���
**
**	�������еƹ�Light��Model3DGroup
**
**
**	�ɶԸ�ģʽ�Ĳ����������úͲ�ѯ
**	RGBģʽ��R��G��B�����Ͳ�����ΧΪ0~255���������Ϊ0.0~1.0��
**  SHVģʽ��S��H��B��S[0.0,360.0]��H[0.0,1.0]��B[0.0,1.0]
**
**
**		������
**
********************************************************/

#pragma once
#include "newbrush/core/DependencyObject.h"
#include "newbrush/core/Point.h"
#include "glm/glm.hpp"

namespace nb {

class NB_API Model3D : public DependencyObject
{
public:
	DependencyPropertyPtr TransformProperty();	//�任����������
};

using Model3DPtr = std::shared_ptr<Model3D>;
using Model3DCollectionPtr = std::shared_ptr<std::vector<Model3DPtr>>;
class NB_API Model3DGroup : public Model3D
{
public:
	DependencyPropertyPtr ChildrenProperty();	//Model3DPtr���󼯺ϵ��������ԣ�Model3DCollectionPtr��Ĭ��ֵnullptr��
};


using Vec2CollectionPtr = std::shared_ptr<std::vector<glm::vec2>>;
using Vec3CollectionPtr = std::shared_ptr<std::vector<glm::vec3>>;
using Int16CollectionPtr = std::shared_ptr<std::vector<int16_t>>;
class Material;
using MaterialPtr = std::shared_ptr<Material>;
class NB_API Mesh3D : public Model3D
{
public:
	static DependencyPropertyPtr PositionsProperty();			//���㼯�ϵ��������ԣ�Vec3CollectionPtr, Ĭ��ֵnullptr)
	static DependencyPropertyPtr TextureCoordinatesProperty();	//�������꼯�ϵ��������ԣ�Vec2CollectionPtr, Ĭ��ֵnullptr)
	static DependencyPropertyPtr TriangleIndicesProperty();		//�������м��ϵ��������ԣ�Int16CollectionPtr, Ĭ��ֵnullptr)
	static DependencyPropertyPtr NormalsProperty();				//���������ϵ��������ԣ�Vec3CollectionPtr, Ĭ��ֵnullptr)
	static DependencyPropertyPtr MaterialProperty();			//���ʵ��������ԣ�MaterialPtr, Ĭ��ֵnullptr)
};

class NB_API Light : public Model3D
{

};


}