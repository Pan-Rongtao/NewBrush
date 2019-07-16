/*******************************************************
**	Program/Programs
**
**	Program����
**	
**		��������������GPU�ĳ���һ����ԣ�����Ҫ������Shader
**	�������壬link�����Ϳ�����ʱʹ��
**
**	Programs���ṩ���õ�Program������primitive��phong��cube��
**
**		������
**	
********************************************************/
#pragma once
#include "../core/Def.h"
#include "glm/glm.hpp"
#include <map>

namespace nb{ namespace gl{

class VertexShader;
class FragmentShader;
class NB_API Program
{
public:
	//nb�̶�location��locationStr
	static constexpr int nbPositionLocation			= 0;
	static constexpr int nbColorLocation			= 1;
	static constexpr int nbTexCoordLocaltion		= 2;
	static constexpr int nbNormalLocation			= 3;
	static constexpr char *nbPositionLocationStr	= "nbPos";
	static constexpr char *nbColorLocationStr		= "nbColor";
	static constexpr char *nbTexCoordLocaltionStr	= "nbTexCoord";
	static constexpr char *nbNormalLocationStr		= "nbNormal";
	static constexpr char *nbMvpStr					= "nbMvp";
	static constexpr char *nbMStr					= "nbM";
	static constexpr char *nbVStr					= "nbV";
	static constexpr char *nbPStr					= "nbP";
	static constexpr char *nbColorModeLocationStr	= "nbColorMode";

public:
	//����һ��Program��δָ��������ɫ����ƬԪ��ɫ��
	Program();

	//����һ��Program����Ϊ��ָ���˶�����ɫ����ƬԪ��ɫ��
	Program(std::shared_ptr<VertexShader> verShader, std::shared_ptr<FragmentShader> fragShader);
	virtual ~Program();

public:
	//���ö�����ɫ��
	void setVertexShader(std::shared_ptr<VertexShader> verShader);

	//��ȡ������ɫ��
	std::shared_ptr<VertexShader> vertexShader();

	//����ƬԪ��ɫ��
	void setFragmentShader(std::shared_ptr<FragmentShader> fragShader);

	//��ȡƬԪ��ɫ��
	std::shared_ptr<FragmentShader> fragmentShader();

	//����
	//�쳣��
	void link();

	//��ȡprogram��attribute���ͱ���sName��λ��/��ַ
	//���δ�ҵ�����������-1
	int getAttributeLocation(const char *name) const;

	//��ȡprogram��uniform���ͱ���sName��λ��/��ַ
	//���δ�ҵ�����������-1
	int getUniformLocation(const char *name) const;

	//��attributeλ��
	void bindAttributeLocation(unsigned int location, const char *name);

	//ʹ��
	//�쳣��
	void use();

	//ȡ��ʹ��
	//�쳣��
	void disuse();

	//����λ��Ϊlocation��attribute
	void vertexAttribute(int location, float v);
	void vertexAttribute(int location, const glm::vec2 &vec);
	void vertexAttribute(int location, const glm::vec3 &vec);
	void vertexAttribute(int location, const glm::vec4 &vec);
	void vertexAttribute(int location, glm::vec2 *vec);
	void vertexAttribute(int location, glm::vec3 *vec);
	void vertexAttribute(int location, glm::vec4 *vec);
	void vertexAttributePointer(int location, int dimension, int stride, const void *data);

	//����λ��Ϊlocation��unform
	void uniform(int location, float v);
	void uniform(int location, float *v, int count);
	void uniform(int location, const glm::vec2 &vec);
	void uniform(int location, glm::vec2 *vec, int count);
	void uniform(int location, const glm::vec3 &vec);
	void uniform(int location, glm::vec3 *vec, int count);
	void uniform(int location, const glm::vec4 &vec);
	void uniform(int location, glm::vec4 *vec, int count);

	void uniform(int location, int v);
	void uniform(int location, int *v, int count);
	void uniform(int location, const glm::ivec2 &vec);
	void uniform(int location, glm::ivec2 *vec, int count);
	void uniform(int location, const glm::ivec3 &vec);
	void uniform(int location, glm::ivec3 *vec, int count);
	void uniform(int location, const glm::ivec4 &vec);
	void uniform(int location, glm::ivec4 *vec, int count);

	void uniform(int location, const glm::mat2x2 &matrix);
	void uniform(int location, glm::mat2x2 *matrix, int count);
	void uniform(int location, const glm::mat3x3 &matrix);
	void uniform(int location, glm::mat3x3 *matrix, int count);
	void uniform(int location, const glm::mat4x4 &matrix);
	void uniform(int location, glm::mat4x4 *matrix, int count);

private:
	std::shared_ptr<VertexShader>	m_vertexShader;
	std::shared_ptr<FragmentShader>	m_fragmentShader;
	unsigned int					m_programHandle;
};

class NB_API Programs
{
public:
	//��program
	static std::shared_ptr<Program> primitive();

	//phong program
	static std::shared_ptr<Program> phong();

	//cube program
	static std::shared_ptr<Program> cube();

	//glyp program
	static std::shared_ptr<Program> glpy();

private:
	static std::shared_ptr<Program> compileBindLink(const std::string &vs, const std::string &fs);
};

}}
