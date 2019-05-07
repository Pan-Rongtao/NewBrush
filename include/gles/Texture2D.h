/*******************************************************
**	Texture2D
**
**	2D纹理
**	
**	是所有2D纹理的基类，2D纹理应用于2D坐标映射。
**	
**	子类有TextureMipmap、CompressedTexture和 BlendTexture
**	
**
**		潘荣涛
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
	//构建一个2D纹理对象，它不包含任何数据，
	//它的纹理环绕方式为WrappingMode::WrappingMode_Repeat，它的纹理过滤方式为TextureFilter::Point
	Texture2D();

	//构建一个2D纹理对象，它将从路径中载入数据
	//它的纹理环绕方式为WrappingMode::WrappingMode_Repeat，它的纹理过滤方式为TextureFilter::Point
	Texture2D(const std::string &path);

	//构建一个2D纹理对象，它将从路径中载入数据
	//它的纹理环绕方式为WrappingMode::WrappingMode_Repeat，它的纹理过滤方式为filter
	Texture2D(const std::string &path, const TextureFilter &filter);

	//构建一个2D纹理对象，它将从路径中载入数据
	//它的纹理环绕方式为wrapping，它的纹理过滤方式为filter
	Texture2D(const std::string &path, const TextureWrapping &wrapping, const TextureFilter &filter);

	//构建一个2D纹理对象，它将从内存载入数据
	Texture2D(const nb::media::Bitmap &bm);

	virtual ~Texture2D();

	//纹理支持的最大尺寸，不同的GPU将返回不同的值；MaxWidth和MaxHeight一般是一样的值
	//注意：此接口依赖于egl的初始化，需在egl初始化完成后才能够得到正确的值，不然将返回0
	static int maxWidthSupported();
	static int maxHeightSupported();

public:
	//激活当前纹理，在调用Gles Api的前置动作，
	//表示之后的gl操作都是针对当前纹理。在每次的Gles纹理操作都应该调用此函数
	virtual void bind() override;
	virtual void unbind() override;

	//设置纹理环绕方式
	virtual void setWrapping(const TextureWrapping &wrapping) override;

	//设置纹理过滤方式，假若不显示设置，将采用默认的过滤方式TextureFilter::Default
	virtual void setFilter(const TextureFilter &filter) override;

	//加载路径源
	//异常：path不存在
	void loadFromPath(const std::string &path);

	//从数据加载
	void loadFromData(const char *data, int width, int height, Texture::PixelFormat format);

	//获取像素高
	int pixcelWidth() const;

	//获取像素宽
	int pixcelHeight() const;

private:
	int					m_nPixcelWidth{ 0 };
	int					m_nPixcelHeight{ 0 };
};

}}
