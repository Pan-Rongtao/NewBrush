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
	enum VertexAttributeE
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

	//��ȡλ������|��ɫ����|��ɫ����|�������ݵ������
	static constexpr int positionDimension			= 3;
	static constexpr int colorDimension				= 4;
	static constexpr int textureCoordinateDimension = 2;
	static constexpr int normalDimension			= 3;

	glm::vec3	position;
	glm::vec4	color;
	glm::vec2	texCoord;
	glm::vec3	normal;
};

class NB_API Mesh
{
public:
	Mesh(const nb::core::EnumFlags<Vertex::VertexAttributeE> &attributes);

	//vertexs�����㼯��
	//indices���������У���ʱ�룬�����ر��棩
	Mesh(const nb::core::EnumFlags<Vertex::VertexAttributeE> &attributes, const std::vector<Vertex> &vertexs, const std::vector<uint16_t> &indices);

	//�Ƿ�������
	bool hasAttribute(Vertex::VertexAttributeE attr) const;

	//��ȡλ��|��ɫ|��������|����������
	float *positionData();
	const float *positionData() const;
	float *colorData();
	const float *colorData() const;
	float *textureCoordinateData();
	const float *textureCoordinateData() const;
	float *normalData();
	const float *normalData() const;

	//���㼯��
	std::vector<Vertex> &vertexs();
	const std::vector<Vertex> &vertexs() const;

	//��������(��ʱ��)
	const std::vector<uint16_t> &indices() const;

	//�����ж�����ɫͳһ
	void unifyColor(const glm::vec4 &color);

private:
	nb::core::EnumFlags<Vertex::VertexAttributeE>	m_attributes;
	std::vector<Vertex>								m_vertexs;
	std::vector<uint16_t>							m_indices;
};

class NB_API Model
{
public:
	//����һ��ģ�ͣ����Ķ������Ϊ_vertexCount����������Ϊflags
	//�쳣��nVertexCount < 0
	Model();
	virtual ~Model() = default;

	//mesh����
	std::vector<Mesh> &meshes();
	const std::vector<Mesh> &meshes() const;

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

	//�޳����棬����д�����
	virtual void cullFace();

	//���Ʒ�ʽ������д��Ĭ��ΪGL_TRIANGLES
	virtual unsigned int drawMode() const;

private:
	glm::mat4x4								m_matrix;
	glm::mat4x4								m_translateMatrix;
	glm::mat4x4								m_rotateMatrix;
	glm::mat4x4								m_scaleMatrix;
	std::vector<Mesh>						m_meshes;
};

}}
