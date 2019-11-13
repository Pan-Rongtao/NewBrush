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
	Vertex();
	explicit Vertex(const glm::vec3 &position);
	Vertex(const glm::vec3 &position, const glm::vec4 &color);
	Vertex(const glm::vec3 &position, const glm::vec4 &color, const glm::vec2 &texCoord);
	Vertex(const glm::vec3 &position, const glm::vec4 &color, const glm::vec2 &texCoord, const glm::vec3 &normal);

	//��ȡλ������|��ɫ����|��ɫ����|�������ݵ�������Լ�������
	static constexpr int positionDimension	= 3;
	static constexpr int colorDimension		= 4;
	static constexpr int texCoordDimension	= 2;
	static constexpr int normalDimension	= 3;
	static constexpr int stride				= (positionDimension + colorDimension + texCoordDimension + normalDimension) * sizeof(float);

	glm::vec3	position;
	glm::vec4	color;
	glm::vec2	texCoord;
	glm::vec3	normal;
};

class NB_API Mesh
{
public:
	Mesh();

	//vertexs�����㼯��
	//indices���������У���ʱ�룬�����ر��棩
	Mesh(const std::vector<Vertex> &vertexs, const std::vector<uint16_t> &indices);

	Mesh(const Mesh &other);
	Mesh(const Mesh &&other);
	void operator = (const Mesh &other);
	void operator = (const Mesh &&other);

	//��ȡλ��|��ɫ|��������|����������
	float *positionData();
	const float *positionData() const;
	float *colorData();
	const float *colorData() const;
	float *textureCoordinateData();
	const float *textureCoordinateData() const;
	float *normalData();
	const float *normalData() const;

	//�����ж�����ɫͳһ
	void unifyColor(const glm::vec4 &color);

	std::vector<Vertex>		vertexs;	//��������
	std::vector<uint16_t>	indices;	//��������(��ʱ��)

};

class NB_API Model
{
public:
	//����һ���յ�ģ��
	Model();
	Model(const std::vector<Mesh> &_meshes);
	Model(const Model &other);
	Model(const Model &&other);
	void operator = (const Model &other);
	void operator = (const Model &&other);
	virtual ~Model() = default;

	//��Ⱦǰָ��
	virtual void preprocess();

	//�������в���
	//xNormalized,yNormalized����׼������[-1.0, 1.0]
	virtual bool sightHitTest(float xNormalized, float yNormalized) const;

	//�������в���
	//x,y������
	virtual bool orthoHitTest(float x, float y) const;

	glm::mat4x4			matrix;	//ģ�;���
	std::vector<Mesh>	meshes;	//����
	uint8_t				mode;	//�滭ģʽ��Ĭ��GL_TRIANGLES��ע�⣺Ϊ���ڴ棬���Ͷ���Ϊ1���ֽڣ�

private:
	bool intersect(const glm::vec3 &raypos, const glm::vec3 &raydir) const;

};

}}
