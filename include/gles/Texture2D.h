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
#include <string>
#include "Texture.h"
#include "media/Bitmap.h"

namespace nb{ namespace gl{

class NB_API Texture2D : public Texture
{
public:
	//����һ��2D����������������κ����ݣ�
	//���������Ʒ�ʽΪWrappingMode::WrappingMode_Repeat������������˷�ʽΪTextureFilter::Point
	Texture2D();

	//��һ���Դ��ڵ�id����Texture2D�����뱣֤idδ���ͷ�
	Texture2D(uint32_t id);

	//����һ��2D����������Ŀ��Ϊwidth, height
	Texture2D(unsigned int width, unsigned int height);

	//����һ��2D�������������·������������
	//���������Ʒ�ʽΪWrappingMode::WrappingMode_Repeat������������˷�ʽΪTextureFilter::Point
	Texture2D(const std::string &path);

	//����һ��2D�������������·������������
	//���������Ʒ�ʽΪWrappingMode::WrappingMode_Repeat������������˷�ʽΪfilter
	Texture2D(const std::string &path, const TextureFilter &filter);

	//����һ��2D�������������·������������
	//���������Ʒ�ʽΪwrapping������������˷�ʽΪfilter
	Texture2D(const std::string &path, const TextureWrapping &wrapping, const TextureFilter &filter);

	//����һ��2D��������������ڴ���������
	Texture2D(const nb::media::Bitmap &bm);

	virtual ~Texture2D();

	//����֧�ֵ����ߴ磬��ͬ��GPU�����ز�ͬ��ֵ��MaxWidth��MaxHeightһ����һ����ֵ
	//ע�⣺�˽ӿ�������egl�ĳ�ʼ��������egl��ʼ����ɺ���ܹ��õ���ȷ��ֵ����Ȼ������0
	static int maxWidthSupported();
	static int maxHeightSupported();

public:
	//���ǰ�����ڵ���Gles Api��ǰ�ö�����
	//��ʾ֮���gl����������Ե�ǰ������ÿ�ε�Gles���������Ӧ�õ��ô˺���
	virtual void bind() override;
	virtual void unbind() override;

	//���������Ʒ�ʽ
	virtual void setWrapping(const TextureWrapping &wrapping) override;

	//����������˷�ʽ����������ʾ���ã�������Ĭ�ϵĹ��˷�ʽTextureFilter::Default
	virtual void setFilter(const TextureFilter &filter) override;

	//����·��Դ
	//�쳣��path������
	void loadFromPath(const std::string &path);

	//�����ݼ���
	void loadFromData(const char *data, int width, int height, Texture::PixelFormatE format);

	//��ȡ���ظ�
	unsigned int width() const;

	//��ȡ���ؿ�
	unsigned int height() const;

private:
	unsigned int		m_width;
	unsigned int		m_height;
};

}}
