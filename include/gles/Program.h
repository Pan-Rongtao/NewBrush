/*******************************************************
**	Program
**
**	����
**	
**		��������������GPU�ĳ���һ����ԣ�����Ҫ������Shader
**	�������壬link�����Ϳ�����ʱʹ��
**
**	Program������
**	ProgramFactory�����򹤳���
**
**		������
**	
********************************************************/
#pragma once
#include "core/NewBrushDef.h"
#include "math/Vec2.h"
#include "math/Vec2I.h"
#include "math/Vec3.h"
#include "math/Vec3I.h"
#include "math/Vec4.h"
#include "math/Vec4I.h"
#include "math/Matrix2x2.h"
#include "math/Matrix3x3.h"
#include "math/Matrix4x4.h"

namespace nb{ namespace gl{ namespace Gles{

class VertexShader;
class FragmentShader;
class NB_EXPORT Program
{
public:
	//���ö�����ɫ����ƬԪ��ɫ��
	void SetVertexShader(VertexShader *verShader);
	void SetFragmentShader(FragmentShader *fragShader);
	void SetShader(VertexShader *verShader, FragmentShader *fragShader);

	//����
	//�쳣��
	void Link();

	//��ȡprogram��attribute���ͱ���sName��λ��/��ַ
	//���δ�ҵ�����������-1
	int GetAttributeLocation(const char *name) const;

	//��ȡprogram��uniform���ͱ���sName��λ��/��ַ
	//���δ�ҵ�����������-1
	int GetUniformLocation(const char *name) const;

	//ʹ��
	//�쳣��
	void Use();

	//ȡ��ʹ��
	//�쳣��
	void UnUse();

	//�Ƿ���program��ͬ
	bool Equal(Program *program) const;

	//����λ��Ϊlocation��attribute
	void VertexAttribute(int location, float v);
	void VertexAttribute(int location, const nb::Math::Vec2 &vec);
	void VertexAttribute(int location, const nb::Math::Vec3 &vec);
	void VertexAttribute(int location, const nb::Math::Vec4 &vec);
	void VertexAttribute(int location, nb::Math::Vec2 *vec);
	void VertexAttribute(int location, nb::Math::Vec3 *vec);
	void VertexAttribute(int location, nb::Math::Vec4 *vec);
	void VertexAttributePointer(int location, int dimension, int stride, const void *data);

	//����λ��Ϊlocation��unform
	void Uniform(int location, float v);
	void Uniform(int location, float *v, int count);
	void Uniform(int location, const nb::Math::Vec2 &vec);
	void Uniform(int location, nb::Math::Vec2 *vec, int count);
	void Uniform(int location, const nb::Math::Vec3 &vec);
	void Uniform(int location, nb::Math::Vec3 *vec, int count);
	void Uniform(int location, const nb::Math::Vec4 &vec);
	void Uniform(int location, nb::Math::Vec4 *vec, int count);

	void Uniform(int location, int v);
	void Uniform(int location, int *v, int count);
	void Uniform(int location, const nb::Math::Vec2I &vec);
	void Uniform(int location, nb::Math::Vec2I *vec, int count);
	void Uniform(int location, const nb::Math::Vec3I &vec);
	void Uniform(int location, nb::Math::Vec3I *vec, int count);
	void Uniform(int location, const nb::Math::Vec4I &vec);
	void Uniform(int location, nb::Math::Vec4I *vec, int count);

	void Uniform(int location, const nb::Math::Matrix2x2 &matrix);
	void Uniform(int location, nb::Math::Matrix2x2 *matrix, int count);
	void Uniform(int location, const nb::Math::Matrix3x3 &matrix);
	void Uniform(int location, nb::Math::Matrix3x3 *matrix, int count);
	void Uniform(int location, const nb::Math::Matrix4x4 &matrix);
	void Uniform(int location, nb::Math::Matrix4x4 *matrix, int count);

public:
	//����һ��Program��δָ��������ɫ����ƬԪ��ɫ��
	Program();

	//����һ��Program����Ϊ��ָ���˶�����ɫ����ƬԪ��ɫ��
	Program(VertexShader *verShader, FragmentShader *fragShader);
	~Program();

public:
	static Program *Common();

private:
	VertexShader	*m_VertexShader;
	FragmentShader	*m_FragmentShader;
	unsigned int	m_ProgramHandle;
};

}}}
