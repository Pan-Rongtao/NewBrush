/*******************************************************
**	::Texture(���������)
**	
**		������������ͬά�����ݵ����ݽṹ��������ɫ���ݣ�
**	�������ݵȡ�2D����ɼ򵥵����Ϊһ��2ά�ṹ���������顣
**	һ������£�������Ҫ��������Ԫ������ָ��������
**	��Ĭ�ϵ�������Ԫ�ϡ�
**
**		������ӳ�䵽����ʱ�п��ܱ��Ŵ������С�����Կ���ָ��
**	�����õ�������˷�ʽ
**
**	::TextureFilter(�����������)
**	
**		������˵�����������������ӳ�䵽��ͬ�����ϣ�����
**	�ߴ������ߴ粻һ�´Ӷ����·Ŵ����С��������ʧ������
**	��ͬ���������ǡ���Ĺ��˷�ʽ���Խ��һЩ��ʵ���⡣ ����
**	Bilinear�������������󣻶���Ҫ�������ƶ��ı����������
**	���˷�ʽΪTrilinear����������˸���⡣
**
**		���˷�ʽ������ά�ȣ��Ŵ���˺���С����
**	
**		������
**	
********************************************************/
#pragma once
#include "../core/Def.h"
#include "glm/glm.hpp"
#include "../media/Bitmap.h"

namespace nb{ namespace gl{

//class TextureWrapping
class NB_API TextureWrapping
{
public:
	//�����Ʒ�ʽ
	enum class WrappingModeE
	{
		Repeat,			//�ظ�
		MirroredRepeat,	//�����ظ�
		ClampToEdge,	//��Ե����
		ClampToBorder,	//�û���ɫ��Ե����
	};

public:
	//����һ�������Ʒ�ʽ������S���T�ᶼ��Repeat
	TextureWrapping();

	//����һ�������Ʒ�ʽ������S��Ϊs������T��Ϊt
	TextureWrapping(WrappingModeE s, WrappingModeE t);

	//����һ�������Ʒ�ʽ������S����s������T����t�������û���ɫ��Ե������borderColor
	TextureWrapping(WrappingModeE s, WrappingModeE t, const glm::vec4 &borderColor);

	//ת��gl��ֵ
	static int glValue(WrappingModeE wrapping);

	//��ȡS��
	WrappingModeE s() const;

	//��ȡT��
	WrappingModeE t() const;

private:
	WrappingModeE	m_s;
	WrappingModeE	m_t;
	glm::vec4		m_borderColor;
};

//class TextureFilter
class NB_API TextureFilter
{
public:
	//������˷�ʽ���������£�����ϸ�ڱ�������Խ�ã�����Ҫ��Խ��
	//�Ŵ����ֻ֧��Point��Bilinear
	//��С����֧�����еĹ��˷�ʽ
	enum class FilterE
	{
		Point = 0,		//���ڽ����ˣ�ָȡ��ӽ�������������ص�λ��
		Bilinear,		//˫���Թ��ˣ����ڽ����ĸ���������Բ�ֵ�㷨������ά����������
		Trilinear,		//�����Թ��ˡ������Թ�����˫���Թ���Ϊ���������pixel��С��texel��С��ӽ�������Mipmap level�ֱ����˫���Թ��ˣ�Ȼ���ٶ�����õ��Ľ���������Բ�ֵ��
		Anisotropic,	//�������Թ��ˣ�����Ҫ��ͼ����ά����ƽ������Ļ(viewport)�����Ǹ���ͬ�Եġ���Ҫ��ͼ����ά��������Ļ��һ���Ƕȵ���б�����Ǹ������Եġ�
	};

public:
	//����һ��������˷�ʽ���Ŵ���˺���С���˶�ʹ��Filter::Piont
	TextureFilter();

	//����һ��������˷�ʽ���Ŵ���˺���С���˶�ʹ��uniformFilter
	TextureFilter(FilterE uniformFilter);

	//����һ��������˷�ʽ���Ŵ���˺���С���˶�ʹ��uniformFilter
	TextureFilter(FilterE magnify, FilterE narrow);

	//����Ĭ�ϵĹ��˷�ʽ(Point)
	static TextureFilter defaultx();

	//��ȡglֵ
	static int glValue(FilterE filter);

	//��ȡ�Ŵ�/��С���˷�ʽ
	FilterE magnifyFilter() const;
	FilterE narrowFilter() const;

private:
	FilterE	m_MagnifyFilter;
	FilterE	m_NarrowFilter;
};

//class Texture
class NB_API Texture
{
public:
	enum class PixelFormatE
	{
		Bpp8_Alpha = 0,
		Bpp16_Rgb565,
		Bpp24_Rgb888,
		Bpp32_Rgb4444,
		Bpp32_Rgb5551,
		Bpp32_Rgba8888,
	};

public:
	virtual ~Texture();

	//�󶨵�ǰ������ʾ֮���gl����������Ե�ǰ������ÿ�ε�Gles���������Ӧ�õ��ô˺���
	virtual void bind() = 0;

	//��������
	virtual void unbind() = 0;

	//���������Ʒ�ʽ
	virtual void setWrapping(const TextureWrapping &wrapping) = 0;

	//��ȡ�����Ʒ�ʽ
	TextureWrapping &wrapping();
	const TextureWrapping &wrapping() const;

	//����������˷�ʽ����������ʾ���ã�������Ĭ�ϵĹ��˷�ʽTextureFilter::Default
	virtual void setFilter(const TextureFilter &filter) = 0;

	//��ȡ������˷�ʽ
	TextureFilter &filter();
	const TextureFilter &filter() const;
	
protected:
	Texture();

	void bitmapFormatToGlFormat(int bmChannels, int &glInteralFormat, int &glPixcelDepth) const;

	TextureWrapping		m_wrapping;
	TextureFilter		m_filter;
	unsigned int		m_handle;
};

}}
