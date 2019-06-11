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
#include "../core/EnumFlags.h"
#include "glm/glm.hpp"
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
	explicit Vertex(const glm::vec3 &position);
	Vertex(const glm::vec3 &position, const glm::vec4 &color);
	Vertex(const glm::vec3 &position, const glm::vec4 &color, const glm::vec2 &texCoord);
	Vertex(const glm::vec3 &position, const glm::vec4 &color, const glm::vec2 &texCoord, const glm::vec3 &normal);

	//λ��
	glm::vec3 &position();
	const glm::vec3 &position() const;

	//��ɫ
	glm::vec4 &color();
	const glm::vec4 &color() const;

	//��������
	glm::vec2 &texCoord();
	const glm::vec2 &texCoord() const;

	//������
	glm::vec3 &normal();
	const glm::vec3 &normal() const;

public:
	//��ȡλ�����������
	static constexpr int positionDimension = 3;

	//��ȡ��ɫ���������
	static constexpr int colorDimension = 4;

	//��ȡ�����������������
	static constexpr int textureCoordinateDimension = 2;

	//��ȡ�������������
	static constexpr int normalDimension = 3;

private:
	glm::vec3	m_position;
	glm::vec4	m_color;
	glm::vec2	m_texCoord;
	glm::vec3	m_normal;
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
	void setPositionAt(uint32_t vertexIndex, const glm::vec3 &position);

	//��ȡ��vertexIndex�������λ������
	glm::vec3 positionAt(uint32_t vertexIndex) const;

	//��ȡ��ɫ����
	float *colorData();
	const float *colorData() const;

	//���õ�vertexIndex���������ɫΪcolor
	void setColorAt(uint32_t vertexIndex, const glm::vec4 &color);

	//��ȡ��vertexIndex���������ɫ
	glm::vec4 colorAt(uint32_t vertexIndex) const;

	//��ȡ������������
	float *textureCoordinateData();
	const float *textureCoordinateData() const;

	//���õ�vertexIndex���������������ΪtexCoord
	void setTextureCoordinateAt(uint32_t vertexIndex, const glm::vec2 &texCoord);

	//��ȡ��vertexIndex���������������
	glm::vec2 textureCoordinateAt(uint32_t vertexIndex) const;

	//��ȡ��������
	float *normalData();
	const float *normalData() const;

	//���õ�vertexIndex������ķ���ΪtexCoord
	void setNormalAt(uint32_t vertexIndex, const glm::vec3 &normal);

	//��ȡ��vertexIndex������ķ���
	glm::vec3 normalAt(uint32_t vertexIndex) const;

	//�����ж�����ɫͳһ
	void unifyColor(const glm::vec4 &color);

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
	void setMatrix(const glm::mat4x4 &matrix);

	//��ȡģ�;���(������ƽ�ơ���ת�����ţ�
	const glm::mat4x4 &getMatrix() const;

	//ƽ��
	void translate(float x, float y, float z);

	//��ת���Ƕȣ�
	void rotate(float angle, float x, float y, float z);

	//����
	void scale(float x, float y, float z);

	//���в���
	virtual bool hitTest(int x, int y) const;

	bool triangleTest(const glm::vec3 & a, const glm::vec3 &b, const glm::vec3 &c, int x, int y) const;

	virtual void cullFace();

protected:
	std::vector<Mesh>						m_meshs;

private:
	glm::mat4x4								m_matrix;
	glm::mat4x4								m_translateMatrix;
	glm::mat4x4								m_rotateMatrix;
	glm::mat4x4								m_scaleMatrix;
};

}}
