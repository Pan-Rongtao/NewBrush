/*******************************************************
**	Program
**
**	����
**	
**		��������������GPU�ĳ���һ����ԣ�����Ҫ������Shader
**	�������壬link�����Ϳ�����ʱʹ��
**
**	Program������
**
**		������
**	
********************************************************/
#pragma once
#include "../core/Def.h"
#include "../core/Vec2.h"
#include "../core/Vec3.h"
#include "../core/Vec4.h"
#include "../core/Matrix2x2.h"
#include "../core/Matrix3x3.h"
#include "../core/Matrix4x4.h"
#include "SourceDecoder.h"

namespace nb{ namespace gl{

class VertexShader;
class FragmentShader;
class NB_API Program
{
public:
	enum AttributeLocation
	{
		positionLocation	= 0,	//"nb_Position"
		colorLocation,				//"nb_Color"
		texCoordLocaltion,			//"nb_TextCoord"
		normalLocation,				//"nb_Normal"
	};

public:
	//����һ��Program��δָ��������ɫ����ƬԪ��ɫ��
	Program();

	//����һ��Program����Ϊ��ָ���˶�����ɫ����ƬԪ��ɫ��
	Program(std::shared_ptr<VertexShader> verShader, std::shared_ptr<FragmentShader> fragShader);
	~Program();

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
	void vertexAttribute(int location, const nb::core::Vec2 &vec);
	void vertexAttribute(int location, const nb::core::Vec3 &vec);
	void vertexAttribute(int location, const nb::core::Vec4 &vec);
	void vertexAttribute(int location, nb::core::Vec2 *vec);
	void vertexAttribute(int location, nb::core::Vec3 *vec);
	void vertexAttribute(int location, nb::core::Vec4 *vec);
	void vertexAttributePointer(int location, int dimension, int stride, const void *data);

	//����λ��Ϊlocation��unform
	void uniform(int location, float v);
	void uniform(int location, float *v, int count);
	void uniform(int location, const nb::core::Vec2 &vec);
	void uniform(int location, nb::core::Vec2 *vec, int count);
	void uniform(int location, const nb::core::Vec3 &vec);
	void uniform(int location, nb::core::Vec3 *vec, int count);
	void uniform(int location, const nb::core::Vec4 &vec);
	void uniform(int location, nb::core::Vec4 *vec, int count);

	void uniform(int location, int v);
	void uniform(int location, int *v, int count);
	void uniform(int location, const nb::core::Vec2I &vec);
	void uniform(int location, nb::core::Vec2I *vec, int count);
	void uniform(int location, const nb::core::Vec3I &vec);
	void uniform(int location, nb::core::Vec3I *vec, int count);
	void uniform(int location, const nb::core::Vec4I &vec);
	void uniform(int location, nb::core::Vec4I *vec, int count);

	void uniform(int location, const nb::core::Matrix2x2 &matrix);
	void uniform(int location, nb::core::Matrix2x2 *matrix, int count);
	void uniform(int location, const nb::core::Matrix3x3 &matrix);
	void uniform(int location, nb::core::Matrix3x3 *matrix, int count);
	void uniform(int location, const nb::core::Matrix4x4 &matrix);
	void uniform(int location, nb::core::Matrix4x4 *matrix, int count);

	//�������ύ���е�uniform����
	void uniformDefault();

private:
	std::shared_ptr<VertexShader>	m_VertexShader;
	std::shared_ptr<FragmentShader>	m_FragmentShader;
	unsigned int					m_ProgramHandle;
};

}}
