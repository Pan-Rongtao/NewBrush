#include "gles/Application.h"
#include "gles/Egl.h"
#include <GLES2/gl2.h>
#include "gles/Window.h"
#include "gles/Display.h"
#include "gles/Configure.h"
#include "gles/RenderObject.h"
#include "EglMaster.h"

using namespace nb::core;
using namespace nb::gl;

Application::Application()
{                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      
	initialize();
}

Application::~Application()
{
}

int Application::run()
{
	InitializeOverride();
	glClearColor(250 / 255.0f, 235 / 255.0f, 215 / 255.0f, 1.0f);
	while(true)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		PreRenderOverride();
		render();
		PostRenderOverride();

		for (int i = 0; i != WindowMaster::count(); ++i)
			WindowMaster::at(i)->pending();

		for(int i = 0; i != SurfacesMaster::count(); ++i)
			nb::gl::swapBuffers(SurfacesMaster::at(i));

		IdledOverride();
	}
}

void Application::InitializeOverride()
{
}

void Application::PreRenderOverride()
{
}

void Application::PostRenderOverride()
{
}

void Application::IdledOverride()
{
}

void Application::render()
{
	static int frames = 0;
	static uint64_t tick = nb::getTickCount();
	for (int i = 0; i != ContextMaster::count(); ++i)
	{
		ContextMaster::at(i)->draw();
	}
	++frames;
	uint64_t tick1 = nb::getTickCount();
	if(tick1 - tick >= 2000)
	{
		float fps = frames * 1000.0f / (tick1 - tick);
		frames = 0;
		tick = tick1;
//		printf("FPS[%.2f]; Batching count[%d]; Drawcalls[%d], Objects[%d], saved by batching[%d]\r\n", fps, bd->GetBatchingCount(), bd->GetBatchingCount(), bd->GetRenderObjectCount(), bd->GetRenderObjectCount() - bd->GetBatchingCount());
		printf("fps:%.2f\r\n", fps);
	}
}

void Application::initialize()
{
	//����display
	nb::gl::initialize(Display::defaultx());

	//����configure

	//ʹ��Configure((int *)NULL)�������֡�ʽ��ͺܶ�
	nb::gl::setConfigure(Configure::fromSystemRecommend(0)/*Configure((int *)NULL)*/);

	//����Contexts
	//ContextMaster::CreateContex(nb::gl::egl::GetCurrentConfigure());

	//����Windows

	//����Surfaces
}
