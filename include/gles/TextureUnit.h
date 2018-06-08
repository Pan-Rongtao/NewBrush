/*******************************************************
**	TextureUnit
**
**	����������Ԫ
**	
**	������Ԫ�������������Ǵ���GPU����������ͼ��ģ��
**		����ȡ�����Կ�
**	
**	һ������£�������Ҫ�󶨶��������Ԫ����
**	������Ҫͬʱ���ж�����Ĳ���
**
**		������
**	
********************************************************/
#pragma once
#include "system/Global.h"

namespace nb{ namespace gl{ namespace Gles{

class NB_EXPORT TextureUnit
{
public:
	//����һ��Ĭ��������Ԫ��GL_TEXTURE0
	TextureUnit();

	//���ݱ�ŷ��أ���Ч���Ϊ0 ~ MaxCount-1
	explicit TextureUnit(int index);
	~TextureUnit();

	//����Ԫ�±�
	int GetIndex() const;

	//����Ԫ��ַ
	int GlAddress() const;

	//���ǰ����Ԫ
	void Activate();

public:
	//��������Ԫ�����������ȡ�����Կ�
	static int MaxCount();

	//����Ĭ�ϵ�����Ԫ����
	static TextureUnit Default();

	//����һ������Ԫ��Ч���Ϊ0 ~ MaxCount-1
	static TextureUnit FromIndex(int index);

	//����һ������Ԫ��glEnumUnitAddress����GL_TEXTURE0~GL_TEXTURE31
	static TextureUnit FromGlAddress(int glEnumUnitAddress);

	//���ص�ǰ�������Ԫ����
	static TextureUnit Activated();

private:
	int		m_nAddress;
};
	
}}}
