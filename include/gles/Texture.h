/*******************************************************
**	Texture
**
**	����
**	
**	����������Ļ��ࡣ
**
**		������������ͬά�����ݵ����ݽṹ��������ɫ���ݣ�
**	�������ݵȡ�2D����ɼ򵥵����Ϊһ��2ά�ṹ���������顣
**	
**		һ������£�������Ҫ��������Ԫ������ָ������
**	�󶨵�Ĭ�ϵ�������Ԫ�ϡ�
**
**		������ӳ�䵽����ʱ�п��ܱ��Ŵ������С�����Կ���ָ��
**	�����õ�������˷�ʽ
**	
**	������2D����Texture2D���� TextureCubemap
**	
**
**		������
**	
********************************************************/

#pragma once
#include "gles/TextureWrapping.h"
#include "gles/TextureFilter.h"
#include "media/Bitmap.h"

namespace nb{ namespace gl{ namespace Gles{

class NB_EXPORT Texture
{
public:
	enum PixelFormat
	{
		Format_Bpp8_Alpha = 0,
		Format_Bpp16_Rgb565,
		Format_Bpp24_Rgb888,
		Format_Bpp32_Rgb4444,
		Format_Bpp32_Rgb5551,
		Format_Bpp32_Rgba8888,
	};

public:
	//�󶨵�ǰ������ʾ֮���gl����������Ե�ǰ������ÿ�ε�Gles���������Ӧ�õ��ô˺���
	virtual void Bind() = 0;

	//��������
	virtual void Unbind() = 0;

	//���������Ʒ�ʽ
	virtual void SetTextureWrapping(const TextureWrapping &wrapping) = 0;

	//��ȡ�����Ʒ�ʽ
	TextureWrapping &GetTextureWrapping();
	const TextureWrapping &GetTextureWrapping() const;

	//����������˷�ʽ����������ʾ���ã�������Ĭ�ϵĹ��˷�ʽTextureFilter::Default
	virtual void SetTextureFilter(const TextureFilter &filter) = 0;

	//��ȡ������˷�ʽ
	TextureFilter &GetTexureFilter();
	const TextureFilter &GetTexureFilter() const;


protected:
	Texture();
	virtual ~Texture();

	void BitmapFormatToGlFormat(nb::Media::Bitmap::PixelFormat bmFormat, int &glInteralFormat, int &glPixcelDepth) const;

	TextureWrapping		m_Wrapping;
	TextureFilter		m_Filter;
	unsigned int		m_TextureHandle;
};

}}}
