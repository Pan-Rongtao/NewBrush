#pragma once
#include "core/Def.h"
#include "gles/Configure.h"

namespace nb {namespace gl{
class Window;
class Context;
class WindowSurface;
class NB_API WindowMaster
{
public:
	//
	static void push(nb::gl::Window *window);

	//
	static void erease(nb::gl::Window *window);

	//��ȡ���ڸ���
	static int count();

	//����һ������
	static nb::gl::Window *at(int index);
};

class NB_API ContextMaster
{
public:
	//����һ��Contex
	static void push(Context *contex);

	//����һ��Contex
	static void erease(Context *contex);

	//��ȡContex����
	static int count();

	//����һ��Contex
	static Context *at(int index);
};

class NB_API SurfacesMaster
{
public:
	//����һ��WindowSurface
	static void push(WindowSurface *surface);

	//����һ��WindowSurface
	static void erease(WindowSurface *surface);

	//��ȡWindowSurface����
	static int count();

	//����һ��WindowSurface
	static WindowSurface *at(int index);
};

}}
