#pragma once
#include "math/Vec4.h"

namespace nb{ namespace gl{ namespace Gles{

class NB_EXPORT TextureWrapping
{
public:
	//�����Ʒ�ʽ
	enum WrappingMode
	{
		WrappingMode_Repeat,			//�ظ�
		WrappingMode_Mirrored_Repeat,	//�����ظ�
		WrappingMode_Clamp_To_Edge,		//��Ե����
		WrappingMode_Clamp_To_Border,	//�û���ɫ��Ե����
	};

public:
	//����һ�������Ʒ�ʽ������S���T�ᶼ��WrappingMode_Repeat
	TextureWrapping();

	//����һ�������Ʒ�ʽ������S��Ϊs������T��Ϊt
	TextureWrapping(WrappingMode s, WrappingMode t);

	//����һ�������Ʒ�ʽ������S����s������T����t�������û���ɫ��Ե������borderColor
	TextureWrapping(WrappingMode s, WrappingMode t, const nb::Math::Vec4 &borderColor);

	//��ȡS��
	WrappingMode GetS() const;

	//��ȡT��
	WrappingMode GetT() const;

public:
	//ת��gl��ֵ
	static int ToGlValue(WrappingMode wrapping);

private:
	WrappingMode	m_s;
	WrappingMode	m_t;
	nb::Math::Vec4	m_BorderColor;
};


}}}
