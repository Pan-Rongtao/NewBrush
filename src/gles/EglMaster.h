#pragma once
#include "core/Def.h"
#include <vector>

namespace nb {namespace gl{
class Context;
class WindowSurface;
class NB_API EglMaster
{
public:
	//�����ļ�
	static std::vector<Context *> &contexts();

};

}}
