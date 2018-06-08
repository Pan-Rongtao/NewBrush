/*******************************************************
**	Model
**
**	ģ��
**	
**	ģ���������������幹������ݽṹ
**	���ĺ����Ƕ��㼯�ϣ�
**		һ����һά����ά����άģ��
**
**		��ά��һ������С�ĵ㣬һά��һ������ϸ���ߣ�
**		��ά��һ�����ޱ���ƽ�棬��ά��һ�����޴��������
**
**		Vertext��	Position	Color		TextureCoordinate		Normal
**						3		  4					2				  3			= 12
**		
**		������
**	
********************************************************/
#pragma once
#include "math/Vec3.h"
#include "math/Matrix4x4.h"
#include "system/EnumFlags.h"
#include "gles/IndicesSequece.h"

namespace nb{ namespace gl{ namespace Gles{

class ModelEventListener;
class NB_EXPORT Model
{
public:
	//������������
	enum VertexAttributesType
	{
		Vertex_Attribute_Position				= 0x00000001 << 0,	//λ��
		Vertex_Attribute_Color					= 0x00000001 << 1,	//��ɫ
		Vertex_Attribute_TextureCoordinate		= 0x00000001 << 2,	//��������
		Vertex_Attribute_Normal					= 0x00000001 << 3,	//����
	};

public:
	//����һ��ģ�ͣ����Ķ�����������Ϊflags
	//�쳣��nVertexCount < 0
	Model(int nVertexCount, nb::System::EnumFlags<VertexAttributesType> flags);

	virtual ~Model();

public:
	//�Ƿ������������
	bool HasVertexAttribute(VertexAttributesType type) const;

	//��ȡ����
	float *GetData() const;

	//��ȡ�������
	int GetVertexCount() const;

	//����λ������
	void SetPositionArrayData(float *data);
	void SetPositionAt(int vertexIndex, const nb::Math::Vec3 &position);

	//��ȡλ������
	float *GetPositionArrayData() const;
	nb::Math::Vec3 GetPositionAt(int vertexIndex) const;

	//������ɫ����
	void SetColorArrayData(float *data);
	void SetColorAt(int vertexIndex, const nb::Math::Vec4 &color);

	//��ȡ��ɫ����
	float *GetColorArrayData() const;
	nb::Math::Vec4 GetColorAt(int vertexIndex) const;

	//����������������
	void SetTextureCoordinateArrayData(float *data);
	void SetTextureCoordinateAt(int vertexIndex, const nb::Math::Vec2 &texCoord);

	//��ȡ������������
	float *GetTextureCoordinateArrayData() const;
	nb::Math::Vec2 GetTextureCoordinateAt(int vertexIndex) const;

	//����������������
	void SetNormalArrayData(float *data);
	void SetNormalAt(int vertexIndex, const nb::Math::Vec3 &texCoord);

	//��ȡ��������
	float *GetNormalArrayData() const;
	nb::Math::Vec3 GetNormalAt(int vertexIndex) const;

	//��ȡ�������ݼ�ĵ�Ԫ�����
	//���������������ΪVertex_Attribute_Position | Vertex_Attribute_Color | Vertex_Attribute_TextureCoordinate������3 + 4 + 2=9
	int GetVertexStrideUnit() const;

	//�����ж�����ɫͳһ
	void UnifyColor(const nb::Math::Vec4 &color);

	//�������У�Ĭ��Ϊ˳�������Ҫ�������У���д�˷���
	virtual IndicesSequece VertextsSequenceOverride() const;

	//����ģ�;���
	void SetMatrix(const nb::Math::Matrix4x4 &matrix);

	//��ȡģ�;���
	nb::Math::Matrix4x4 &GetMatrix();
	const nb::Math::Matrix4x4 &GetMatrix() const;

	//���в���
	virtual bool HitTest(int x, int y) const;

	bool TriangleTest(const nb::Math::Vec3 & a, const nb::Math::Vec3 &b, const nb::Math::Vec3 &c, int x, int y) const;

	//�����¼�����
	void SetListener(ModelEventListener *listener);

public:
	//��ȡλ�����������
	static int PositionDimension();

	//��ȡ��ɫ���������
	static int ColorDimension();

	//��ȡ�����������������
	static int TextureCoordinateDimension();

	//��ȡ�������������
	static int NormalDimension();

private:
	int											m_nVertexCount;
	nb::System::EnumFlags<VertexAttributesType>	m_AttributeFlags;
	float										*m_Data;
	nb::Math::Matrix4x4							m_Matrix;
	ModelEventListener							*m_Listener;
};

class NB_EXPORT ModelEventListener
{
public:
	virtual void On_ModelData_Changed(Model::VertexAttributesType type) { (void)type; }
};

}}}
