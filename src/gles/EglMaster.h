#pragma once
#include "core/NewBrushDef.h"
#include "gles/Configure.h"

namespace nb {namespace gl{ namespace egl{
class Window;
class Context;
class WindowSurface;
class NB_EXPORT WindowMaster
{
public:
	//
	static void Push(nb::gl::egl::Window *window);

	//
	static void Erease(nb::gl::egl::Window *window);

	//��ȡ���ڸ���
	static int GetCount();

	//����һ������
	static nb::gl::egl::Window *At(int index);
};

class NB_EXPORT ContextMaster
{
public:
	//����һ��Contex
	static void Push(Context *contex);

	//����һ��Contex
	static void Erease(Context *contex);

	//��ȡContex����
	static int GetCount();

	//����һ��Contex
	static Context *At(int index);
};

class NB_EXPORT SurfacesMaster
{
public:
	//����һ��WindowSurface
	static void Push(WindowSurface *surface);

	//����һ��WindowSurface
	static void Erease(WindowSurface *surface);

	//��ȡWindowSurface����
	static int GetCount();

	//����һ��WindowSurface
	static WindowSurface *At(int index);
};

}}}
