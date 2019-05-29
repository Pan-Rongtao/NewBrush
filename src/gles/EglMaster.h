#pragma once
#include "core/Def.h"
#include <vector>

namespace nb {namespace gl{
class Window;
class Context;
class WindowSurface;
class NB_API EglMaster
{
public:
	//���ڼ�
	static std::vector<Window *> &windows();

	//�����ļ�
	static std::vector<Context *> &contexts();

	//windowsSurface��
	static std::vector<WindowSurface *> &windowSurfaces();
};

}}
