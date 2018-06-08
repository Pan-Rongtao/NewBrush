/*******************************************************
**	TextureFilter
**
**	�����������
**	
**		������˵���Ҫ������������ӳ�䵽��ͬ�����ϣ�����ߴ������ߴ�
**	��һ�´Ӷ����·Ŵ����С��������ʧ������
**
**		��ͬ���������ǡ���Ĺ��˷�ʽ���Խ��һЩ��ʵ���⡣
**	����Bilinear�������������󣻶���Ҫ�������ƶ��ı����
**	�����ù��˷�ʽΪTrilinear����������˸����
**	
**		���˷�ʽ������ά�ȣ��Ŵ���˺���С����
**
**		������
**	
********************************************************/

#pragma once
#include "system/Global.h"

namespace nb{ namespace gl{ namespace Gles{

class NB_EXPORT TextureFilter
{
public:
	//������˷�ʽ���������£�����ϸ�ڱ�������Խ�ã�����Ҫ��Խ��
	//�Ŵ����ֻ֧��Point��Bilinear
	//��С����֧�����еĹ��˷�ʽ
	enum Filter
	{
		Point = 0,						//���ڽ����ˣ�ָȡ��ӽ�������������ص�λ��
		Bilinear,						//˫���Թ��ˣ����ڽ����ĸ���������Բ�ֵ�㷨������ά����������
		Trilinear,						//�����Թ��ˡ������Թ�����˫���Թ���Ϊ���������pixel��С��texel��С��ӽ�������Mipmap level�ֱ����˫���Թ��ˣ�Ȼ���ٶ�����õ��Ľ���������Բ�ֵ��
		Anisotropic,					//�������Թ��ˣ�����Ҫ��ͼ����ά����ƽ������Ļ(viewport)�����Ǹ���ͬ�Եġ���Ҫ��ͼ����ά��������Ļ��һ���Ƕȵ���б�����Ǹ������Եġ�
	};

public:
	//����һ��������˷�ʽ���Ŵ���˺���С���˶�ʹ��Filter::Piont
	TextureFilter();

	//����һ��������˷�ʽ���Ŵ���˺���С���˶�ʹ��uniformFilter
	TextureFilter(Filter uniformFilter);

	//����һ��������˷�ʽ���Ŵ���˺���С���˶�ʹ��uniformFilter
	TextureFilter(Filter magnify, Filter narrow);

	//��ȡ�Ŵ�/��С���˷�ʽ
	Filter GetMagnifyFilter() const;
	Filter GetNarrowFilter() const;


public:
	//����Ĭ�ϵĹ��˷�ʽ
	static TextureFilter Default();

	//��ȡglֵ
	static int ToGlValue(Filter filter);

private:

	Filter	m_MagnifyFilter;
	Filter	m_NarrowFilter;
};

}}}
