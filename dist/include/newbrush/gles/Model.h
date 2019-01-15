/*******************************************************
**	Vertex/Mesh/Model
**
**	
**		ģ����Mesh���Ϲ��ɣ�Mesh���ɶ��㼯�Ϲ��ɣ�һ���������position��color��texCoord�Լ�normal�������ݣ�
**		һ����ԣ��򵥵�ģ����һ��Mesh���ɣ������ӵ�ģ�Ϳ����ɶ��Mesh���ɡ�
**	
**		����Ĺ������£�
**		Vertex��	Position	Color		TextureCoordinate		Normal
**						3		  4					2				  3			= 12
**		Mesh��ѡ���ԵĹ�����Щ���ԣ�Mesh�еĶ��㼯��ʹ��ͬ�������Թ��ɣ�Ҳ����˵��Mesh�е�
**		ÿ�����㶼ӵ����ͬ�����ݿռ䣬����Position|Color�������һ��ģ���ж��Mesh��������ÿ��Mesh
**		������ӵ���Լ��Ķ������Թ��ɣ���Ϊ��ʵ�ʻ��ƹ����У�ÿ��Mesh���ǵ������Ƶġ�����ʹ������
**		Ҳû������ʹ�ò�ͬ�������Թ��ɵı�Ҫ��
**		
**		������
**	
********************************************************/
#pragma once
#include "../core/Vec3.h"
#include "../core/Matrix4x4.h"
#include "../core/EnumFlags.h"
#include <vector>

namespace nb{ namespace gl{

class NB_API Vertex
{
public:
	//������������
	enum VertexAttribute
	{
		positionAttribute			= 0x00000001 << 0,		//λ��
		colorAttribute				= 0x00000001 << 1,		//��ɫ
		textureCoordinateAttribute	= 0x00000001 << 2,		//��������
		normalAttribute				= 0x00000001 << 3,		//����
	};

public:
	Vertex();
	explicit Vertex(const nb::core::Vec3 &position);
	Vertex(const nb::core::Vec3 &position, const nb::core::Vec4 &color);
	Vertex(const nb::core::Vec3 &position, const nb::core::Vec4 &color, const nb::core::Vec2 &texCoord);
	Vertex(const nb::core::Vec3 &position, const nb::core::Vec4 &color, const nb::core::Vec2 &texCoord, const nb::core::Vec3 &normal);

	//λ��
	nb::core::Vec3 &position();
	const nb::core::Vec3 &position() const;

	//��ɫ
	nb::core::Vec4 &color();
	const nb::core::Vec4 &color() const;

	//��������
	nb::core::Vec2 &texCoord();
	const nb::core::Vec2 &texCoord() const;

	//������
	nb::core::Vec3 &normal();
	const nb::core::Vec3 &normal() const;

public:
	//��ȡλ�����������
	static int positionDimension();

	//��ȡ��ɫ���������
	static int colorDimension();

	//��ȡ�����������������
	static int textureCoordinateDimension();

	//��ȡ�������������
	static int normalDimension();

private:
	nb::core::Vec3	m_position;
	nb::core::Vec4	m_color;
	nb::core::Vec2	m_texCoord;
	nb::core::Vec3	m_normal;
};

class NB_API Mesh
{
public:
	Mesh(const nb::core::EnumFlags<Vertex::VertexAttribute> &attributes);
	Mesh(const nb::core::EnumFlags<Vertex::VertexAttribute> &attributes, const std::vector<Vertex> &vertexs, const std::vector<uint16_t> &indices);

	//�Ƿ�������
	bool hasAttribute(Vertex::VertexAttribute attr) const;

	//��ȡ�������
	uint32_t vertexCount() const;

	//��ȡλ������
	float *positionData();
	const float *positionData() const;

	//���õ�vertexIndex�������λ��Ϊposition
	void setPositionAt(uint32_t vertexIndex, const nb::core::Vec3 &position);

	//��ȡ��vertexIndex�������λ������
	nb::core::Vec3 positionAt(uint32_t vertexIndex) const;

	//��ȡ��ɫ����
	float *colorData();
	const float *colorData() const;

	//���õ�vertexIndex���������ɫΪcolor
	void setColorAt(uint32_t vertexIndex, const nb::core::Vec4 &color);

	//��ȡ��vertexIndex���������ɫ
	nb::core::Vec4 colorAt(uint32_t vertexIndex) const;

	//��ȡ������������
	float *textureCoordinateData();
	const float *textureCoordinateData() const;

	//���õ�vertexIndex���������������ΪtexCoord
	void setTextureCoordinateAt(uint32_t vertexIndex, const nb::core::Vec2 &texCoord);

	//��ȡ��vertexIndex���������������
	nb::core::Vec2 textureCoordinateAt(uint32_t vertexIndex) const;

	//��ȡ��������
	float *normalData();
	const float *normalData() const;

	//���õ�vertexIndex������ķ���ΪtexCoord
	void setNormalAt(uint32_t vertexIndex, const nb::core::Vec3 &normal);

	//��ȡ��vertexIndex������ķ���
	nb::core::Vec3 normalAt(uint32_t vertexIndex) const;

	//�����ж�����ɫͳһ
	void unifyColor(const nb::core::Vec4 &color);

	//��������(��ʱ��)
	const std::vector<uint16_t> &indices() const;

private:
	nb::core::EnumFlags<Vertex::VertexAttribute>	m_attributes;
	std::vector<Vertex>								m_vertexs;
	std::vector<uint16_t>							m_indices;
};

class NB_API Model
{
public:
	//����һ��ģ�ͣ����Ķ������Ϊ_vertexCount����������Ϊflags
	//�쳣��nVertexCount < 0
	Model();
	virtual ~Model();

public:
	//mesh����
	uint32_t meshCount() const;

	//mesh
	Mesh &mesh(uint32_t index);
	const Mesh &mesh(uint32_t index) const;

	std::vector<Mesh> &meshs();
	const std::vector<Mesh> &meshs() const;

	//����ģ�;���(������ƽ�ơ���ת�����ţ�
	void setMatrix(const nb::core::Matrix4x4 &matrix);

	//��ȡģ�;���(������ƽ�ơ���ת�����ţ�
	const nb::core::Matrix4x4 &getMatrix() const;

	//ƽ��
	void translate(float x, float y, float z);

	//��ת���Ƕȣ�
	void rotate(float angle, float x, float y, float z);

	//����
	void scale(float x, float y, float z);

	//���в���
	virtual bool hitTest(int x, int y) const;

	bool triangleTest(const nb::core::Vec3 & a, const nb::core::Vec3 &b, const nb::core::Vec3 &c, int x, int y) const;

	virtual void cullFace();

protected:
	std::vector<Mesh>								m_meshs;

private:
	nb::core::Matrix4x4								m_matrix;
	nb::core::Matrix4x4								m_TranslateMatrix;
	nb::core::Matrix4x4								m_RotateMatrix;
	nb::core::Matrix4x4								m_ScaleMatrix;
};

}}
