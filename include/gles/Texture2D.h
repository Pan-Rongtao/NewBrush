/*******************************************************
**	Texture2D
**
**	2D����
**	
**	������2D����Ļ��࣬2D����Ӧ����2D����ӳ�䡣
**	
**	������TextureMipmap��CompressedTexture�� BlendTexture
**	
**
**		������
**	
********************************************************/
#pragma once
#include "system/String.h"
#include "gles/Texture.h"

namespace nb{ namespace gl{ namespace Gles{

class NB_EXPORT Texture2D : public Texture
{
public:
	//���ǰ�����ڵ���Gles Api��ǰ�ö�����
	//��ʾ֮���gl����������Ե�ǰ������ÿ�ε�Gles���������Ӧ�õ��ô˺���
	virtual void Bind();
	virtual void Unbind();

	//���������Ʒ�ʽ
	virtual void SetTextureWrapping(const TextureWrapping &wrapping);

	//����������˷�ʽ����������ʾ���ã�������Ĭ�ϵĹ��˷�ʽTextureFilter::Default
	virtual void SetTextureFilter(const TextureFilter &filter);

	//����·��Դ
	//�쳣��path������
	void LoadFromPath(const nb::System::String &path);

	//�����ݼ���
	void LoadFromData(const char *data, int width, int height, Texture::PixelFormat format);

	//��ȡ���ظ�
	int GetPixcelWidth() const;

	//��ȡ���ؿ�
	int GetPixcelHeight() const;


public:
	//����һ��2D����������������κ����ݣ�
	//���������Ʒ�ʽΪWrappingMode::WrappingMode_Repeat������������˷�ʽΪTextureFilter::Point
	Texture2D();

	//����һ��2D�������������·������������
	//���������Ʒ�ʽΪWrappingMode::WrappingMode_Repeat������������˷�ʽΪTextureFilter::Point
	Texture2D(const nb::System::String &path);

	//����һ��2D�������������·������������
	//���������Ʒ�ʽΪWrappingMode::WrappingMode_Repeat������������˷�ʽΪfilter
	Texture2D(const nb::System::String &path, const TextureFilter &filter);

	//����һ��2D�������������·������������
	//���������Ʒ�ʽΪwrapping������������˷�ʽΪfilter
	Texture2D(const nb::System::String &path, const TextureWrapping &wrapping, const TextureFilter &filter);

	//����һ��2D��������������ڴ���������
	//
	Texture2D(const char *data, int width, int height, Texture::PixelFormat format);

	virtual ~Texture2D();

public:
	//����֧�ֵ����ߴ磬��ͬ��GPU�����ز�ͬ��ֵ��MaxWidth��MaxHeightһ����һ����ֵ
	//ע�⣺�˽ӿ�������egl�ĳ�ʼ��������egl��ʼ����ɺ���ܹ��õ���ȷ��ֵ����Ȼ������0
	static int MaxWidthSupported();
	static int MaxHeightSupported();

private:
	int					m_nPixcelWidth;
	int					m_nPixcelHeight;
};

}}}
