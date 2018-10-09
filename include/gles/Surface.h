#pragma once
#include "../core/Object.h"

namespace nb{ namespace gl{

class NB_API Surface
{
public:
	//���ÿ�
	void setWidth(int width);

	//���ø�
	void setHeight(int height);

	//��ȡ���
	int width() const;
	int height() const;

	//egl id
	void *handle() const;

	virtual ~Surface();

protected:
	Surface();

	void		*m_Handle;

private:
	Surface(const Surface &other);
	void operator = (const Surface &other);
};

class NB_API WindowSurface : public Surface
{
public:
	WindowSurface(int width, int height, long windowHandle);
	~WindowSurface();

	long windowHandle();

private:
	long		m_WindowHandle;
};

class NB_API PbufferSurface : public Surface
{
public:
	PbufferSurface(int width, int height);

};

class NB_API PixmapSurface : public Surface
{
public:
	PixmapSurface(int width, int height, void *pixmapHandle);

	void *pixmapHandle();
	const void *pixmapHandle() const;

private:
	void		*m_PixmapHandle;
};

}}
