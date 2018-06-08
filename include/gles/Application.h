#pragma once
#include "core/NewBrushDef.h"
#include "gles/Display.h"
#include "gles/Configure.h"
#include "gles/RenderObject.h"

namespace nb{ namespace gl{ namespace egl{
class Surface;
class WindowSurface;
class Context;
}}}

namespace nb{ namespace gl{ namespace Gles{

class NB_EXPORT Application
{
public:
	//����һ��Application����
	//�쳣����ι���
	Application();
	virtual ~Application();

	//����
	void Run();

protected:
	//��ʼ��
	virtual void InitializeOverride();

	//��Ⱦǰ
	virtual void PreRenderOverride();

	//��Ⱦ��
	virtual void PostRenderOverride();

	//����
	virtual void IdledOverride();


private:
	void Initialize();
	void Render();
};

}}}
